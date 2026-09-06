#!/bin/sh
# Put the display modules on the phone and stop the rootfs from blocking msm.
#
# Four separate things were keeping the display down, and only one of them was
# the device tree:
#
#   1. CONFIG_SM_DISPCC_8550 was not set, so nothing drove
#      af00000.clock-controller ("qcom,sm8650-dispcc" is handled by
#      dispcc-sm8550.c, not by a file named after 8650). With no display clock
#      controller, msm-mdss's devm_clk_bulk_get_all() returns -EPROBE_DEFER
#      forever and then dies of the deferred-probe timeout: that is the
#      "deferred probe timeout, ignoring dependency" / "failed with error -110"
#      pair in the log. This is THE blocker; the rest only mattered after it.
#
#   2. /etc/modprobe.d/zorn-msm.conf held "blacklist msm". Dropping
#      modprobe.blacklist=msm from the kernel command line did nothing, because
#      this file blocks the udev autoload just as effectively. (An explicit
#      "modprobe msm" still works -- blacklist only suppresses alias matches --
#      which is why msm could be loaded by hand and still not bring up KMS.)
#
#   3. panel-xiaomi-o11-42-02-0a.ko was never installed, so nothing claimed
#      panel@0 and the dsi component never completed.
#
#   4. Load order. msm-mdss aggregates dpu + dsi + panel and needs dispcc's
#      clocks; when it binds after driver_deferred_probe_timeout has expired it
#      does not wait for anything. A softdep pulls both dependencies in first.
#
# The kernel release string has not changed and CONFIG_MODVERSIONS is off, so the
# modules built here load against the kernel already on the phone -- no rebuild,
# no reflash of /Image needed for this part.
#
# Usage: ./install-display.sh [user@host]
set -e
cd "$(dirname "$0")"

HOST=${1:-root@10.43.0.1}
MODS="zorn-display/dispcc-sm8550.ko zorn-display/panel-xiaomi-o11-42-02-0a.ko zorn-display/msm.ko"

for m in $MODS; do
	[ -f "$m" ] || { echo "missing $m"; exit 1; }
done

echo "=== $HOST: kernel release and current state ==="
ssh -o BatchMode=yes -o ConnectTimeout=10 "$HOST" bash -s <<'EOF'
echo "  running: $(uname -r)"
echo "  msm blacklisted by: $(grep -rl 'blacklist[[:space:]]*msm' /etc/modprobe.d/ /usr/lib/modprobe.d/ 2>/dev/null | tr '\n' ' ')"
for m in dispcc-sm8550 panel-xiaomi-o11-42-02-0a; do
  echo "  $m: $(modinfo -F filename $m 2>/dev/null || echo 'not installed')"
done
echo "  dispcc bound: $(basename $(readlink /sys/bus/platform/devices/af00000.clock-controller/driver 2>/dev/null) 2>/dev/null || echo NONE)"
EOF

echo "=== copying the modules ==="
for m in $MODS; do
	scp -q -o BatchMode=yes "$m" "$HOST:/tmp/$(basename $m)"
done

echo "=== installing ==="
ssh -o BatchMode=yes -o ConnectTimeout=20 "$HOST" bash -s <<'EOF'
set -e
R=$(uname -r)
mount -o remount,rw / 2>/dev/null || true
install -d /usr/lib/modules/$R/kernel/drivers/gpu/drm/panel
install -d /usr/lib/modules/$R/kernel/drivers/clk/qcom
install -d /usr/lib/modules/$R/kernel/drivers/gpu/drm/msm
install -m 644 /tmp/panel-xiaomi-o11-42-02-0a.ko /usr/lib/modules/$R/kernel/drivers/gpu/drm/panel/
install -m 644 /tmp/dispcc-sm8550.ko             /usr/lib/modules/$R/kernel/drivers/clk/qcom/
install -m 644 /tmp/msm.ko                       /usr/lib/modules/$R/kernel/drivers/gpu/drm/msm/
rm -f /tmp/panel-xiaomi-o11-42-02-0a.ko /tmp/dispcc-sm8550.ko /tmp/msm.ko
depmod -a "$R"
for m in dispcc-sm8550 panel-xiaomi-o11-42-02-0a msm; do
  echo "  $m -> $(modinfo -F filename $m)"
done

cat > /etc/modprobe.d/zorn-msm.conf <<'CONF'
# msm is no longer blacklisted: zorn now has a real panel driver, and the escape
# hatch moved into the device tree instead. GRUB entry 0 boots /dtb/zorn.dtb,
# where display-subsystem@ae00000 is status = "disabled", so msm-mdss simply does
# not bind there no matter what is loaded -- a better fallback than a blacklist,
# because it still lets the GPU half of msm work.
#
# The softdep fixes load order. msm-mdss needs dispcc's clocks and aggregates
# dpu + dsi + panel; if it binds after driver_deferred_probe_timeout has passed it
# will not wait for a provider that is not registered yet and fails with -110.
# dispcc-sm8550 is what provides "qcom,sm8650-dispcc" -- there is no
# dispcc-sm8650.
softdep msm pre: dispcc-sm8550 panel-xiaomi-o11-42-02-0a

# DSI byte-clock override for the DSC link, in uncompressed bits per pixel.
# Commented out = stock upstream behaviour, which derives it from the MIPI DSI
# pixel format and lands on 960 Mbps/lane. 30 (bits_per_component * 3) makes it
# agree with dsi_adjust_pclk_for_compression() and lands on the 1.2 Gbps/lane the
# panel's vendor device tree specifies.
#
# Observed so far on zorn: 960 Mbps -> picture with periodic corruption bands.
#                          1.2 Gbps -> no picture at all.
# So neither is right yet; uncomment and edit to sweep, one reboot per value.
#options msm dsi_dsc_uncompressed_bpp=30
CONF
echo "  softdep: $(sed -n 's/^softdep //p' /etc/modprobe.d/zorn-msm.conf)"
echo "  byte-clock override: $(sed -n 's/^options msm //p' /etc/modprobe.d/zorn-msm.conf || true)$(grep -q '^options msm' /etc/modprobe.d/zorn-msm.conf || echo 'off (stock, 960 Mbps/lane)')"
grep -rl 'blacklist[[:space:]]*msm' /etc/modprobe.d/ /usr/lib/modprobe.d/ 2>/dev/null \
  && echo "  WARNING: msm is still blacklisted somewhere above" \
  || echo "  no blacklist on msm anywhere"

# Load dispcc now so the next msm bind -- this boot or the next -- has its clocks.
modprobe dispcc-sm8550 2>&1 | head -3 || true
sleep 1
echo "  dispcc bound: $(basename $(readlink /sys/bus/platform/devices/af00000.clock-controller/driver 2>/dev/null) 2>/dev/null || echo NONE)"
sync
EOF

cat <<'EOF'

Modules installed and dispcc loaded. What happens next depends on whether
af00000.clock-controller says dispcc-sm8550 above:

  bound  -> the last blocker is gone. Reboot to get a clean probe order:
            msm-mdss already failed permanently this boot (-110 past the
            deferred-probe timeout) and will not retry on its own.
  NONE   -> something else is missing; send dmesg.

Reboot with the display entry still the default:

    ssh root@10.43.0.1 reboot
EOF


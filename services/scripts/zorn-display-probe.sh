#!/bin/sh
# Capture everything about the display stack, once per boot, to a file on disk.
#
# Why this exists: debugging the display over ssh does not work, because the same
# change that breaks the display also drags the machine down enough that the
# hotspot's uplink is unusable -- and that uplink is how the person driving this
# reaches the assistant. So the loop is not "ssh in and look", it is: boot once,
# let this run, reboot to Android, and read /var/log/zorn-display.txt over adb
# from the mounted arch partition. No network involved on either side.
#
# Runs 45 s in, which is past deferred_probe_timeout=30 -- so whatever the display
# stack was going to do, it has already done it.
exec >>/var/log/zorn-display.txt 2>&1

say() { echo; echo "### $*"; }

echo
echo "================================================================"
echo "boot at $(date -Is)   uptime $(cut -d' ' -f1 /proc/uptime)s"
echo "================================================================"
echo "kernel:  $(uname -r)"
echo "cmdline: $(cat /proc/cmdline)"

say "modules"
lsmod | awk 'NR==1 || /^(msm|panel_|dispcc_|drm)/ {print "  " $1 " used=" $3 " by=" $4}'

say "driver binding"
for n in af00000.clock-controller ae00000.display-subsystem 3d00000.gpu \
         1780000.interconnect 24100000.interconnect; do
	d=/sys/bus/platform/devices/$n
	[ -e "$d" ] || { echo "  $n  (no such device)"; continue; }
	echo "  $n  -> $(basename "$(readlink "$d/driver" 2>/dev/null)" 2>/dev/null || echo NONE)"
done
for n in ae01000.display-controller ae94000.dsi ae95000.phy; do
	for d in /sys/bus/platform/devices/*$n*; do
		[ -e "$d" ] || continue
		echo "  $(basename "$d")  -> $(basename "$(readlink "$d/driver" 2>/dev/null)" 2>/dev/null || echo NONE)"
	done
done

say "mipi-dsi devices (the panel only exists if the dsi host registered it)"
ls -l /sys/bus/mipi-dsi/devices/ 2>&1 | sed 's/^/  /'
for d in /sys/bus/mipi-dsi/devices/*; do
	[ -e "$d" ] || continue
	echo "  $(basename "$d") -> $(basename "$(readlink "$d/driver" 2>/dev/null)" 2>/dev/null || echo NONE)"
done

say "drm cards, connectors, modes"
for c in /sys/class/drm/card*; do
	[ -e "$c/dev" ] || continue
	echo "  $(basename "$c")  driver=$(basename "$(readlink -f "$c/device/driver" 2>/dev/null)")"
done
for s in /sys/class/drm/card*-*/status; do
	[ -e "$s" ] || continue
	c=$(dirname "$s")
	echo "  $(basename "$c")  status=$(cat "$s")  enabled=$(cat "$c/enabled" 2>/dev/null)"
	sed 's/^/      mode: /' "$c/modes" 2>/dev/null | head -6
done

say "backlight"
for b in /sys/class/backlight/*; do
	[ -e "$b" ] || { echo "  none"; break; }
	echo "  $(basename "$b")  brightness=$(cat "$b/brightness" 2>/dev/null)" \
	     "max=$(cat "$b/max_brightness" 2>/dev/null)" \
	     "power=$(cat "$b/bl_power" 2>/dev/null)"
done

say "still-deferred devices"
mountpoint -q /sys/kernel/debug || mount -t debugfs none /sys/kernel/debug 2>/dev/null
cat /sys/kernel/debug/devices_deferred 2>/dev/null | sed 's/^/  /' || echo "  (unavailable)"

say "smmu context faults (the mdss stream is cbfrsynra=0x1c00)"
echo "  total fault lines: $(dmesg | grep -c 'Unhandled context fault')"
dmesg | grep 'Unhandled context fault' | head -3 | sed 's/^/  /'

say "visible self-test: a 200-line colour bar at the top of the screen"
# The point: on an AMOLED an empty console and a dead panel look identical, and
# with loglevel=4 the console really is empty once msm takes over. Every boot
# should leave something on screen that answers "is the panel showing anything,
# and are the colours right" without needing anyone to run commands. Only the top
# 200 lines are touched, so whatever the console has is left alone.
for b in /sys/class/backlight/*; do
	[ -e "$b/max_brightness" ] || continue
	m=$(cat "$b/max_brightness")
	echo $((m * 3 / 5)) > "$b/brightness" 2>/dev/null
	echo "  $(basename "$b") brightness -> $(cat "$b/brightness") of $m"
done
if [ -e /dev/fb0 ]; then
	python3 - <<'PY' 2>&1 | sed 's/^/  /'
import mmap, os
W, H, BPP, BAR = 1440, 3200, 4, 200
# XR24 little-endian: byte order in memory is B, G, R, X
bands = [(b'\xff\xff\xff\x00', 'white'), (b'\x00\x00\xff\x00', 'red'),
         (b'\x00\xff\x00\x00', 'green'), (b'\xff\x00\x00\x00', 'blue')]
try:
    fd = os.open('/dev/fb0', os.O_RDWR)
    m = mmap.mmap(fd, W * H * BPP)
    for y in range(BAR):
        px, _ = bands[(y * len(bands)) // BAR]
        m[y*W*BPP:(y+1)*W*BPP] = px * W
    m.flush(); m.close(); os.close(fd)
    print("drew " + " / ".join(n for _, n in bands) + f" in the top {BAR} lines")
except Exception as e:
    print(f"could not draw: {e}")
PY
else
	echo "  no /dev/fb0"
fi

say "dmesg: everything touching the display stack"
dmesg | grep -iE 'msm|mdss|dpu|dsi|panel|o11|drm|disp_cc|dispcc|adreno|smmu|rcg|gdsc|vddd|reg-fixed' \
      | grep -viE 'GPIODBG|drm_mode_object|atomic_state|drm_atomic_(get|check|commit)|msm_serial' \
      | sed 's/^/  /'

say "dmesg: warnings and errors, whatever they are about"
dmesg --level=err,warn 2>/dev/null | grep -viE 'GPIODBG' | sed 's/^/  /' | head -80

echo
echo "### end of boot $(date -Is)"
sync

#!/bin/sh
# Verify the ENC_DF_CTRL value the DPU actually programmed at boot, since that is
# the only place it is programmed -- dpu_encoder_prep_dsc() does not rerun on DPMS,
# which is why sweeping these two knobs at runtime measured nothing at all.
v=$(dmesg | grep -oE 'ENC_DF_CTRL:0x100\] <= 0x[0-9A-Fa-f]+' | head -1 | grep -oE '0x[0-9A-Fa-f]+$')
[ -n "$v" ] || { echo "no ENC_DF_CTRL write logged (is msm.hw_log_mask=0x800 and drm.debug DRIVER on?)"; exit 1; }
python3 - "$v" <<'PY'
import sys
v = int(sys.argv[1], 16)
print(f"  ENC_DF_CTRL = {v:#010x}")
print(f"    initial_lines       = {v & 0xff}")
print(f"    video mode  bit9    = {(v >> 9) & 1}")
print(f"    full ICH prec bit12 = {(v >> 12) & 1}   (vendor sets this for bpc > 8 on DPU >= A00)")
print(f"    ob_max_addr         = {v >> 18}   (upstream 1199, vendor 2399 for RGB, 1 soft slice)")
PY
echo "  params in force: ob_max_addr=$(cat /sys/module/msm/parameters/dsc_ob_max_addr) full_ich_prec=$(cat /sys/module/msm/parameters/dsc_full_ich_prec)"

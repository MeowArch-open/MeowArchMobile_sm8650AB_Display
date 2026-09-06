#!/bin/sh
# Sweep the DSC "initial lines" the DPU programs. It is not in the PPS, so the
# panel cannot correct for it; get it wrong and the encoder's rate buffer slips
# once per slice row -- flat content is unaffected, detailed content bands.
#
# The computed value here is 2. dpu_hw_dsc.c (the DSC 1.1 block) adds one line in
# command mode; dpu_hw_dsc_1_2.c, which is the block SM8650 uses, does not. So 3
# is the value to look at first.
set -e
FB=/sys/class/graphics/fb0
P=/sys/module/msm/parameters/dsc_initial_lines
HOLD=${1:-14}
[ -e "$P" ] || { echo "no $P -- old msm still loaded, reboot first"; exit 1; }
for n in 2 3 4 5 1; do
	echo "--- initial_lines = $n ---"
	echo "$n" > "$P"
	echo 1 > "$FB/blank"; sleep 2; echo 0 > "$FB/blank"; sleep 2
	for b in /sys/class/backlight/*; do
		[ -e "$b/max_brightness" ] && cat "$b/max_brightness" > "$b/brightness" 2>/dev/null || true
	done
	printf '\033[2J\033[H' > /dev/tty1
	printf '======== DSC initial_lines = %s ========\n\n' "$n" > /dev/tty1
	dmesg | tail -100 > /dev/tty1
	sleep "$HOLD"
done
echo 0 > "$P"
echo "back to the computed value (2)"

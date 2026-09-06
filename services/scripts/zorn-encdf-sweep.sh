#!/bin/sh
# The two ENC_DF_CTRL differences between mainline and the vendor driver.
#
# Both only matter on detailed content, which is exactly how this panel fails:
#   output buffer max address  mainline 1199, vendor 2399 for RGB with 1 soft
#                              slice -- upstream halves it on the mere *presence*
#                              of the native 4:2:x capability, the vendor halves
#                              only on a separate REDUCED_OB_MAX capability. A
#                              half-size output FIFO overflows when the compressed
#                              data is large.
#   BIT(12) full ICH precision mainline never sets it; the vendor sets it for
#                              DPU >= A00 (ours is 0xa0000000) with bpc > 8 (10).
#                              ICH is dormant on flat fills, heavily used on text.
#
# Our boot-time register dump read ENC_DF_CTRL = 0x12BC0002:
#   initial_lines 2, video 0, ob_max_addr 1199, BIT(12) clear.
set -e
FB=/sys/class/graphics/fb0
P=/sys/module/msm/parameters
HOLD=${1:-18}
[ -e "$P/dsc_ob_max_addr" ] || { echo "old msm still loaded; reboot first"; exit 1; }

# fbcon must own the display for a blank/unblank to reach the hardware.
pkill -x Hyprland 2>/dev/null || true
pkill -x foot 2>/dev/null || true
sleep 3

show() {
	printf '\033[2J\033[H' > /dev/tty1
	printf '======== %s ========\n\n' "$1" > /dev/tty1
	dmesg | tail -100 > /dev/tty1
}
cycle() {
	echo 1 > "$FB/blank"; sleep 2; echo 0 > "$FB/blank"; sleep 2
	for b in /sys/class/backlight/*; do
		[ -e "$b/max_brightness" ] && cat "$b/max_brightness" > "$b/brightness" 2>/dev/null || true
	done
}
step() {
	echo "$2" > "$P/dsc_ob_max_addr"
	echo "$3" > "$P/dsc_full_ich_prec"
	echo "--- step $1: ob_max_addr=$2 full_ich_prec=$3 ---"
	cycle
	show "STEP $1   ob_max_addr=${2} (0=1199)   full_ich_prec=$3"
	sleep "$HOLD"
	echo "    ENC_DF_CTRL now: $(dmesg | grep -oE 'ENC_DF_CTRL:0x100\] <= 0x[0-9A-F]+' | tail -1)"
}

step 1 0    0     # upstream, the current broken baseline
step 2 2399 0     # vendor's output buffer size
step 3 0    1     # full ICH precision only
step 4 2399 1     # both, i.e. what the vendor programs

echo 0 > "$P/dsc_ob_max_addr"; echo 0 > "$P/dsc_full_ich_prec"
echo
echo "Back on upstream values. Which step was clean?"
echo "  step 4 clean  -> both fixes needed; make it permanent with"
echo "    options msm dsc_ob_max_addr=2399 dsc_full_ich_prec=1"

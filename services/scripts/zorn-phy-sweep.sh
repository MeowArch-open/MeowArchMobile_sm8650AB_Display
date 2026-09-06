#!/bin/sh
# Swap mainline's computed D-PHY timings for the vendor's measured set.
#
# Everything else has been ruled out: every DSC field (bpc, version, slice height,
# block prediction) makes it worse or identical, both link rates are identical,
# and forcing initial_lines 1..5 changes nothing. What is left is the physical
# layer -- and the symptom fits it: flat colour is perfect, dense text bands once
# per DSC slice row. Compressed detail is high-entropy and stresses the link;
# compressed flat colour does not. A single bit error ruins the slice it lands in.
#
# zorn's vendor device tree ships the measured values:
#   qcom,mdss-dsi-panel-phy-timings = [00 27 0A 0A 1B 19 0A 0B 0A 02 04 00 20 0F]
set -e
FB=/sys/class/graphics/fb0
P=/sys/module/msm/parameters/dsi_phy_timing
HOLD=${1:-20}
[ -e "$P" ] || { echo "no $P -- old msm still loaded, reboot first"; exit 1; }

VENDOR=0,39,10,10,27,25,10,11,10,2,4,0,32,15

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

echo "--- A: mainline computed timings (the baseline) ---"
echo 0 > "$P" 2>/dev/null || true
cycle; show "A: computed PHY timings"; sleep "$HOLD"

echo "--- B: the vendor's measured timings ---"
echo "$VENDOR" > "$P"
cycle; show "B: VENDOR PHY timings $VENDOR"; sleep "$HOLD"

echo "--- A again, to check the state does not drift ---"
echo 0 > "$P" 2>/dev/null || true
cycle; show "A again: computed PHY timings"; sleep "$HOLD"

echo
echo "Which of A / B / A-again was clean?"
echo "Currently on the computed timings. To keep the vendor set:"
echo "  echo 'options msm dsi_phy_timing=$VENDOR' >> /etc/modprobe.d/zorn-msm.conf"

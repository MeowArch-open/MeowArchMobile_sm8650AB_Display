#!/bin/sh
# slice_per_pkt: how many DSC slices go in one DSI packet.
#
# mainline states in dsi_update_dsc_timing() that it only supports 1 and has the
# "* slice_per_pkt" literally commented out. zorn's panel asks for 2
# (qcom,mdss-dsc-slice-per-pkt), and the vendor driver computes
#
#	bytes_per_pkt = bytes_in_slice * slice_per_pkt   -> 720 * 2 = 1440
#	pkt_per_line  = slice_per_intf / slice_per_pkt   -> 2   / 2 = 1
#
# so the panel expects one 1440-byte packet per line carrying both slices, and
# mainline sends two 720-byte packets. The byte count per line is identical, which
# is exactly why every clock, PHY and DSC-parameter change measured the same: the
# framing differs, not the volume, and a mis-framed DSC stream corrupts per slice.
set -e
FB=/sys/class/graphics/fb0
P=/sys/module/msm/parameters/dsi_dsc_slice_per_pkt
HOLD=${1:-20}
[ -e "$P" ] || { echo "no $P -- old msm still loaded, reboot first"; exit 1; }

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

for n in 1 2 1 2; do
	if [ "$n" = 1 ]; then w="two 720-byte packets per line (upstream)";
	else w="ONE 1440-byte packet per line (what the panel asks for)"; fi
	echo "--- slice_per_pkt=$n: $w ---"
	echo "$n" > "$P"
	cycle
	show "slice_per_pkt=$n  --  $w"
	sleep "$HOLD"
done

echo 1 > "$P"
echo
echo "Back on 1. Repeated 1,2,1,2 on purpose -- the panel has been seen to carry"
echo "state across reconfigurations, so a single A/B could mislead."
echo
echo "If 2 is clean, make it permanent:"
echo "  echo 'options msm dsi_dsc_slice_per_pkt=2' >> /etc/modprobe.d/zorn-msm.conf"

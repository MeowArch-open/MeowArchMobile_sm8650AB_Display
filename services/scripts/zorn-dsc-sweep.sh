#!/bin/sh
# Walk the DSC configuration space, showing dense text at each step.
#
# Why dense text: solid colour compresses to almost nothing and renders perfectly
# no matter what the DSC settings are. Only detailed content uses the rate budget,
# and only then does a wrong DSC parameter show up -- as periodic bands. So each
# step fills the console with real text and holds it, long enough to look at.
#
# Every knob here is re-applied by the panel driver's prepare(), and msm
# recomputes every derived DSC field in dsi_timing_setup() on the modeset that
# follows, so a DPMS off/on cycle is enough -- no reboot per value.
#
# Usage: ./zorn-dsc-sweep.sh [seconds-per-step]
#   Watch the screen. Each step prints its own label at the top of the text.
#   Note which step numbers look clean.
set -e

P=/sys/module/panel_xiaomi_o11_42_02_0a/parameters
M=/sys/module/msm/parameters
FB=/sys/class/graphics/fb0
TTY=/dev/tty1
HOLD=${1:-14}

[ -d "$P" ] || { echo "panel module has no parameters -- old module still loaded?"; exit 1; }

cycle() {
	echo 1 > "$FB/blank"
	sleep 2
	echo 0 > "$FB/blank"
	sleep 2
	for b in /sys/class/backlight/*; do
		[ -e "$b/max_brightness" ] || continue
		cat "$b/max_brightness" > "$b/brightness" 2>/dev/null || true
	done
}

show() {
	# Clear, label, then dense text -- the case that stripes.
	printf '\033[2J\033[H' > "$TTY"
	printf '======== STEP %s : %s ========\n\n' "$1" "$2" > "$TTY"
	dmesg | tail -100 > "$TTY"
}

step() {
	n=$1; shift
	label="$*"
	echo "--- step $n: $label ---"
	cycle
	show "$n" "$label"
	sleep "$HOLD"
}

set_panel() { echo "$2" > "$P/$1"; }
set_msm()   { [ -e "$M/$1" ] && echo "$2" > "$M/$1" || true; }

echo "=== baseline: what the vendor device tree says ==="
set_panel dsc_bpc 10; set_panel dsc_minor 2; set_panel dsc_slice_height 20
set_panel dsc_block_pred 1; set_msm dsi_dsc_uncompressed_bpp 0
step 1 "vendor values: bpc=10 dsc=1.2 slice_h=20 bp=1 clk=960M"

echo "=== the framebuffer is XR24, i.e. 8 bits per component ==="
set_panel dsc_bpc 8
step 2 "bpc=8   (dpu_hw_dsc_1_2 programs an 8-bit-input bit from this)"

echo "=== msm forces the DSC 1.1 pre-SCR RC table regardless of the PPS ==="
set_panel dsc_bpc 10; set_panel dsc_minor 1
step 3 "dsc=1.1 (matches the RC table msm actually uses)"

set_panel dsc_bpc 8; set_panel dsc_minor 1
step 4 "bpc=8 + dsc=1.1"

echo "=== block prediction off ==="
set_panel dsc_bpc 10; set_panel dsc_minor 2; set_panel dsc_block_pred 0
step 5 "block_pred=0"

echo "=== slice height: bands appear at slice boundaries ==="
set_panel dsc_block_pred 1; set_panel dsc_slice_height 40
step 6 "slice_h=40"

set_panel dsc_slice_height 80
step 7 "slice_h=80"

echo "=== and the link rate the vendor asks for, on top of the vendor values ==="
set_panel dsc_slice_height 20; set_msm dsi_dsc_uncompressed_bpp 30
step 8 "vendor values + 1.2 Gbps/lane"

set_panel dsc_bpc 8
step 9 "bpc=8 + 1.2 Gbps/lane"

echo "=== back to the vendor baseline ==="
set_panel dsc_bpc 10; set_msm dsi_dsc_uncompressed_bpp 0
cycle
printf '\033[2J\033[H' > "$TTY"
dmesg | tail -60 > "$TTY"
cat <<'EOF'

Done, back on the vendor baseline (step 1).

Tell me which step numbers looked clean. If none did, the striping is not in these
fields and the next suspect is the vendor's explicit PHY timings
(qcom,mdss-dsi-panel-phy-timings), which mainline computes for itself.
EOF

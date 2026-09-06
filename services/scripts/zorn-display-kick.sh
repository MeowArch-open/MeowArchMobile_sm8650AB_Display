#!/bin/sh
# Kick the panel once, early, by cycling DPMS.
#
# This is a workaround, not a fix, and it is worth being honest about why it
# exists. ABL brings this panel up itself and hands it to Linux initialised and
# scanning out (UEFI here is SimpleFbDxe, which only paints into ABL's
# framebuffer). From that state the panel refuses a fresh init and stays dark --
# but a DPMS off/on cycle brings it up correctly every single time.
#
# prepare() already forces a power cycle of its own that is, step for step, what
# unprepare() does: off-commands, reset asserted, rails dropped, wait, rails back.
# It is still not equivalent, and the remaining difference has not been found yet.
# Rather than leave the display unusable while that is chased, do the thing that
# works.
#
# Cost: the panel blanks and unblanks once, a few seconds into boot.
set -e

FB=

# Wait for *msm's* fbdev, not simpledrm's -- cycling simpledrm would do nothing
# useful, and the DRM connector appears a little before the framebuffer does.
# Polling on /sys/class/drm/card1-DSI-1 was too early by ~200 ms: the service ran
# at 3.386 s and found no fb0 at all.
for i in $(seq 1 120); do
	for f in /sys/class/graphics/fb*; do
		[ -e "$f/name" ] || continue
		case "$(cat "$f/name")" in
		msmdrmfb|msm*) FB=$f; break ;;
		esac
	done
	[ -n "$FB" ] && break
	sleep 0.5
done

if [ -z "$FB" ]; then
	echo "no msm framebuffer appeared in 60 s, nothing to kick" >&2
	exit 0
fi

echo "kicking $(basename "$FB") ($(cat "$FB/name")): dpms off, ${OFF_SECONDS:-2}s, dpms on"
echo 1 > "$FB/blank"
sleep "${OFF_SECONDS:-2}"
echo 0 > "$FB/blank"

# Stop the console blanking itself again: fb0 was found at blank=4
# (FB_BLANK_POWERDOWN) later in the boot, which looks exactly like the panel
# having died. 0 disables the timeout entirely.
setterm --blank 0 --powerdown 0 >/dev/tty1 2>/dev/null || \
	printf '\033[9;0]\033[14;0]' > /dev/tty1 2>/dev/null || true

# The vendor's on-sequence leaves DBV at 0, and backlight_device_register() does
# not push an initial level, so without this the panel is on but emitting nothing
# -- indistinguishable from dead on an AMOLED.
for b in /sys/class/backlight/*; do
	[ -e "$b/max_brightness" ] || continue
	m=$(cat "$b/max_brightness")
	echo $((m * 3 / 5)) > "$b/brightness" 2>/dev/null || true
	echo "  $(basename "$b") brightness -> $(cat "$b/brightness") of $m"
done

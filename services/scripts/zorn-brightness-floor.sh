#!/bin/sh
# Keep the panel backlight from being driven to (near) black. KDE's powerdevil
# and its brightness slider will happily write 0, which on this AMOLED is
# indistinguishable from the panel being dead. Poll the sysfs attribute and pull
# it back up to FLOOR whenever it drops below. Reading one sysfs int at a few Hz
# is negligible; this avoids pulling in inotify-tools just for one file.
B=/sys/class/backlight/ae94000.dsi.0
FLOOR=${BL_FLOOR:-165}
[ -e "$B/brightness" ] || exit 0
while :; do
	cur=$(cat "$B/brightness" 2>/dev/null || echo "$FLOOR")
	if [ "${cur:-0}" -lt "$FLOOR" ]; then
		echo "$FLOOR" > "$B/brightness" 2>/dev/null || true
	fi
	sleep 0.3
done

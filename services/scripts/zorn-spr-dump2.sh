#!/system/bin/sh
# Read everything about the SPR wiring from a working Android in one pass, so the
# next mainline attempt does not have to spend a reboot per guess.
#
# The first attempt enabled SPR_0 only and the DPU stopped completing frames
# ("failed wait_for_idle ... pp:0" every frame, not clearing on a DPMS cycle).
# Two candidate causes, and this dump settles both:
#
#   1. Is SPR_1 configured too? There are two layer mixers here (debugfs shows
#      mixer=101 101) and downstream applies DSPP features per-DSPP, so if
#      Android programs both blocks then leaving the second one blank while
#      telling the first "two mixers feed you" is exactly the kind of half-set-up
#      hardware that would stall the pipe.
#
#   2. Was anything in SPR_0 skipped? +0x94 read as 1 the first time and 0 the
#      second, so it was treated as a status register and left out. If it is
#      actually configuration, that omission alone could do it.
#
# Offsets are relative to mdss (0xae00000), which is what sde_off wants.
# Note sde_off rejects a leading 0x -- "6a400 100", not "0x6a400 0x100".
#
#   SPR_0  0x6a400   SPR_1  0x6b400        (dspp_base + spr_base, 0x1000 apart)
#   LM_0   0x45000   LM_1   0x46000        (mainline 0x44000/0x45000 + 0x1000)
#   CTL_0  0x16000                         (mainline 0x15000 + 0x1000)
#
# CTL_0 matters because CTL_DSPP_0_FLUSH is at CTL+0x13C and SPR is bit 8 there;
# seeing what Android leaves in the CTL flush registers tells us whether the
# flush path is the same one mainline already implements.

D=/sys/kernel/debug/dri/0/debug

dump() {
	printf '%s' "$1 $2" > $D/sde_off 2>/dev/null
	echo "### $3  (offset $1, $2 words-ish)"
	echo "    sde_off reads back: $(cat $D/sde_off 2>&1)"
	cat $D/sde_reg 2>&1
	echo
}

echo "### $(uname -a)"
dump 6a400 100 "SPR_0 -- the one already transcribed"
dump 6b400 100 "SPR_1 -- is the second mixer's block configured at all?"
dump 45000 40  "LM_0 -- OUT_SIZE tells us the per-mixer width"
dump 46000 40  "LM_1"
dump 16130 20  "CTL_0 +0x130.. -- CTL_DSPP_0_FLUSH is at +0x13C, SPR is bit 8"

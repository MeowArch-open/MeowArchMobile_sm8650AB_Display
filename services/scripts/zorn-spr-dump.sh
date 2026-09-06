#!/bin/sh
# Dump the DPU's SPR block from a running Android, where it is configured
# correctly, so mainline can be made to write the same values.
#
# Why read the hardware instead of deriving it: the SPR block is programmed from
# a drm_msm_spr_init_cfg payload that Android's display HAL builds out of
# Binaries/zorn/RawFiles/sprconfig_o11_42_02_0a_dsc_cmd.xml. The array-shaped
# fields map onto that XML unambiguously by size --
#
#     FilterCoeffs (16)          -> cfg16[16]  @ spr+0x34, 2x 11-bit per word
#     ColorPhaseOffsets RGBW (24)-> cfg17[24]  @ spr+0x24, 6x  5-bit per word
#     AdaptiveFilterCoeffs (5)   -> cfg14[5]
#     Pba (7)                    -> cfg18[7]   @ spr+0x7C
#
# -- but roughly ten scalar fields (cfg0..cfg13, the ones packed into the opmode
# word at spr+0x04) have no documentation and no comments in the vendor source.
# Guessing ten fields costs many reboots; reading the registers once costs one.
#
# Address arithmetic, from the stock Android device tree:
#
#     mdss                      0x0ae00000
#     qcom,sde-dspp-off         <0x55000 0x57000 0x59000 0x5b000>
#     qcom,sde-dspp-spr-off     <0x15400 0x14400 0x13400 0x12400>
#     qcom,sde-dspp-spr-size    0x200
#
# downstream computes base = dspp_off + spr_off, and those sum to 0x6A400,
# 0x6B400, 0x6C400, 0x6D400 -- consecutive, 0x1000 apart, which is the check that
# the arithmetic is right. demura-off does the same and lands at 0x6A600, exactly
# one 0x200 block after SPR_0. So:
#
#     SPR_0  0x0ae6a400   SPR_1  0x0ae6b400   SPR_2  0x0ae6c400   SPR_3  0x0ae6d400
#
# Only SPR_0 matters here: this panel is a single-DSI, single-DSPP setup.
#
# Run from the host with the phone in Android and adb root available:
#     ./zorn-spr-dump.sh > spr-android.txt
set -e

SPR0=0x0ae6a400
LEN=0x200

adb wait-for-device
adb root >/dev/null 2>&1 || true
adb wait-for-device

adb shell 'su -c "
  echo \"### $(uname -a)\"
  echo \"### SPR_0 at '"$SPR0"', '"$LEN"' bytes\"
  b=$(( '"$SPR0"' ))
  i=0
  while [ \$i -lt $(( '"$LEN"' )) ]; do
    line=\$(printf %08x \$(( b + i ))):
    j=0
    while [ \$j -lt 16 ]; do
      v=\$(devmem \$(( b + i + j )) 32 2>/dev/null || echo 0)
      line=\"\$line \$(printf %08x \$v)\"
      j=\$(( j + 4 ))
    done
    echo \"  \$line\"
    i=\$(( i + 16 ))
  done
"' 2>&1

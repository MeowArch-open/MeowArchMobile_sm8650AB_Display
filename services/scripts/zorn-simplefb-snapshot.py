#!/usr/bin/env python3
"""Snapshot the DPU exactly as ABL left it, from the simplefb boot path.

Why this path is the best reference available: with GRUB entry 0 the DT has mdss
disabled and `modprobe.blacklist=msm`, so Linux never touches the display
controller. Everything the DPU is doing was programmed by ABL -- and simplefb
renders colour correctly. Unlike the Android snapshot, this one is 8 bits per
component with no Dest Scaler, i.e. structurally identical to what mainline's
DRM path is trying to do. The only difference between "correct" and "wrong" here
is who configured the DPU, so a field-by-field diff isolates it.

Paints the reference bands first so the premise itself gets verified rather than
trusted, then reads. simplefb is literally CPU-writes-memory + DPU-scans-memory,
so writing /dev/fb0 shows up even though the console has stopped updating.
"""

import mmap
import os
import struct
import sys

FB = '/dev/fb0'
BANDS = [("pure blue", (0x00, 0x00, 0xff)),
         ("KDE accent", (0x3d, 0xae, 0xe9)),
         ("pure red", (0xff, 0x00, 0x00)),
         ("pure green", (0x00, 0xff, 0x00)),
         ("white", (0xff, 0xff, 0xff))]

# FBIOGET_VSCREENINFO -- the channel offsets tell us the byte order rather than
# assuming it matches the DRM path's XR24.
FBIOGET_VSCREENINFO = 0x4600


def screeninfo():
    import fcntl
    buf = bytearray(160)
    with open(FB, 'rb') as f:
        fcntl.ioctl(f, FBIOGET_VSCREENINFO, buf)
    v = struct.unpack('<40I', bytes(buf))
    # xres yres xres_v yres_v xoff yoff bpp grayscale, then r/g/b/a as
    # (offset, length, msb_right) triples
    return dict(xres=v[0], yres=v[1], bpp=v[6],
                r_off=v[8], g_off=v[11], b_off=v[14])


def paint(si, stride):
    w, h = si['xres'], si['yres']
    bh = h // len(BANDS)
    with open(FB, 'r+b') as fb:
        for i, (name, (r, g, b)) in enumerate(BANDS):
            px = (r << si['r_off']) | (g << si['g_off']) | (b << si['b_off'])
            row = px.to_bytes(4, 'little') * w
            if stride > 4 * w:
                row += bytes(stride - 4 * w)
            y1 = h if i == len(BANDS) - 1 else (i + 1) * bh
            fb.seek(i * bh * stride)
            fb.write(row * (y1 - i * bh))
        fb.flush()
    print(f"  painted {len(BANDS)} bands, {w}x{h}, "
          f"r@{si['r_off']} g@{si['g_off']} b@{si['b_off']}")


REGIONS = [
    ("MDSS_HW_VERSION", 0x0ae00000, 0x10),
    ("DSPP_TOP",        0x0ae01300, 0x80),
    ("CTL_0",           0x0ae16000, 0x40),
    ("LM_0",            0x0ae45000, 0x40),
    ("LM_1",            0x0ae46000, 0x40),
    ("SPR_0",           0x0ae6a400, 0x100),
    ("SPR_1",           0x0ae6b400, 0x100),
    ("DSC_0_enc0",      0x0ae81100, 0xa0),
    ("DSC_0_enc1",      0x0ae81200, 0xa0),
    ("DSI0_ctrl",       0x0ae94000, 0x100),
]


def dump():
    ps = os.sysconf('SC_PAGE_SIZE')
    fd = os.open('/dev/mem', os.O_RDONLY | os.O_SYNC)
    for name, base, size in REGIONS:
        off = base & ~(ps - 1)
        skew = base - off
        try:
            m = mmap.mmap(fd, skew + size + ps, mmap.MAP_SHARED,
                          mmap.PROT_READ, offset=off)
        except OSError as e:
            print(f"# {name} @ {base:#010x}: mmap failed: {e}")
            continue
        print(f"# {name} @ {base:#010x}")
        for row in range(0, size, 16):
            w = [int.from_bytes(m[skew+row+k:skew+row+k+4], 'little')
                 for k in (0, 4, 8, 12)]
            print("0x%08x: %s" % (base + row, " ".join("%08x" % x for x in w)))
        m.close()
    os.close(fd)


if __name__ == '__main__':
    si = screeninfo()
    stride = 4 * si['xres']
    try:
        stride = int(open('/sys/class/graphics/fb0/stride').read().strip())
    except OSError:
        pass
    print(f"  fb0: {si['xres']}x{si['yres']} {si['bpp']}bpp stride={stride} "
          f"name={open('/sys/class/graphics/fb0/name').read().strip()}")
    if '--no-paint' not in sys.argv:
        paint(si, stride)
    print()
    dump()


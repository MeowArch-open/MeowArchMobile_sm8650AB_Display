#!/usr/bin/env python3
"""Parse and compare DPU register snapshots.

Three captures exist now, and the third one is what makes this worth doing:

    android.txt   Android, full vendor display stack -- colour correct
    abl.txt       ABL, read from UEFI before the kernel runs -- colour correct
    mainline.txt  mainline drm/msm -- saturated red and blue wrong

A plain two-way diff against mainline turns up hundreds of differences, nearly
all of them incidental. What narrows it down is the pair of correct captures
agreeing with each other and disagreeing with mainline:

    ./dpu-snapshot.py suspects android.txt abl.txt mainline.txt

Registers the two correct captures disagree on cannot be the cause -- they vary
with mode or resolution while the colour stays right -- so `suspects` sets them
aside and counts them separately. A plain two-way comparison is still there:

    ./dpu-snapshot.py diff abl.txt mainline.txt

Where the captures come from
---------------------------
Android: the SDE debugfs (sde_off/sde_reg), then `convert` to rebase its
mdss-relative offsets onto absolute addresses. NOT /dev/mem -- Android has it
now, and reading the DPU through it reset the SoC on the first try. The kernel
enables the display power resource before a debugfs read; userspace cannot.

mainline: dpu-capture.c, which is /dev/mem and is safe on that side only.

ABL: DpuSnapshotDxe prints the registers to the UEFI DEBUG log twice per boot,
tagged DPU0 at load time and DPUS at ReadyToBoot. The log lands in the
Silicium_Log ring at 0xFEEF0000; read-uefi-log.py pulls it back out.

    ./read-uefi-log.py > abl.txt

Any argument may name a pass as `file:TAG`, default DPUS. That is how the two
UEFI passes get compared against each other, to see whether anything inside UEFI
touched the DPU:

    ./dpu-snapshot.py diff abl.txt:DPU0 abl.txt:DPUS

Every format involved parses -- the UEFI log's tagged lines, dpu-capture's
output, and the older `0x0ae...:` dumps -- so nothing has to be converted first.
"""

import argparse
import re
import sys

# Labels only. The addresses that decide what gets read live in dpu-capture.c and
# in mDpuRegions[] in DpuSnapshot.c; this table just names the regions in the
# output, so a region missing here shows up as "?" rather than making a diff
# wrong.
REGIONS = [
    ("MDSS",         0x0AE00000, 0x010),
    ("MDP_TOP",      0x0AE01000, 0x040),
    ("DSPP_TOP",     0x0AE01300, 0x080),
    ("CTL_0",        0x0AE16000, 0x060),
    ("CTL_1",        0x0AE17000, 0x060),
    ("LM_0",         0x0AE45000, 0x040),
    ("LM_1",         0x0AE46000, 0x040),
    ("DSPP_0",       0x0AE55000, 0x080),
    ("DSPP_0_PA",    0x0AE55800, 0x200),
    ("DSPP_0_GAMUT", 0x0AE56000, 0x040),
    ("DSPP_0_PCC",   0x0AE56700, 0x150),
    ("DSPP_1",       0x0AE57000, 0x080),
    ("DSPP_1_PA",    0x0AE57800, 0x200),
    ("DSPP_1_GAMUT", 0x0AE58000, 0x040),
    ("DSPP_1_PCC",   0x0AE58700, 0x150),
    ("SPR_0",        0x0AE6A400, 0x100),
    ("SPR_1",        0x0AE6B400, 0x100),
    # CDM does RGB -> YCbCr and the chroma downsample between the layer mixer
    # and DSC. Reading Android's copy settles the packer mode, the downsample
    # phase and the CSC matrix all at once, instead of guessing them one reboot
    # at a time. Base is catalog 0x79200 relative to mdp = mdss + 0x1000; the
    # block is 0x228 long, so stop at 0x220 -- sde_reg refuses a read that would
    # run past a block's end.
    ("CDM_0",        0x0AE7A200, 0x220),
    ("DSC_0_ENC0",   0x0AE81100, 0x0A0),
    ("DSC_0_ENC1",   0x0AE81200, 0x0A0),
    ("DSC_0_CTL",    0x0AE81F00, 0x040),
    ("DSI0_CTRL",    0x0AE94000, 0x100),
]


def label(addr):
    """Region name and offset for an address, for the diff output."""
    for name, base, size in REGIONS:
        if base <= addr < base + size:
            return name, addr - base
    return "?", 0


# "DPUS 0ae55800: 00000000 ..." from the UEFI log, "0x0ae55800: ..." from the
# older dumps, and this script's own output all reduce to the same thing. An
# untagged line belongs to whichever pass is being read: only the UEFI log
# carries two passes in one file.
LINE_RE = re.compile(
    r"^(?:(DPU[0-9A-Z])\s+)?(?:0x)?([0-9a-fA-F]{8})\s*:\s*"
    r"((?:[0-9a-fA-F]{8}\s*){1,4})\s*$"
)
SUM_RE = re.compile(r"(DPU[0-9A-Z])\s+END sum=0x([0-9a-fA-F]{8})")
SPEC_RE = re.compile(r"^(.*):(DPU[0-9A-Z])$")
DEFAULT_TAG = "DPUS"


def parse(text, tag):
    """Flat {address: value} for one pass. Ignores region headers -- the static
    table above labels addresses, so the two formats' headers never have to
    agree."""
    regs = {}
    claimed_sum = None
    for line in text.splitlines():
        m = SUM_RE.search(line)
        if m:
            if m.group(1) == tag:
                claimed_sum = int(m.group(2), 16)
            continue
        m = LINE_RE.match(line.strip())
        if not m or (m.group(1) is not None and m.group(1) != tag):
            continue
        addr = int(m.group(2), 16)
        for i, word in enumerate(m.group(3).split()):
            regs[addr + 4 * i] = int(word, 16)
    return regs, claimed_sum


def read_file(spec):
    """`spec` is a path, optionally `path:TAG` to pick one pass out of a log."""
    m = SPEC_RE.match(spec)
    path, tag = (m.group(1), m.group(2)) if m else (spec, DEFAULT_TAG)

    with open(path, encoding="utf-8", errors="replace") as f:
        regs, claimed = parse(f.read(), tag)
    if not regs:
        sys.exit(f"{path}: no {tag} register lines found")
    if claimed is not None:
        actual = sum(regs.values()) & 0xFFFFFFFF
        if actual != claimed:
            print(f"# {path}:{tag}: sum mismatch -- the log says {claimed:#010x}, "
                  f"the {len(regs)} words present add to {actual:#010x}. The ring "
                  f"buffer probably wrapped over part of this pass.",
                  file=sys.stderr)
    return regs


def suspects(good_specs, bad_spec):
    """Registers that both correct captures agree on and the broken one does not.

    A register the two correct captures disagree on cannot be what breaks the
    colour: the colour is right in both, so whatever differs there is free to
    vary. Setting those aside is the whole filter."""
    goods = [(spec, read_file(spec)) for spec in good_specs]
    bad = read_file(bad_spec)

    shared = set(bad)
    for _, regs in goods:
        shared &= set(regs)
    shared = sorted(shared)
    if not shared:
        sys.exit("the captures have no addresses in common")

    first = goods[0][1]
    agreed = [a for a in shared if all(regs[a] == first[a]
                                       for _, regs in goods[1:])]
    hits = [a for a in agreed if first[a] != bad[a]]

    print(f"# {' + '.join(spec for spec, _ in goods)} vs {bad_spec}")
    print(f"# {len(shared)} words in common; the correct captures disagree on "
          f"{len(shared) - len(agreed)} of them, set aside; {len(hits)} of the "
          f"remaining {len(agreed)} differ from {bad_spec}")

    for name, base, size in REGIONS:
        rows = [a for a in hits if base <= a < base + size]
        if not rows:
            continue
        print(f"\n{name} @ {base:#010x}  {len(rows)} suspect words")
        for a in rows:
            print(f"  +0x{a - base:03x}  correct={first[a]:08x}  "
                  f"broken={bad[a]:08x}")

    if not hits:
        print("\n# nothing survives the filter: every register the two correct "
              "captures agree on is also what mainline has")


def diff(left_path, right_path, show_same):
    left, right = read_file(left_path), read_file(right_path)
    shared = sorted(set(left) & set(right))
    if not shared:
        sys.exit("the two files have no addresses in common")

    print(f"# {left_path} vs {right_path}: {len(shared)} words in common, "
          f"{len(set(left) ^ set(right))} covered by only one side")

    changed = 0
    for name, base, size in REGIONS:
        rows = [a for a in shared if base <= a < base + size]
        if not rows:
            continue
        bad = [a for a in rows if left[a] != right[a]]
        changed += len(bad)
        if not bad:
            if show_same:
                print(f"\n{name}: identical ({len(rows)} words)")
            continue
        print(f"\n{name} @ {base:#010x}  {len(bad)}/{len(rows)} words differ")
        for a in bad:
            print(f"  +0x{a - base:03x}  {left[a]:08x} -> {right[a]:08x}")

    orphans = [a for a in shared if label(a)[0] == "?"]
    if orphans:
        print(f"\n# {len(orphans)} words outside every known region, e.g. "
              f"{orphans[0]:#010x} -- REGIONS is out of step with the capture")

    print(f"\n# {changed} of {len(shared)} shared words differ")


def convert(path, base, tag):
    """Rebase a downstream sde_reg dump onto absolute addresses.

    sde_off/sde_reg speak offsets relative to mdss, so a raw capture has to be
    rebased before it can be compared with the /dev/mem and UEFI captures. It
    also has gaps: the SDE debug blocks reject any offset that is not inside a
    registered block, and reject a read that would run past one's end. DSPP base
    itself (0x55000) is rejected while its PA sub-block (0x55800) is fine, which
    is what the REJECTED markers in a raw capture are."""
    out = []
    total = 0
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            m = LINE_RE.match(line.strip())
            if not m:
                continue
            addr = base + int(m.group(2), 16)
            words = [int(w, 16) for w in m.group(3).split()]
            total += sum(words)
            out.append("%s %08x: %s" %
                       (tag, addr, " ".join("%08x" % w for w in words)))

    if not out:
        sys.exit(f"{path}: no register lines found")

    print(f"{tag} BEGIN v1 rebased={path} base=0x{base:08x} lines={len(out)}")
    print("\n".join(out))
    print(f"{tag} END sum=0x{total & 0xFFFFFFFF:08x}")


def main():
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)

    sus = sub.add_parser("suspects",
                         help="what the correct captures agree on and the "
                              "broken one does not")
    sus.add_argument("good", nargs="+", help="captures with correct colour")
    sus.add_argument("bad", help="the capture with wrong colour")

    dif = sub.add_parser("diff", help="compare two captures")
    dif.add_argument("left", help="path, or path:TAG to pick one pass (DPU0/DPUS)")
    dif.add_argument("right", help="same")
    dif.add_argument("--all", action="store_true",
                     help="also name the regions that match")

    con = sub.add_parser("convert",
                         help="rebase an sde_reg dump onto absolute addresses")
    con.add_argument("path")
    con.add_argument("--base", default="0x0ae00000",
                     help="what the dump's offsets are relative to (default mdss)")
    con.add_argument("--tag", default=DEFAULT_TAG)

    args = ap.parse_args()
    if args.cmd == "suspects":
        suspects(args.good, args.bad)
    elif args.cmd == "convert":
        convert(args.path, int(args.base, 0), args.tag)
    else:
        diff(args.left, args.right, args.all)


if __name__ == "__main__":
    main()




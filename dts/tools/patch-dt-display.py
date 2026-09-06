#!/usr/bin/env python3
"""Turn on the real display pipeline in zorn's booted device tree.

The DT that GRUB loads (ESP:/dtb/zorn.dtb) comes from upstream sm8650-mtp.dts, so
it already contains the whole MDSS block -- dpu, both dsi controllers, both phys,
dispcc -- wired up and merely status = "disabled", plus the MTP's own
visionox,vtdr6130 panel node whose reset pin and TE pin happen to be exactly the
ones zorn uses. Five things have to change:

  1. display-subsystem@ae00000   disabled -> okay
  2. dsi@ae94000                 disabled -> okay   (vdda-supply already set)
  3. phy@ae95000                 disabled -> okay   (vdds-supply already set)
  4. panel@0                     visionox,vtdr6130 -> xiaomi,o11-42-02-0a, with
                                 zorn's own three supplies, keeping the MTP's
                                 pinctrl (gpio133 as gpio, gpio86 as mdp_vsync)
  5. tlmm gpio-reserved-ranges   narrowed so that gpio 86, 126 and 133 become
                                 usable -- see below

Whoever built this DT added

    gpio-reserved-ranges = <8 8>, <18 76>, <97 113>

which marks 8-15, 18-93 and 97-209 unusable: that is nearly the whole chip, and
it includes all three display pins. Every gpiod_get() on them returns -EINVAL,
which is exactly what "reg-fixed-voltage panel-vddd-regulator: error -EINVAL:
can't get GPIO" was. Upstream reserves only <32 8>, <74 1> on every sm8650 board,
and the stock Android tree reserves nothing at all, so the wide ranges are a local
choice, not a hardware constraint -- upstream sm8650-mtp.dts even drives gpio133
as its own panel reset. Rather than revert to the upstream pair, which would
un-reserve ~180 pins whose original reason for being reserved is unknown, this
script punches exactly three holes and leaves everything else as it was.

Works on the decompiled tree because the source of the booted dtb is not on this
host: Resources/DTBs/zorn.dts and work/zorn.dts are both the decompiled *stock
Android* tree, not this one. Decompile, edit, recompile:

    ./patch-dt-display.py                       # esp.img.orig -> zorn-display.dtb
    ./patch-dt-display.py --dtb some-other.dtb

Then flash it next to a kernel that has the panel driver:

    GRUB_DEFAULT=1 ./make-esp.sh knat/Image "" zorn-display.dtb
    fastboot flash esp esp-new.img
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent

RESET_GPIO = 133   # qcom,platform-reset-gpio = <&tlmm 133 0>, active low
TE_GPIO = 86       # qcom,platform-te-gpio = <&tlmm 86 0>, muxed as mdp_vsync
VDDD_GPIO = 126    # display_panel_vddd: gpio = <&tlmm 126 0>, enable-active-high
VDDD_UV = 1070000  # regulator-{min,max}-microvolt = <0x1053b0>

# Pins to make usable again. Everything else stays reserved exactly as it was.
FREE_GPIOS = (TE_GPIO, VDDD_GPIO, RESET_GPIO)


def sh(*cmd: str, **kw) -> subprocess.CompletedProcess:
    return subprocess.run(cmd, check=True, capture_output=True, **kw)


def node_span(s: str, header: str, start: int = 0) -> tuple[int, int]:
    """Byte range of the node whose header is `header`, braces balanced."""
    i = s.index(header, start)
    j = i + len(header)
    depth = 1
    while depth and j < len(s):
        if s[j] == '{':
            depth += 1
        elif s[j] == '}':
            depth -= 1
        j += 1
    if depth:
        sys.exit(f"unbalanced braces looking for {header!r}")
    return i, j


def own_props(s: str, i: int, j: int) -> str:
    """The node's own properties: everything before its first child node."""
    body = s[i:j]
    cut = re.search(r'\n\t+[\w@,.+-]+ \{', body)
    return body[:cut.start()] if cut else body


def enclosing_node(s: str, pos: int) -> tuple[str, int, int]:
    """Name and span of the innermost node containing byte `pos`."""
    depth = 0
    i = pos
    while i > 0:
        i -= 1
        if s[i] == '}':
            depth += 1
        elif s[i] == '{':
            if depth == 0:
                name = s[s.rfind('\n', 0, i) + 1:i].strip()
                return name, i, node_span(s, name + ' {', max(0, i - len(name) - 2))[1]
            depth -= 1
    sys.exit("could not find an enclosing node")


def phandle_owner(s: str, ph: str) -> str:
    """Which node actually owns phandle `ph`. The whole point of this function is
    that a byte-window search around a property gets this wrong: it will happily
    return a neighbouring node's phandle, which is how vddio once ended up
    pointing at bob2."""
    m = re.search(r'phandle = <' + re.escape(ph) + r'>;', s)
    if not m:
        return 'NOT FOUND'
    return enclosing_node(s, m.start())[0]


def phandle_of(s: str, i: int, j: int) -> str | None:
    m = re.search(r'phandle = <(0x[0-9a-f]+)>;', own_props(s, i, j))
    return m.group(1) if m else None


def regulator_phandle(s: str, regulator_name: str) -> str:
    """Phandle of the node whose regulator-name is `regulator_name`, found by
    walking out to that node and reading its own phandle property."""
    m = re.search(r'regulator-name = "' + re.escape(regulator_name) + r'"', s)
    if not m:
        sys.exit(f"no regulator named {regulator_name}")
    name, i, j = enclosing_node(s, m.start())
    ph = phandle_of(s, i, j)
    if not ph:
        sys.exit(f"{regulator_name} (node {name}) has no phandle")
    return ph


def node_phandle(s: str, header: str) -> str:
    i, j = node_span(s, header)
    ph = phandle_of(s, i, j)
    if not ph:
        sys.exit(f"{header} has no phandle")
    return ph


def free_phandle(s: str) -> int:
    return max(int(x, 16) for x in re.findall(r'phandle = <(0x[0-9a-f]+)>;', s)) + 1


def enable(s: str, header: str, what: str) -> str:
    """Flip one node's own status to okay, leaving its children alone."""
    i, j = node_span(s, header)
    head = own_props(s, i, j)
    rest = s[i:j][len(head):]
    if 'status = "disabled"' not in head:
        print(f"  {what}: already "
              f"{'okay' if 'status = \"okay\"' in head else 'without a status'}")
        return s
    head = head.replace('status = "disabled"', 'status = "okay"', 1)
    print(f"  {what}: disabled -> okay")
    return s[:i] + head + rest + s[j:]


def reserved_ranges(head: str):
    """(match, [cells]) for gpio-reserved-ranges, in either the single-group form
    dtc emits (<a b c d>) or the multi-group form this script writes
    (<a b>, <c d>)."""
    m = re.search(r'gpio-reserved-ranges = ([^;]*);', head)
    if not m:
        return None, []
    return m, [int(x, 0) for x in re.findall(r'0x[0-9a-fA-F]+|\d+', m.group(1))]


def reserved_set(head: str) -> set:
    _, cells = reserved_ranges(head)
    out = set()
    for k in range(0, len(cells) - 1, 2):
        out.update(range(cells[k], cells[k] + cells[k + 1]))
    return out


def free_reserved_gpios(s: str) -> str:
    """Punch holes in tlmm's gpio-reserved-ranges for the display pins."""
    i, j = node_span(s, 'pinctrl@f100000 {')
    head = own_props(s, i, j)
    m, cells = reserved_ranges(head)
    if not m:
        print("  gpio-reserved-ranges: none, nothing to free")
        return s
    if len(cells) % 2:
        sys.exit("gpio-reserved-ranges has an odd number of cells")

    reserved = reserved_set(head)
    still_blocked = [g for g in FREE_GPIOS if g in reserved]
    if not still_blocked:
        print("  gpio-reserved-ranges: display pins already usable")
        return s
    reserved -= set(FREE_GPIOS)

    # Re-emit as runs, so the result stays a minimal list of ranges.
    runs = []
    for g in sorted(reserved):
        if runs and g == runs[-1][0] + runs[-1][1]:
            runs[-1][1] += 1
        else:
            runs.append([g, 1])

    new = ', '.join(f'<{a:#x} {n:#x}>' for a, n in runs)
    head_new = head[:m.start()] + f'gpio-reserved-ranges = {new};' + head[m.end():]
    print(f"  gpio-reserved-ranges: freed {', '.join(str(g) for g in still_blocked)}")
    print(f"    was {' '.join(str(c) for c in cells)}")
    print(f"    now {' '.join(f'{a} {n}' for a, n in runs)}")
    return s[:i] + head_new + s[i:j][len(head):] + s[j:]


def add_vddd(s: str, tlmm: str, ph: int) -> str:
    """Xiaomi's display_panel_vddd, as a mainline regulator-fixed."""
    if 'panel-vddd-regulator' in s:
        print("  vddd regulator: already present")
        return s
    node = f'''
	panel-vddd-regulator {{
		compatible = "regulator-fixed";
		regulator-name = "panel_vddd";
		regulator-min-microvolt = <{VDDD_UV:#x}>;
		regulator-max-microvolt = <{VDDD_UV:#x}>;
		gpios = <{tlmm} {VDDD_GPIO:#x} 0x00>;
		enable-active-high;
		regulator-boot-on;
		phandle = <{ph:#x}>;
	}};
'''
    m = list(re.finditer(r'\n\};\s*$', s))
    if not m:
        sys.exit("could not find the end of the root node")
    at = m[-1].start()
    print(f"  vddd regulator: added panel-vddd-regulator "
          f"({VDDD_UV/1e6:.2f} V, tlmm {VDDD_GPIO}, phandle {ph:#x})")
    return s[:at] + node + s[at:]


def swap_panel(s: str, tlmm: str, vddd_ph: int) -> str:
    """Replace the MTP's vtdr6130 panel node with zorn's o11, keeping everything
    about it that is already right: the pinctrl that muxes gpio133 as gpio and
    gpio86 as mdp_vsync, and the port/endpoint that ties it to dsi0."""
    i, j = node_span(s, 'panel@0 {')
    old = s[i:j]
    if 'visionox,vtdr6130' not in old:
        sys.exit("panel@0 is not the MTP's vtdr6130; refusing to guess")

    ep = re.search(r'remote-endpoint = <(0x[0-9a-f]+)>;\s*\n\s*phandle = <(0x[0-9a-f]+)>;',
                   old)
    if not ep:
        sys.exit("could not find panel@0's endpoint phandles")
    dsi_out, panel_in = ep.group(1), ep.group(2)

    # Carry the pinctrl over verbatim -- the MTP's disp0_reset_n / mdp_vsync
    # states already name exactly the pins zorn's panel uses.
    pinctrl = '\n'.join('\t\t\t\t\t' + l.strip() for l in old.splitlines()
                        if re.match(r'\s*pinctrl-(0|1|names) =', l))
    if not pinctrl:
        sys.exit("panel@0 has no pinctrl properties to carry over")

    vddio = regulator_phandle(s, 'vreg_l12b_1p8')
    vci = regulator_phandle(s, 'vreg_l13b_3p0')

    new = f'''panel@0 {{
					compatible = "xiaomi,o11-42-02-0a";
					reg = <0x00>;
					reset-gpios = <{tlmm} {RESET_GPIO:#x} 0x01>;
					vddio-supply = <{vddio}>;
					vci-supply = <{vci}>;
					vddd-supply = <{vddd_ph:#x}>;
{pinctrl}

					port {{

						endpoint {{
							remote-endpoint = <{dsi_out}>;
							phandle = <{panel_in}>;
						}};
					}};
				}}'''
    print("  panel@0: visionox,vtdr6130 -> xiaomi,o11-42-02-0a")
    print(f"           reset=tlmm {RESET_GPIO} active-low, pinctrl carried over")
    return s[:i] + new + s[j:], {'vddio': vddio, 'vci': vci}


def verify(s: str, tlmm: str, supplies: dict, vddd_ph: int) -> None:
    """Resolve every phandle the new nodes reference and check it owns the node it
    is supposed to. This exists because the first version of this script found
    phandles with a byte-window search and silently wired vddio to bob2 and vci to
    ldo5 -- both wrong rails, and nothing downstream would have complained."""
    expect = {
        tlmm: 'pinctrl@f100000',
        supplies['vddio']: 'ldo12',
        supplies['vci']: 'ldo13',
        f'{vddd_ph:#x}': 'panel-vddd-regulator',
    }
    print("=== verifying phandles ===")
    bad = False
    for ph, want in expect.items():
        got = phandle_owner(s, ph)
        ok = got == want
        bad |= not ok
        print(f"  {ph:8s} -> {got:26s} {'ok' if ok else f'EXPECTED {want}'}")
    if bad:
        sys.exit("refusing to write a tree with phandles pointing at the wrong nodes")

    # And that the pins the panel needs are no longer reserved.
    i, j = node_span(s, 'pinctrl@f100000 {')
    reserved = reserved_set(own_props(s, i, j))
    for g in FREE_GPIOS:
        blocked = g in reserved
        print(f"  gpio {g:<4} {'STILL RESERVED' if blocked else 'usable'}")
        if blocked:
            sys.exit(f"gpio {g} is still reserved; gpiod_get() would return -EINVAL")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument('--dtb', help='input dtb (default: pull /dtb/zorn.dtb out of esp.img.orig)')
    ap.add_argument('--out', default='zorn-display.dtb')
    args = ap.parse_args()

    src = args.dtb
    if not src:
        src = str(HERE / 'booted-zorn-in.dtb')
        print("=== pulling /dtb/zorn.dtb out of esp.img.orig ===")
        sh('mcopy', '-o', '-i', str(HERE / 'esp.img.orig'), '::/dtb/zorn.dtb', src,
           env={'MTOOLS_SKIP_CHECK': '1', 'PATH': '/usr/bin:/bin'})

    print(f"=== decompiling {src} ===")
    dts = sh('dtc', '-I', 'dtb', '-O', 'dts', src).stdout.decode()

    print("=== patching ===")
    tlmm = node_phandle(dts, 'pinctrl@f100000 {')
    vddd_ph = free_phandle(dts)

    dts = enable(dts, 'display-subsystem@ae00000 {', 'mdss')
    dts = enable(dts, 'dsi@ae94000 {', 'dsi0')
    dts = enable(dts, 'phy@ae95000 {', 'dsi0 phy')
    dts = free_reserved_gpios(dts)
    dts = add_vddd(dts, tlmm, vddd_ph)
    dts, supplies = swap_panel(dts, tlmm, vddd_ph)

    verify(dts, tlmm, supplies, vddd_ph)

    out_dts = Path(args.out).with_suffix('.dts')
    out_dts.write_text(dts)

    print(f"=== recompiling -> {args.out} ===")
    r = subprocess.run(['dtc', '-I', 'dts', '-O', 'dtb', '-o', args.out, str(out_dts)],
                       capture_output=True)
    if r.returncode:
        sys.exit(r.stderr.decode())

    print(f"\nWrote {args.out} ({Path(args.out).stat().st_size} bytes) and {out_dts}")
    print("\nNext:")
    print(f"  GRUB_DEFAULT=1 ./make-esp.sh knat/Image \"\" {args.out}")
    print("  fastboot flash esp esp-new.img")
    print("\nThe kernel needs the panel module present *before* msm binds -- see")
    print("install-display.sh, which handles the module and the blacklist.")


if __name__ == '__main__':
    main()



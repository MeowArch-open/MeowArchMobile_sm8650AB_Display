/*
 * DO NOT RUN THIS. Kept for the register map, not as a tool.
 *
 * It has taken the SoC down twice in one day (2026-09-03): once on Android and
 * once on mainline. Both times the very first read was the fatal one, which is
 * why the MDSS_HW_VERSION gate below cannot save it -- that read IS the
 * dangerous one.
 *
 * It cannot be made safe from userspace. This panel is command mode, so the DPU
 * idle-collapses whenever nothing is drawing, and reading a collapsed block is
 * an unclocked access that TZ answers with a hard reset: no panic, no pstore
 * record, bootreason just says "reboot". --poke-fb does not fix it either -- the
 * damage flush behind /dev/fb0 is asynchronous, so the write returns well before
 * the DPU is actually up and the read that follows lands in the gap.
 *
 * Read DPU registers these ways instead:
 *
 *   Android    the SDE debugfs (sde_off / sde_reg). The kernel enables the
 *              display power resource before it reads, which is why the same
 *              addresses have gone through it dozens of times without incident.
 *              Rebase with: dpu-snapshot.py convert raw.txt > android.txt
 *
 *   mainline   there is no equivalent debugfs, so do not read -- print from the
 *              kernel. dpu_hw_dsc_1_2_config() now pr_info()s the value it
 *              writes to DSC_MAIN_CONF, which is better than reading it back:
 *              it lands in dmesg, costs nothing, and shows what the driver
 *              actually intended.
 *
 *   UEFI       DpuSnapshotDxe. No runtime PM there, and the DPU is up for the
 *              whole of DXE.
 */

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define MDSS_HW_VERSION          0x0ae00000u
#define MDSS_HW_VERSION_EXPECTED 0xa0000000u

struct region {
	const char *name;
	uint32_t    base;
	uint32_t    len;
};

/*
 * Keep in step with mDpuRegions[] in
 * Silicon/Silicium/SiliciumPkg/Drivers/DpuSnapshotDxe/DpuSnapshot.c. That table
 * and this one are the only two places the addresses are stated; the REGIONS
 * list in dpu-snapshot.py only labels output and cannot make a diff wrong.
 *
 * The DSPP colour blocks are the point of the exercise. mainline drm/msm
 * programs none of PA HSIC (+0x800), SIXZONE (+0x900), GAMUT (+0x1000) or PCC
 * (+0x1700), so whatever the vendor stack puts there is invisible from the
 * mainline side. dspp_0/dspp_1 are at 0x54000/0x56000 relative to
 * mdp = mdss + 0x1000.
 *
 * Resolution does not have to match between the two sides for these to be
 * comparable: they are per-pixel colour transforms, so the coefficients mean the
 * same thing whether Android is running 1080x2400 or mainline 1440x3200.
 */
static const struct region regions[] = {
	{ "MDSS",          0x0ae00000, 0x010 },
	{ "MDP_TOP",       0x0ae01000, 0x040 },
	{ "DSPP_TOP",      0x0ae01300, 0x080 },
	{ "CTL_0",         0x0ae16000, 0x060 },
	{ "CTL_1",         0x0ae17000, 0x060 },
	{ "LM_0",          0x0ae45000, 0x040 },
	{ "LM_1",          0x0ae46000, 0x040 },
	{ "DSPP_0",        0x0ae55000, 0x080 },
	{ "DSPP_0_PA",     0x0ae55800, 0x200 },
	{ "DSPP_0_GAMUT",  0x0ae56000, 0x040 },
	{ "DSPP_0_PCC",    0x0ae56700, 0x150 },
	{ "DSPP_1",        0x0ae57000, 0x080 },
	{ "DSPP_1_PA",     0x0ae57800, 0x200 },
	{ "DSPP_1_GAMUT",  0x0ae58000, 0x040 },
	{ "DSPP_1_PCC",    0x0ae58700, 0x150 },
	{ "SPR_0",         0x0ae6a400, 0x100 },
	{ "SPR_1",         0x0ae6b400, 0x100 },
	{ "DSC_0_ENC0",    0x0ae81100, 0x0a0 },
	{ "DSC_0_ENC1",    0x0ae81200, 0x0a0 },
	{ "DSC_0_CTL",     0x0ae81f00, 0x040 },
	{ "DSI0_CTRL",     0x0ae94000, 0x100 },
};

#define NREGIONS (sizeof (regions) / sizeof (regions[0]))

static long page_size;

struct window {
	void                    *addr;
	size_t                   span;
	const volatile uint32_t *regs;
};

/* mmap /dev/mem wants a page-aligned offset; the register bases are not. */
static int window_open(struct window *w, int fd, uint32_t base, uint32_t len)
{
	uint32_t skew = base & (uint32_t)(page_size - 1);

	w->span = ((size_t)skew + len + (size_t)page_size - 1) &
		  ~((size_t)page_size - 1);
	w->addr = mmap(NULL, w->span, PROT_READ, MAP_SHARED, fd,
		       (off_t)(base - skew));
	if (w->addr == MAP_FAILED)
		return -1;

	w->regs = (const volatile uint32_t *)((const char *)w->addr + skew);
	return 0;
}

static void window_close(struct window *w)
{
	munmap(w->addr, w->span);
}

/*
 * Write the first pixel back over itself: a damage event with no visible effect,
 * which is enough to bring the DPU out of idle collapse. Linux only -- Android
 * has no fbdev node, so there a touch event is the way.
 */
static void poke_fb(void)
{
	unsigned char pixel[4];
	int fd = open("/dev/fb0", O_RDWR);

	if (fd < 0) {
		fprintf(stderr, "# /dev/fb0: %s -- on Android, generate a touch "
				"event instead\n", strerror(errno));
		return;
	}

	if (read(fd, pixel, sizeof pixel) == (ssize_t)sizeof pixel &&
	    lseek(fd, 0, SEEK_SET) == 0) {
		if (write(fd, pixel, sizeof pixel) < 0)
			fprintf(stderr, "# /dev/fb0: write: %s\n", strerror(errno));
	}

	close(fd);
}

int main(int argc, char **argv)
{
	const char *tag = "DPUS";
	int do_poke = 0, fd, a;
	uint32_t sum = 0, hw;
	struct window w;
	size_t i;

	for (a = 1; a < argc; a++) {
		if (!strcmp(argv[a], "--poke-fb")) {
			do_poke = 1;
		} else if (!strncmp(argv[a], "--tag=", 6)) {
			tag = argv[a] + 6;
		} else {
			fprintf(stderr, "usage: %s [--poke-fb] [--tag=DPUS]\n",
				argv[0]);
			return 2;
		}
	}

	page_size = sysconf(_SC_PAGESIZE);

	if (do_poke)
		poke_fb();

	fd = open("/dev/mem", O_RDONLY | O_SYNC);
	if (fd < 0) {
		fprintf(stderr, "/dev/mem: %s\n", strerror(errno));
		return 1;
	}

	/*
	 * Same gate as the UEFI side, for the same reason: this register is
	 * hard-wired, so a wrong answer means the block is dark and reading
	 * anything else in it would take the SoC down.
	 */
	if (window_open(&w, fd, MDSS_HW_VERSION, 4) < 0) {
		fprintf(stderr, "mmap %#x: %s\n", MDSS_HW_VERSION, strerror(errno));
		close(fd);
		return 1;
	}
	hw = w.regs[0];
	window_close(&w);

	if ((hw >> 24) != (MDSS_HW_VERSION_EXPECTED >> 24)) {
		fprintf(stderr, "MDSS is dark: HW_VERSION reads 0x%08x, expected "
				"0x%08x. Draw a frame first (--poke-fb on Linux, "
				"a touch on Android) and run it again. Nothing "
				"else was read.\n", hw, MDSS_HW_VERSION_EXPECTED);
		close(fd);
		return 1;
	}

	printf("%s BEGIN v1 HW_VERSION=0x%08x regions=%zu\n", tag, hw, NREGIONS);

	for (i = 0; i < NREGIONS; i++) {
		const struct region *r = &regions[i];
		uint32_t off;

		if (r->len == 0 || r->len % 16) {
			fprintf(stderr, "# %s: length 0x%x is not a multiple of "
					"16, skipped\n", r->name, r->len);
			continue;
		}

		if (window_open(&w, fd, r->base, r->len) < 0) {
			fprintf(stderr, "# %s @ 0x%08x: mmap: %s\n", r->name,
				r->base, strerror(errno));
			continue;
		}

		printf("%s === %s @ 0x%08x len 0x%x\n", tag, r->name, r->base,
		       r->len);

		for (off = 0; off < r->len; off += 16) {
			uint32_t v[4];
			int k;

			for (k = 0; k < 4; k++) {
				v[k] = w.regs[(off >> 2) + k];
				sum += v[k];
			}

			printf("%s %08x: %08x %08x %08x %08x\n", tag,
			       r->base + off, v[0], v[1], v[2], v[3]);
		}

		window_close(&w);
	}

	printf("%s END sum=0x%08x\n", tag, sum);
	close(fd);
	return 0;
}



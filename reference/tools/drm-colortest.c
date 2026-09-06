// SPDX-License-Identifier: GPL-2.0-only
/*
 * Nine colour swatches through KMS, to find out whether the red/blue distortion
 * follows the RGB channels or follows DSC's Co channel.
 *
 * The distortion has a very specific shape: saturated red and blue are wrong,
 * green and white are fine. DSC 1.2 codes internally in YCoCg-R, where
 * Co = R - B, and that channel is exactly what separates the broken colours from
 * the good ones -- white and green both have Co = 0. Eleven experiments have
 * ruled out everything around it (bit depth, slice_per_pkt, convert_rgb,
 * line_buf_depth, the RC table, the panel init sequence, the DPU's SPR block,
 * and every DSPP colour block), but nothing has tested Co itself.
 *
 * Magenta, cyan and yellow are the swatches that settle it, because the two
 * candidate faults predict opposite results for all three. Everything observed
 * so far -- red and blue bad, green and white good -- fits both of these equally
 * well, which is why nothing so far has been able to separate them:
 *
 *                            Co = R-B   Cg        if Co is  if Cg<0 is
 *                                                 at fault  at fault
 *     red      (255,  0,  0)     +255   -127        bad       bad     (observed bad)
 *     blue     (  0,  0,255)     -255   -127        bad       bad     (observed bad)
 *     green    (  0,255,  0)        0   +255        good      good    (observed good)
 *     white    (255,255,255)        0      0        good      good    (observed good)
 *     magenta  (255,  0,255)        0   -255        GOOD      BAD
 *     cyan     (  0,255,255)     -255   +128        BAD       GOOD
 *     yellow   (255,255,  0)     +255   +128        BAD       GOOD
 *
 * So magenta good with cyan and yellow bad puts the fault in Co; magenta bad with
 * cyan and yellow good puts it in the negative half of Cg. Magenta bad *and* cyan
 * and yellow bad means it is not a chroma channel at all and the R and B channels
 * themselves are involved -- which would exonerate DSC's colour transform and
 * make the panel and the UEFI reference the next question.
 *
 * Each swatch's YCoCg-R values and both predictions are printed at run time
 * rather than asserted here, so the table above can be checked against the
 * arithmetic that the code actually does.
 *
 * Usage -- needs DRM master, so stop the compositor first (systemctl stop sddm),
 * or run it from a VT with nothing on it:
 *
 *     ./drm-colortest                  # the 3x3 grid, 60 s
 *     ./drm-colortest --solid magenta  # one colour full screen, easiest to judge
 *     ./drm-colortest --ramp red       # black -> red in 16 steps, finds the
 *                                      # saturation at which it starts to break
 *     ./drm-colortest --bpc 30         # same thing on a 10-bit framebuffer
 *
 * Grid layout, top to bottom, left to right -- each swatch is numbered with that
 * many small dots in its top-left corner, painted black or white so they survive
 * whatever happens to the swatch itself (both have Co = 0):
 *
 *     1 red      2 green    3 blue
 *     4 cyan     5 magenta  6 yellow
 *     7 white    8 grey     9 black
 *
 * build -- the -I is written out rather than taken from pkg-config because the
 * shell on both machines is fish, which does not do $(...) command substitution:
 *
 *     cc -O1 -o drm-colortest drm-colortest.c -I/usr/include/libdrm -ldrm
 */

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm_fourcc.h>

static const struct swatch {
	const char *name;
	uint8_t     r, g, b;
} swatches[] = {
	{ "red",     0xff, 0x00, 0x00 },
	{ "green",   0x00, 0xff, 0x00 },
	{ "blue",    0x00, 0x00, 0xff },
	{ "cyan",    0x00, 0xff, 0xff },
	{ "magenta", 0xff, 0x00, 0xff },
	{ "yellow",  0xff, 0xff, 0x00 },
	{ "white",   0xff, 0xff, 0xff },
	{ "grey",    0x80, 0x80, 0x80 },
	{ "black",   0x00, 0x00, 0x00 },
};
#define NSWATCH (sizeof(swatches) / sizeof(swatches[0]))

#define GRID_COLS 3
#define GRID_GAP  8	/* black seam between swatches, so edges are unambiguous */
#define DOT       16	/* size of a numbering dot */
#define DOT_GAP   8

/*
 * DSC 1.2's reversible YCoCg-R, straight from the spec's forward transform. The
 * shifts are arithmetic on every compiler this is built with, which is what the
 * spec means.
 */
static void ycocg_r(int r, int g, int b, int *y, int *co, int *cg)
{
	int t;

	*co = r - b;
	t   = b + (*co >> 1);
	*cg = g - t;
	*y  = t + (*cg >> 1);
}

static int pentile = -1;

struct fb {
	uint8_t *map;
	uint32_t pitch;
	unsigned w, h;
	unsigned bpc;
};

/*
 * XR24 is 0x00RRGGBB. XR30 (DRM_FORMAT_XRGB2101010) packs 10 bits per channel
 * with blue at the bottom, so the 8-bit values are scaled by (v << 2) | (v >> 6)
 * -- exactly 1023/255, which keeps full scale full and black black.
 */
static uint32_t pixel(const struct fb *fb, uint8_t r, uint8_t g, uint8_t b)
{
	if (fb->bpc == 30) {
		uint32_t R = ((uint32_t)r << 2) | (r >> 6);
		uint32_t G = ((uint32_t)g << 2) | (g >> 6);
		uint32_t B = ((uint32_t)b << 2) | (b >> 6);

		return (R << 20) | (G << 10) | B;
	}

	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

static void fill(struct fb *fb, unsigned x0, unsigned y0, unsigned w,
		 unsigned h, uint32_t v)
{
	unsigned x, y;

	if (x0 >= fb->w || y0 >= fb->h)
		return;
	if (x0 + w > fb->w)
		w = fb->w - x0;
	if (y0 + h > fb->h)
		h = fb->h - y0;

	uint32_t vodd = v;

	/*
	 * PENTILE=1 in the environment: put the red value where the DSC wrapper
	 * reads chroma on odd columns. In native 4:2:2 it takes (Y0, Cb, Y1, Cr)
	 * from a pixel pair as (P0.g, P0.b, P1.g, P1.b), so channel 0 is never read
	 * and Cr comes out equal to Cb -- measured on zorn as output (B, G, B) for
	 * all nine swatches. Writing red into the blue slot of odd columns hands Cr
	 * the red value the hardware would otherwise never see. If that makes the
	 * colours correct, what is missing is a pentile-style rearrangement between
	 * the mixer and DSC, not anything in the DSC configuration itself.
	 */
	if (pentile < 0)
		pentile = getenv("PENTILE") ? 1 : 0;

	if (pentile) {
		if (fb->bpc == 30)
			vodd = (v & ~0x3ffu) | ((v >> 20) & 0x3ff);
		else
			vodd = (v & ~0xffu) | ((v >> 16) & 0xff);
	}

	for (y = y0; y < y0 + h; y++) {
		uint32_t *row = (uint32_t *)(fb->map + y * fb->pitch);

		for (x = x0; x < x0 + w; x++)
			row[x] = (pentile && (x & 1)) ? vodd : v;
	}
}

/* Rec.601 luma, only to decide whether the dots go black or white. */
static int is_light(const struct swatch *s)
{
	return (299 * s->r + 587 * s->g + 114 * s->b) / 1000 > 127;
}

static void report(const struct swatch *s, unsigned n)
{
	int y, co, cg;

	ycocg_r(s->r, s->g, s->b, &y, &co, &cg);
	printf("  %u %-8s rgb(%3u,%3u,%3u)  Y=%4d Co=%5d Cg=%5d   "
	       "if Co: %-4s   if Cg<0: %s\n", n, s->name, s->r, s->g, s->b,
	       y, co, cg, co ? "BAD" : "GOOD", cg < 0 ? "BAD" : "GOOD");
}

static void draw_grid(struct fb *fb)
{
	unsigned rows = (NSWATCH + GRID_COLS - 1) / GRID_COLS;
	unsigned cw = (fb->w - (GRID_COLS - 1) * GRID_GAP) / GRID_COLS;
	unsigned ch = (fb->h - (rows - 1) * GRID_GAP) / rows;
	unsigned i;

	fill(fb, 0, 0, fb->w, fb->h, pixel(fb, 0, 0, 0));

	for (i = 0; i < NSWATCH; i++) {
		const struct swatch *s = &swatches[i];
		unsigned col = i % GRID_COLS, row = i / GRID_COLS;
		unsigned x0 = col * (cw + GRID_GAP);
		unsigned y0 = row * (ch + GRID_GAP);
		uint32_t dot = is_light(s) ? pixel(fb, 0, 0, 0)
					  : pixel(fb, 0xff, 0xff, 0xff);
		unsigned d;

		fill(fb, x0, y0, cw, ch, pixel(fb, s->r, s->g, s->b));

		/* i+1 dots, so the swatch can be named out loud without a font. */
		for (d = 0; d <= i; d++)
			fill(fb, x0 + DOT_GAP + d * (DOT + DOT_GAP),
			     y0 + DOT_GAP, DOT, DOT, dot);

		report(s, i + 1);
	}
}

static void draw_solid(struct fb *fb, const struct swatch *s)
{
	fill(fb, 0, 0, fb->w, fb->h, pixel(fb, s->r, s->g, s->b));
	report(s, (unsigned)(s - swatches) + 1);
}

/*
 * Horizontal bands, each a different RGB triple with all three channels
 * distinct. The nine-swatch grid could not answer which output channel follows
 * which input: eight of its nine colours have channels that are only 0x00 or
 * 0xff, so a component that ended up reading the wrong input often produced the
 * same pixel anyway. Pure red is the clearest case -- G and B are both zero, so
 * Y and Cb are indistinguishable no matter which input they took.
 *
 * These triples are chosen so every channel is a different, recognisable level,
 * and so the six permutations of (R, G, B) are all present. Read the bands top
 * to bottom and the mapping falls out of one photograph:
 *
 *   1  (255, 128,   0)  red   full, green half, blue off
 *   2  (  0, 255, 128)  rotated once
 *   3  (128,   0, 255)  rotated twice
 *   4  (255,   0, 128)  reflected
 *   5  (128, 255,   0)
 *   6  (  0, 128, 255)
 *   7  (255, 128,  64)  three distinct nonzero levels, no channel at an extreme
 *   8  (192,  96,  32)  the same ratios darker, to separate gain from routing
 *
 * A routing fault permutes the bands; a gain fault changes 7 and 8 together
 * while leaving the ordering of 1..6 intact.
 */
static const struct swatch bands[] = {
	{ "R255 G128 B000", 0xff, 0x80, 0x00 },
	{ "R000 G255 B128", 0x00, 0xff, 0x80 },
	{ "R128 G000 B255", 0x80, 0x00, 0xff },
	{ "R255 G000 B128", 0xff, 0x00, 0x80 },
	{ "R128 G255 B000", 0x80, 0xff, 0x00 },
	{ "R000 G128 B255", 0x00, 0x80, 0xff },
	{ "R255 G128 B064", 0xff, 0x80, 0x40 },
	{ "R192 G096 B032", 0xc0, 0x60, 0x20 },
};
#define NBANDS (sizeof(bands) / sizeof(bands[0]))

static void draw_bands(struct fb *fb)
{
	unsigned bh = (fb->h - (NBANDS - 1) * GRID_GAP) / NBANDS;
	unsigned i;

	fill(fb, 0, 0, fb->w, fb->h, pixel(fb, 0, 0, 0));

	for (i = 0; i < NBANDS; i++) {
		const struct swatch *s = &bands[i];
		unsigned y0 = i * (bh + GRID_GAP);
		uint32_t dot = is_light(s) ? pixel(fb, 0, 0, 0)
					  : pixel(fb, 0xff, 0xff, 0xff);
		unsigned d;

		fill(fb, 0, y0, fb->w, bh, pixel(fb, s->r, s->g, s->b));

		for (d = 0; d <= i; d++)
			fill(fb, DOT_GAP + d * (DOT + DOT_GAP),
			     y0 + DOT_GAP, DOT, DOT, dot);

		printf("  %u %-14s rgb(%3u,%3u,%3u)\n",
		       i + 1, s->name, s->r, s->g, s->b);
	}
}

#define RAMP_STEPS 16

/*
 * Two ramps at once. Top half goes white -> colour, which is saturation rising
 * at full value; bottom half goes black -> colour, which is value rising at full
 * saturation. The symptom is stated in terms of saturation, so the top half is
 * the one that should show a threshold -- but having both says whether
 * brightness matters as well, which nobody has checked.
 */
static void draw_ramp(struct fb *fb, const struct swatch *s)
{
	unsigned bw = fb->w / RAMP_STEPS;
	unsigned half = fb->h / 2;
	unsigned i;

	for (i = 0; i < RAMP_STEPS; i++) {
		unsigned k = 255 * i / (RAMP_STEPS - 1);
		unsigned x0 = i * bw;
		unsigned w = (i == RAMP_STEPS - 1) ? fb->w - x0 : bw;
		uint8_t sr = 255 - (255 - s->r) * k / 255;
		uint8_t sg = 255 - (255 - s->g) * k / 255;
		uint8_t sb = 255 - (255 - s->b) * k / 255;
		uint8_t vr = s->r * k / 255;
		uint8_t vg = s->g * k / 255;
		uint8_t vb = s->b * k / 255;
		int y, co, cg, co2;

		fill(fb, x0, 0, w, half, pixel(fb, sr, sg, sb));
		fill(fb, x0, half, w, fb->h - half, pixel(fb, vr, vg, vb));

		ycocg_r(sr, sg, sb, &y, &co, &cg);
		ycocg_r(vr, vg, vb, &y, &co2, &cg);
		printf("  step %2u/%u   sat rgb(%3u,%3u,%3u) Co=%5d   "
		       "val rgb(%3u,%3u,%3u) Co=%5d\n",
		       i, RAMP_STEPS - 1, sr, sg, sb, co, vr, vg, vb, co2);
	}
}

static const struct swatch *find_swatch(const char *name)
{
	unsigned i;

	for (i = 0; i < NSWATCH; i++)
		if (!strcmp(swatches[i].name, name))
			return &swatches[i];
	return NULL;
}

static void usage(const char *argv0)
{
	unsigned i;

	fprintf(stderr,
		"usage: %s [--bpc 24|30] [--solid NAME] [--ramp NAME] [--bands]\n"
		"          [--seconds N] [--card N]\n"
		"colours:", argv0);
	for (i = 0; i < NSWATCH; i++)
		fprintf(stderr, " %s", swatches[i].name);
	fprintf(stderr, "\n");
}

/*
 * Pick the first card that has a connected connector with modes, so this does
 * not have to know whether msm landed on card0 or card1 on this boot.
 */
static int find_card(int want, drmModeRes **res_out, drmModeConnector **conn_out)
{
	int n, lo = (want >= 0) ? want : 0, hi = (want >= 0) ? want : 3;

	for (n = lo; n <= hi; n++) {
		char path[32];
		drmModeRes *res;
		int fd, i;

		snprintf(path, sizeof path, "/dev/dri/card%d", n);
		fd = open(path, O_RDWR | O_CLOEXEC);
		if (fd < 0)
			continue;

		res = drmModeGetResources(fd);
		if (!res) {
			close(fd);
			continue;
		}

		for (i = 0; i < res->count_connectors; i++) {
			drmModeConnector *c =
				drmModeGetConnector(fd, res->connectors[i]);

			if (c && c->connection == DRM_MODE_CONNECTED &&
			    c->count_modes) {
				printf("using %s, connector %u\n", path,
				       c->connector_id);
				*res_out = res;
				*conn_out = c;
				return fd;
			}
			if (c)
				drmModeFreeConnector(c);
		}

		drmModeFreeResources(res);
		close(fd);
	}

	return -1;
}

int main(int argc, char **argv)
{
	const struct swatch *one = NULL;
	const char *mode_name = "grid";
	unsigned seconds = 60;
	struct fb fb = { .bpc = 24 };
	drmModeRes *res = NULL;
	drmModeConnector *conn = NULL;
	drmModeCrtc *saved = NULL;
	drmModeModeInfo *mode;
	uint32_t crtc_id = 0, fb_id = 0, handle = 0;
	uint64_t size = 0, offset = 0;
	uint32_t fourcc;
	int card = -1, fd, i, ret;

	for (i = 1; i < argc; i++) {
		const char *a = argv[i];
		const char *v = (i + 1 < argc) ? argv[i + 1] : NULL;

		if (!strcmp(a, "--bpc") && v) {
			fb.bpc = (unsigned)atoi(v), i++;
		} else if (!strcmp(a, "--seconds") && v) {
			seconds = (unsigned)atoi(v), i++;
		} else if (!strcmp(a, "--card") && v) {
			card = atoi(v), i++;
		} else if (!strcmp(a, "--bands")) {
			mode_name = a + 2;
		} else if ((!strcmp(a, "--solid") || !strcmp(a, "--ramp")) && v) {
			mode_name = a + 2;
			one = find_swatch(v);
			if (!one) {
				fprintf(stderr, "unknown colour: %s\n", v);
				usage(argv[0]);
				return 1;
			}
			i++;
		} else {
			usage(argv[0]);
			return 1;
		}
	}

	if (fb.bpc != 24 && fb.bpc != 30) {
		usage(argv[0]);
		return 1;
	}
	fourcc = (fb.bpc == 30) ? DRM_FORMAT_XRGB2101010 : DRM_FORMAT_XRGB8888;

	fd = find_card(card, &res, &conn);
	if (fd < 0) {
		fprintf(stderr, "no DRM card with a connected connector\n");
		return 1;
	}

	if (drmSetMaster(fd)) {
		fprintf(stderr, "drmSetMaster: %s -- something else holds the "
			"device (systemctl stop sddm, or run this from an idle "
			"VT)\n", strerror(errno));
		return 1;
	}

	if (conn->encoder_id) {
		drmModeEncoder *enc = drmModeGetEncoder(fd, conn->encoder_id);

		if (enc) {
			crtc_id = enc->crtc_id;
			drmModeFreeEncoder(enc);
		}
	}
	if (!crtc_id && res->count_crtcs)
		crtc_id = res->crtcs[0];
	if (!crtc_id) {
		fprintf(stderr, "no usable crtc\n");
		return 1;
	}
	saved = drmModeGetCrtc(fd, crtc_id);

	mode = &conn->modes[0];
	fb.w = mode->hdisplay;
	fb.h = mode->vdisplay;

	printf("crtc %u, mode %ux%u@%u, %s, pattern %s\n", crtc_id, fb.w, fb.h,
	       mode->vrefresh, fb.bpc == 30 ? "XR30 (10 bpc)" : "XR24 (8 bpc)",
	       mode_name);

	ret = drmModeCreateDumbBuffer(fd, fb.w, fb.h, 32, 0, &handle, &fb.pitch,
				      &size);
	if (ret) {
		fprintf(stderr, "CreateDumbBuffer: %s\n", strerror(-ret));
		return 1;
	}

	ret = drmModeMapDumbBuffer(fd, handle, &offset);
	if (ret) {
		fprintf(stderr, "MapDumbBuffer: %s\n", strerror(-ret));
		return 1;
	}

	fb.map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
	if (fb.map == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	if (!strcmp(mode_name, "solid"))
		draw_solid(&fb, one);
	else if (!strcmp(mode_name, "ramp"))
		draw_ramp(&fb, one);
	else if (!strcmp(mode_name, "bands"))
		draw_bands(&fb);
	else
		draw_grid(&fb);

	{
		uint32_t handles[4] = { handle };
		uint32_t pitches[4] = { fb.pitch };
		uint32_t offsets[4] = { 0 };

		ret = drmModeAddFB2(fd, fb.w, fb.h, fourcc, handles, pitches,
				    offsets, &fb_id, 0);
	}
	if (ret) {
		fprintf(stderr, "AddFB2 with %s: %s -- the DPU may not accept "
			"this format on this pipe\n",
			fb.bpc == 30 ? "XR30" : "XR24", strerror(-ret));
		return 1;
	}

	ret = drmModeSetCrtc(fd, crtc_id, fb_id, 0, 0, &conn->connector_id, 1,
			     mode);
	if (ret) {
		fprintf(stderr, "SetCrtc: %s\n", strerror(-ret));
		return 1;
	}

	printf("displayed. restoring in %us.\n", seconds);
	fflush(stdout);
	sleep(seconds);

	if (saved)
		drmModeSetCrtc(fd, saved->crtc_id, saved->buffer_id, saved->x,
			       saved->y, &conn->connector_id, 1, &saved->mode);
	drmModeRmFB(fd, fb_id);
	drmModeDestroyDumbBuffer(fd, handle);
	drmDropMaster(fd);
	close(fd);
	return 0;
}

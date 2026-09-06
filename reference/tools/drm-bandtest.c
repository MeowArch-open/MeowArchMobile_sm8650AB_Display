// SPDX-License-Identifier: GPL-2.0-only
/*
 * Paint colour bands straight through KMS, with a choice of 8-bit or 10-bit
 * framebuffer, to settle whether this panel's red/blue distortion is a bit-depth
 * problem.
 *
 * Why this exists rather than flipping a KWin setting: KWin only moves to a
 * 10-bit framebuffer as part of enabling HDR, which simultaneously changes the
 * colour management pipeline. That would confound the experiment. Here the only
 * difference between the two runs is the DRM pixel format -- same bands, same
 * modeset path, same DSC configuration.
 *
 * Pair it with the panel driver's dsc_bpc so the whole chain agrees:
 *
 *     echo 8  > /sys/module/panel_xiaomi_o11_42_02_0a/parameters/dsc_bpc
 *     ./drm-bandtest 24        # baseline: known to give violet/grey
 *     echo 10 > /sys/module/panel_xiaomi_o11_42_02_0a/parameters/dsc_bpc
 *     ./drm-bandtest 30        # the actual question
 *
 * Needs to be DRM master, so nothing else may hold the device -- stop sddm first.
 *
 * build: cc -O1 -o drm-bandtest drm-bandtest.c -I/usr/include/libdrm -ldrm
 *        (the -I is spelled out because fish has no $(...) substitution)
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

/* Five bands, as 8-bit-per-channel reference values. */
static const struct { const char *name; uint8_t r, g, b; } bands[] = {
	{ "pure blue",   0x00, 0x00, 0xff },
	{ "KDE accent",  0x3d, 0xae, 0xe9 },
	{ "pure red",    0xff, 0x00, 0x00 },
	{ "pure green",  0x00, 0xff, 0x00 },
	{ "white",       0xff, 0xff, 0xff },
};
#define NBANDS (sizeof(bands) / sizeof(bands[0]))

/*
 * XR24 is 0x00RRGGBB. XR30 (DRM_FORMAT_XRGB2101010) packs 10 bits per channel
 * with blue at the bottom, so the 8-bit reference values are scaled by 1023/255
 * -- exactly 4.011..., i.e. (v << 2) | (v >> 6), which keeps full-scale full and
 * black black rather than losing the top two codes.
 */
static uint32_t pixel(unsigned bpc, uint8_t r, uint8_t g, uint8_t b)
{
	if (bpc == 30) {
		uint32_t R = ((uint32_t)r << 2) | (r >> 6);
		uint32_t G = ((uint32_t)g << 2) | (g >> 6);
		uint32_t B = ((uint32_t)b << 2) | (b >> 6);

		return (R << 20) | (G << 10) | B;
	}

	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

int main(int argc, char **argv)
{
	unsigned bpc = (argc > 1) ? (unsigned)atoi(argv[1]) : 24;
	uint32_t fourcc = (bpc == 30) ? DRM_FORMAT_XRGB2101010 : DRM_FORMAT_XRGB8888;
	drmModeRes *res;
	drmModeConnector *conn = NULL;
	drmModeCrtc *saved = NULL;
	uint32_t crtc_id = 0, fb_id = 0, handle = 0;
	uint32_t pitch = 0;
	uint64_t size = 0, offset = 0;
	uint8_t *map;
	int fd, i, ret;

	if (bpc != 24 && bpc != 30) {
		fprintf(stderr, "usage: %s [24|30]\n", argv[0]);
		return 1;
	}

	fd = open("/dev/dri/card1", O_RDWR | O_CLOEXEC);
	if (fd < 0) {
		perror("open /dev/dri/card1");
		return 1;
	}

	if (drmSetMaster(fd)) {
		fprintf(stderr, "drmSetMaster: %s -- something else holds the device "
			"(stop sddm)\n", strerror(errno));
		return 1;
	}

	res = drmModeGetResources(fd);
	if (!res) {
		perror("drmModeGetResources");
		return 1;
	}

	for (i = 0; i < res->count_connectors; i++) {
		drmModeConnector *c = drmModeGetConnector(fd, res->connectors[i]);

		if (c && c->connection == DRM_MODE_CONNECTED && c->count_modes) {
			conn = c;
			break;
		}
		if (c)
			drmModeFreeConnector(c);
	}
	if (!conn) {
		fprintf(stderr, "no connected connector with modes\n");
		return 1;
	}

	/* Whatever CRTC the connector's encoder is already wired to. */
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

	drmModeModeInfo *mode = &conn->modes[0];

	printf("connector %u, crtc %u, mode %ux%u@%u, format %s\n",
	       conn->connector_id, crtc_id, mode->hdisplay, mode->vdisplay,
	       mode->vrefresh, bpc == 30 ? "XR30 (10 bpc)" : "XR24 (8 bpc)");

	ret = drmModeCreateDumbBuffer(fd, mode->hdisplay, mode->vdisplay, 32, 0,
				      &handle, &pitch, &size);
	if (ret) {
		fprintf(stderr, "CreateDumbBuffer: %s\n", strerror(-ret));
		return 1;
	}

	ret = drmModeMapDumbBuffer(fd, handle, &offset);
	if (ret) {
		fprintf(stderr, "MapDumbBuffer: %s\n", strerror(-ret));
		return 1;
	}

	map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
	if (map == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	unsigned bh = mode->vdisplay / NBANDS;

	for (i = 0; i < (int)NBANDS; i++) {
		uint32_t v = pixel(bpc, bands[i].r, bands[i].g, bands[i].b);
		unsigned y0 = i * bh;
		unsigned y1 = (i == (int)NBANDS - 1) ? mode->vdisplay : y0 + bh;
		unsigned x, y;

		for (y = y0; y < y1; y++) {
			uint32_t *row = (uint32_t *)(map + y * pitch);

			for (x = 0; x < mode->hdisplay; x++)
				row[x] = v;
		}
		printf("  band %d %-12s -> %#010x\n", i + 1, bands[i].name, v);
	}

	uint32_t handles[4] = { handle }, pitches[4] = { pitch }, offsets[4] = { 0 };

	ret = drmModeAddFB2(fd, mode->hdisplay, mode->vdisplay, fourcc,
			    handles, pitches, offsets, &fb_id, 0);
	if (ret) {
		fprintf(stderr, "AddFB2 with %s: %s -- the DPU may not accept this "
			"format on this pipe\n",
			bpc == 30 ? "XR30" : "XR24", strerror(-ret));
		return 1;
	}

	ret = drmModeSetCrtc(fd, crtc_id, fb_id, 0, 0, &conn->connector_id, 1, mode);
	if (ret) {
		fprintf(stderr, "SetCrtc: %s\n", strerror(-ret));
		return 1;
	}

	printf("displayed. sleeping 60s, then restoring.\n");
	fflush(stdout);
	sleep(60);

	if (saved)
		drmModeSetCrtc(fd, saved->crtc_id, saved->buffer_id, saved->x, saved->y,
			       &conn->connector_id, 1, &saved->mode);
	drmModeRmFB(fd, fb_id);
	drmModeDestroyDumbBuffer(fd, handle);
	drmDropMaster(fd);
	close(fd);
	return 0;
}


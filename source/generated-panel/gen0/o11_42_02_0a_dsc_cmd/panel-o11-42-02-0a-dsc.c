// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <video/mipi_display.h>

#include <drm/display/drm_dsc.h>
#include <drm/display/drm_dsc_helper.h>
#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct o11_42_02_0a_dsc {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct drm_dsc_config dsc;
	struct gpio_desc *reset_gpio;
};

static inline
struct o11_42_02_0a_dsc *to_o11_42_02_0a_dsc(struct drm_panel *panel)
{
	return container_of_const(panel, struct o11_42_02_0a_dsc, panel);
}

static void o11_42_02_0a_dsc_reset(struct o11_42_02_0a_dsc *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(11000, 12000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(11000, 12000);
}

static int o11_42_02_0a_dsc_on(struct o11_42_02_0a_dsc *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_column_address_multi(&dsi_ctx, 0x0000, 0x059f);
	mipi_dsi_dcs_set_page_address_multi(&dsi_ctx, 0x0000, 0x0c7f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x90, 0x03, 0x43);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x91,
				     0xab, 0xf0, 0x00, 0x14, 0xd1, 0x00, 0x01,
				     0xde, 0x00, 0xa3, 0x00, 0x3c, 0x05, 0x7a,
				     0x15, 0x9a, 0x11, 0x50);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xde,
				     0x10, 0x34, 0x25, 0x30, 0x14, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x84, 0x44, 0x01, 0x00, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0xcc);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2, 0x01);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x04);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0xff0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x20);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8b, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0xa2);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe7,
				     0xff, 0xff, 0xff, 0xff, 0xff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe7, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc7, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x00, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x35);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x22, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xca, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8,
				     0x11, 0x90, 0x00, 0x00, 0x00, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8,
				     0x00, 0x70, 0x74, 0x74, 0x78, 0x78, 0x7c,
				     0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c,
				     0x78, 0x78, 0x74, 0x74, 0x70, 0x70, 0x64,
				     0x64, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x1d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8,
				     0x00, 0x64, 0x6c, 0x6c, 0x80, 0x80, 0x88,
				     0x88, 0x88, 0x88, 0x8c, 0x8c, 0x8c, 0x8c,
				     0x88, 0x88, 0x84, 0x84, 0x84, 0x84, 0x70,
				     0x70, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8,
				     0x00, 0xa4, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8,
				     0xa8, 0xac, 0xac, 0xac, 0xac, 0xac, 0xac,
				     0xa8, 0xa8, 0xa4, 0xa4, 0xa4, 0xa4, 0x8c,
				     0x8c, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe0, 0x01, 0x01, 0x01, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe0,
				     0x80, 0x00, 0x21, 0x32, 0x43, 0x54, 0x65,
				     0x76, 0x87, 0x98, 0x99, 0x99, 0x99);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x03, 0x03, 0x03, 0x06, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x01, 0x02, 0x04, 0x05, 0x0a, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x2a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x03, 0x04, 0x06, 0x07, 0x0b, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x38);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
				     0x01, 0x04, 0x07, 0x09, 0x0a, 0x0c, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x46);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
				     0x03, 0x04, 0x06, 0x07, 0x09, 0x0a, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x54);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
				     0x03, 0x04, 0x06, 0x07, 0x09, 0x0a, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x62);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
				     0x01, 0x03, 0x05, 0x08, 0x0c, 0x0d, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1,
				     0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02,
				     0x03, 0x05, 0x06, 0x09, 0x0b, 0x0e, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x01, 0x01, 0x01, 0x02, 0x19, 0x1a, 0x10,
				     0x0f, 0x0f, 0x17, 0x08, 0x12, 0x15, 0x1e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x04, 0x08, 0x0b, 0x0f, 0x11, 0x11, 0x13,
				     0x13, 0x0c, 0x0c, 0x0a, 0x0b, 0x12, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x02, 0x04, 0x05, 0x07, 0x0a, 0x0d, 0x0f,
				     0x0d, 0x06, 0x09, 0x0a, 0x0e, 0x0f, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x2a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x02, 0x04, 0x0a, 0x0b, 0x02, 0x03, 0x06,
				     0x07, 0x07, 0x09, 0x0b, 0x0c, 0x0f, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x38);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x03, 0x05, 0x05, 0x08, 0x02, 0x02, 0x04,
				     0x05, 0x05, 0x08, 0x0b, 0x0d, 0x10, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x46);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x02, 0x02, 0x03, 0x05, 0x02, 0x01, 0x04,
				     0x05, 0x07, 0x09, 0x0a, 0x0c, 0x0f, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x54);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x02, 0x02, 0x03, 0x05, 0x02, 0x01, 0x04,
				     0x05, 0x07, 0x09, 0x0a, 0x0c, 0x0f, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x62);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x03,
				     0x03, 0x07, 0x08, 0x09, 0x0d, 0x0d, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2,
				     0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03,
				     0x04, 0x06, 0x08, 0x09, 0x0b, 0x0f, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x02, 0x02, 0x07, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
				     0x01, 0x01, 0x02, 0x04, 0x04, 0x0e, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
				     0x01, 0x01, 0x04, 0x03, 0x05, 0x08, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x2a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
				     0x02, 0x02, 0x06, 0x08, 0x0c, 0x0d, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x38);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
				     0x02, 0x05, 0x06, 0x0a, 0x0a, 0x0c, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x46);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
				     0x02, 0x04, 0x07, 0x06, 0x0a, 0x0b, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x54);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
				     0x02, 0x04, 0x07, 0x06, 0x0a, 0x0b, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x62);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x03,
				     0x04, 0x05, 0x07, 0x0a, 0x0c, 0x0f, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3,
				     0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02,
				     0x03, 0x06, 0x07, 0x0a, 0x0d, 0x0f, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe5,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe6,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe0, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbe, 0x47, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbe, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc8, 0x01, 0x02, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xaa, 0x55, 0xa5, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfe, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xaa, 0x55, 0xa5, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf3, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc5, 0x0a, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x78);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x11, 0x00, 0x2a, 0x00, 0xc2, 0x01, 0xda,
				     0x03, 0x7c, 0x05, 0xb1, 0x08, 0x80, 0x0b,
				     0xee, 0x0f, 0xff, 0x05, 0x55, 0x05, 0x56,
				     0x05, 0x55);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x6f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x02, 0xd0, 0x05, 0xa0, 0x02, 0xd0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1,
				     0x8c, 0xff, 0xcc, 0xff, 0xff, 0xcc, 0xff,
				     0xff, 0xcc, 0xff, 0xff, 0xec, 0xff, 0x7f,
				     0xee, 0x7f, 0x7f, 0xff, 0x7f, 0xff, 0x0e,
				     0x7f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1, 0x4f, 0x00, 0xff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1,
				     0x0c, 0xff, 0xcc, 0xff, 0xff, 0xcc, 0xff,
				     0xff, 0xcc, 0xff, 0xff, 0xec, 0xff, 0x7f,
				     0xee, 0x7f, 0x7f, 0xcf, 0x7f, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x99);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x30);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x20, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x70, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x26, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x1d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x20, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x3a, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x62, 0xde);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x62, 0xde);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x1a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x62, 0xde);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x62, 0xde);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x3f, 0x62, 0xde);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x29);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x11, 0x11, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x2c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0xaa, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0xaa, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0xe3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0xe4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x29);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x29);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x02, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea, 0x01, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea, 0x01, 0xac);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x1a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea, 0x01, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea, 0x01, 0xac);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0xea);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0xea);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x77);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcb,
				     0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xeb, 0x01);

	return dsi_ctx.accum_err;
}

static int o11_42_02_0a_dsc_off(struct o11_42_02_0a_dsc *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x00);
	mipi_dsi_usleep_range(&dsi_ctx, 10000, 11000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 105);

	return dsi_ctx.accum_err;
}

static int o11_42_02_0a_dsc_prepare(struct drm_panel *panel)
{
	struct o11_42_02_0a_dsc *ctx = to_o11_42_02_0a_dsc(panel);
	struct device *dev = &ctx->dsi->dev;
	struct drm_dsc_picture_parameter_set pps;
	int ret;

	o11_42_02_0a_dsc_reset(ctx);

	ret = o11_42_02_0a_dsc_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	drm_dsc_pps_payload_pack(&pps, &ctx->dsc);

	ret = mipi_dsi_picture_parameter_set(ctx->dsi, &pps);
	if (ret < 0) {
		dev_err(panel->dev, "failed to transmit PPS: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_compression_mode(ctx->dsi, true);
	if (ret < 0) {
		dev_err(dev, "failed to enable compression mode: %d\n", ret);
		return ret;
	}

	msleep(28); /* TODO: Is this panel-dependent? */

	return 0;
}

static int o11_42_02_0a_dsc_unprepare(struct drm_panel *panel)
{
	struct o11_42_02_0a_dsc *ctx = to_o11_42_02_0a_dsc(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = o11_42_02_0a_dsc_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode o11_42_02_0a_dsc_mode = {
	.clock = (1440 + 8 + 12 + 8) * (3200 + 16 + 14 + 6) * 60 / 1000,
	.hdisplay = 1440,
	.hsync_start = 1440 + 8,
	.hsync_end = 1440 + 8 + 12,
	.htotal = 1440 + 8 + 12 + 8,
	.vdisplay = 3200,
	.vsync_start = 3200 + 16,
	.vsync_end = 3200 + 16 + 14,
	.vtotal = 3200 + 16 + 14 + 6,
	.width_mm = 695,
	.height_mm = 1545,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int o11_42_02_0a_dsc_get_modes(struct drm_panel *panel,
				      struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &o11_42_02_0a_dsc_mode);
}

static const struct drm_panel_funcs o11_42_02_0a_dsc_panel_funcs = {
	.prepare = o11_42_02_0a_dsc_prepare,
	.unprepare = o11_42_02_0a_dsc_unprepare,
	.get_modes = o11_42_02_0a_dsc_get_modes,
};

static int o11_42_02_0a_dsc_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness_large(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

// TODO: Check if /sys/class/backlight/.../actual_brightness actually returns
// correct values. If not, remove this function.
static int o11_42_02_0a_dsc_bl_get_brightness(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness_large(dsi, &brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return brightness;
}

static const struct backlight_ops o11_42_02_0a_dsc_bl_ops = {
	.update_status = o11_42_02_0a_dsc_bl_update_status,
	.get_brightness = o11_42_02_0a_dsc_bl_get_brightness,
};

static struct backlight_device *
o11_42_02_0a_dsc_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 16383,
		.max_brightness = 16383,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &o11_42_02_0a_dsc_bl_ops, &props);
}

static int o11_42_02_0a_dsc_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct o11_42_02_0a_dsc *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct o11_42_02_0a_dsc, panel,
				   &o11_42_02_0a_dsc_panel_funcs,
				   DRM_MODE_CONNECTOR_DSI);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;

	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = o11_42_02_0a_dsc_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	/* This panel only supports DSC; unconditionally enable it */
	dsi->dsc = &ctx->dsc;

	ctx->dsc.dsc_version_major = 1;
	ctx->dsc.dsc_version_minor = 2;

	/* TODO: Pass slice_per_pkt = 2 */
	ctx->dsc.slice_height = 20;
	ctx->dsc.slice_width = 720;
	/*
	 * TODO: hdisplay should be read from the selected mode once
	 * it is passed back to drm_panel (in prepare?)
	 */
	WARN_ON(1440 % ctx->dsc.slice_width);
	ctx->dsc.slice_count = 1440 / ctx->dsc.slice_width;
	ctx->dsc.bits_per_component = 10;
	ctx->dsc.bits_per_pixel = 8 << 4; /* 4 fractional bits */
	ctx->dsc.block_pred_enable = true;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void o11_42_02_0a_dsc_remove(struct mipi_dsi_device *dsi)
{
	struct o11_42_02_0a_dsc *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id o11_42_02_0a_dsc_of_match[] = {
	{ .compatible = "mdss,o11-42-02-0a-dsc" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, o11_42_02_0a_dsc_of_match);

static struct mipi_dsi_driver o11_42_02_0a_dsc_driver = {
	.probe = o11_42_02_0a_dsc_probe,
	.remove = o11_42_02_0a_dsc_remove,
	.driver = {
		.name = "panel-o11-42-02-0a-dsc",
		.of_match_table = o11_42_02_0a_dsc_of_match,
	},
};
module_mipi_dsi_driver(o11_42_02_0a_dsc_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for xiaomi o11 42 02 0a cmd mode dsc dsi panel");
MODULE_LICENSE("GPL");

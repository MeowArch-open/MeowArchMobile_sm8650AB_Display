// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode o11_42_02_0a_dsc_mode = {
	.clock = (1440 + 8 + 12 + 8) * (3200 + 16 + 14 + 6) * 90 / 1000,
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

static const struct panel_desc_dsi o11_42_02_0a_dsc = {
	.desc = {
		.modes = &o11_42_02_0a_dsc_mode,
		.num_modes = 1,
		.bpc = 10,
		.size = {
			.width = 695,
			.height = 1545,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_CLOCK_NON_CONTINUOUS |
		 MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};

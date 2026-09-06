// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_O11_42_02_0A_DSC_CMD_H_
#define _PANEL_O11_42_02_0A_DSC_CMD_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config o11_42_02_0a_dsc_cmd_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_o11_42_02_0a_dsc_cmd",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 1,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 60,
	.panel_lp11_init = 1,
	.panel_init_delay = 0,
};

static struct panel_resolution o11_42_02_0a_dsc_cmd_panel_res = {
	.panel_width = 1440,
	.panel_height = 3200,
	.hfront_porch = 8,
	.hback_porch = 8,
	.hpulse_width = 12,
	.hsync_skew = 0,
	.vfront_porch = 16,
	.vback_porch = 6,
	.vpulse_width = 14,
	/* Borders not supported yet */
};

static struct color_info o11_42_02_0a_dsc_cmd_color = {
	.color_format = 30,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char o11_42_02_0a_dsc_cmd_on_cmd_0[] = {
	0x05, 0x00, 0x39, 0x40, 0x2a, 0x00, 0x00, 0x05,
	0x9f, 0xff, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_1[] = {
	0x05, 0x00, 0x39, 0x40, 0x2b, 0x00, 0x00, 0x0c,
	0x7f, 0xff, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_2[] = {
	0x03, 0x00, 0x39, 0x40, 0x90, 0x03, 0x43, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_3[] = {
	0x13, 0x00, 0x39, 0x40, 0x91, 0xab, 0xf0, 0x00,
	0x14, 0xd1, 0x00, 0x01, 0xde, 0x00, 0xa3, 0x00,
	0x3c, 0x05, 0x7a, 0x15, 0x9a, 0x11, 0x50, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_4[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x03, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_5[] = {
	0x6f, 0x09, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_6[] = {
	0x07, 0x00, 0x39, 0x40, 0xde, 0x10, 0x34, 0x25,
	0x30, 0x14, 0x25, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_7[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x07, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_8[] = {
	0x06, 0x00, 0x39, 0x40, 0xb0, 0x84, 0x44, 0x01,
	0x00, 0x40, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_9[] = {
	0x2f, 0x02, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_10[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x00, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_11[] = {
	0x6f, 0xcc, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_12[] = {
	0xb2, 0x01, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_13[] = {
	0x03, 0x00, 0x39, 0x40, 0x51, 0x00, 0x00, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_14[] = {
	0x6f, 0x04, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_15[] = {
	0x03, 0x00, 0x39, 0x40, 0x51, 0x0f, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_16[] = {
	0x53, 0x20, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_17[] = {
	0x35, 0x00, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_18[] = {
	0x6f, 0x01, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_19[] = {
	0x8b, 0x01, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_20[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x01, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_21[] = {
	0x6f, 0xa2, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_22[] = {
	0x06, 0x00, 0x39, 0x40, 0xe7, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_23[] = {
	0x6f, 0x11, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_24[] = {
	0xe7, 0x08, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_25[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x00, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_26[] = {
	0xc7, 0x33, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_27[] = {
	0x6f, 0x31, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_28[] = {
	0x03, 0x00, 0x39, 0x40, 0xc0, 0x00, 0x10, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_29[] = {
	0x6f, 0x35, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_30[] = {
	0x03, 0x00, 0x39, 0x40, 0xc0, 0x22, 0x40, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_31[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x04, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_32[] = {
	0xc0, 0x20, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_33[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x04, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_34[] = {
	0xca, 0x01, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_35[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x08, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_36[] = {
	0x07, 0x00, 0x39, 0x40, 0xe8, 0x11, 0x90, 0x00,
	0x00, 0x00, 0x20, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_37[] = {
	0x6f, 0x06, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_38[] = {
	0x18, 0x00, 0x39, 0x40, 0xe8, 0x00, 0x70, 0x74,
	0x74, 0x78, 0x78, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c,
	0x7c, 0x7c, 0x7c, 0x78, 0x78, 0x74, 0x74, 0x70,
	0x70, 0x64, 0x64, 0x64
};
static char o11_42_02_0a_dsc_cmd_on_cmd_39[] = {
	0x6f, 0x1d, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_40[] = {
	0x18, 0x00, 0x39, 0x40, 0xe8, 0x00, 0x64, 0x6c,
	0x6c, 0x80, 0x80, 0x88, 0x88, 0x88, 0x88, 0x8c,
	0x8c, 0x8c, 0x8c, 0x88, 0x88, 0x84, 0x84, 0x84,
	0x84, 0x70, 0x70, 0x70
};
static char o11_42_02_0a_dsc_cmd_on_cmd_41[] = {
	0x6f, 0x34, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_42[] = {
	0x18, 0x00, 0x39, 0x40, 0xe8, 0x00, 0xa4, 0xa8,
	0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xac, 0xac, 0xac,
	0xac, 0xac, 0xac, 0xa8, 0xa8, 0xa4, 0xa4, 0xa4,
	0xa4, 0x8c, 0x8c, 0x8c
};
static char o11_42_02_0a_dsc_cmd_on_cmd_43[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x08, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_44[] = {
	0x05, 0x00, 0x39, 0x40, 0xe0, 0x01, 0x01, 0x01,
	0x01, 0xff, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_45[] = {
	0x6f, 0x06, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_46[] = {
	0x0e, 0x00, 0x39, 0x40, 0xe0, 0x80, 0x00, 0x21,
	0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0x99,
	0x99, 0x99, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_47[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x01, 0x03, 0x03, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_48[] = {
	0x6f, 0x0e, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_49[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,
	0x03, 0x06, 0x07, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_50[] = {
	0x6f, 0x1c, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_51[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04,
	0x05, 0x0a, 0x0b, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_52[] = {
	0x6f, 0x2a, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_53[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x06,
	0x07, 0x0b, 0x0c, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_54[] = {
	0x6f, 0x38, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_55[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x01, 0x04, 0x07, 0x09,
	0x0a, 0x0c, 0x0e, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_56[] = {
	0x6f, 0x46, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_57[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x01, 0x03, 0x04, 0x06, 0x07,
	0x09, 0x0a, 0x0b, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_58[] = {
	0x6f, 0x54, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_59[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x01, 0x03, 0x04, 0x06, 0x07,
	0x09, 0x0a, 0x0b, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_60[] = {
	0x6f, 0x62, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_61[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x05, 0x08,
	0x0c, 0x0d, 0x0e, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_62[] = {
	0x6f, 0x70, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_63[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe1, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x02, 0x02, 0x03, 0x05, 0x06, 0x09,
	0x0b, 0x0e, 0x10, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_64[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x01, 0x01, 0x01,
	0x02, 0x19, 0x1a, 0x10, 0x0f, 0x0f, 0x17, 0x08,
	0x12, 0x15, 0x1e, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_65[] = {
	0x6f, 0x0e, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_66[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x04, 0x08, 0x0b,
	0x0f, 0x11, 0x11, 0x13, 0x13, 0x0c, 0x0c, 0x0a,
	0x0b, 0x12, 0x13, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_67[] = {
	0x6f, 0x1c, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_68[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x02, 0x04, 0x05,
	0x07, 0x0a, 0x0d, 0x0f, 0x0d, 0x06, 0x09, 0x0a,
	0x0e, 0x0f, 0x10, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_69[] = {
	0x6f, 0x2a, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_70[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x02, 0x04, 0x0a,
	0x0b, 0x02, 0x03, 0x06, 0x07, 0x07, 0x09, 0x0b,
	0x0c, 0x0f, 0x12, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_71[] = {
	0x6f, 0x38, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_72[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x03, 0x05, 0x05,
	0x08, 0x02, 0x02, 0x04, 0x05, 0x05, 0x08, 0x0b,
	0x0d, 0x10, 0x11, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_73[] = {
	0x6f, 0x46, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_74[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x02, 0x02, 0x03,
	0x05, 0x02, 0x01, 0x04, 0x05, 0x07, 0x09, 0x0a,
	0x0c, 0x0f, 0x11, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_75[] = {
	0x6f, 0x54, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_76[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x02, 0x02, 0x03,
	0x05, 0x02, 0x01, 0x04, 0x05, 0x07, 0x09, 0x0a,
	0x0c, 0x0f, 0x11, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_77[] = {
	0x6f, 0x62, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_78[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x01, 0x01, 0x02,
	0x02, 0x01, 0x01, 0x03, 0x03, 0x07, 0x08, 0x09,
	0x0d, 0x0d, 0x11, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_79[] = {
	0x6f, 0x70, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_80[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe2, 0x00, 0x00, 0x01,
	0x01, 0x01, 0x01, 0x03, 0x04, 0x06, 0x08, 0x09,
	0x0b, 0x0f, 0x11, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_81[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	0x02, 0x07, 0x07, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_82[] = {
	0x6f, 0x0e, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_83[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x04,
	0x04, 0x0e, 0x0e, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_84[] = {
	0x6f, 0x1c, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_85[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x04, 0x03,
	0x05, 0x08, 0x0e, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_86[] = {
	0x6f, 0x2a, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_87[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x06, 0x08,
	0x0c, 0x0d, 0x0f, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_88[] = {
	0x6f, 0x38, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_89[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x02, 0x02, 0x05, 0x06, 0x0a,
	0x0a, 0x0c, 0x0f, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_90[] = {
	0x6f, 0x46, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_91[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x07, 0x06,
	0x0a, 0x0b, 0x0d, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_92[] = {
	0x6f, 0x54, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_93[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x07, 0x06,
	0x0a, 0x0b, 0x0d, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_94[] = {
	0x6f, 0x62, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_95[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x00, 0x01,
	0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x07, 0x0a,
	0x0c, 0x0f, 0x11, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_96[] = {
	0x6f, 0x70, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_97[] = {
	0x0f, 0x00, 0x39, 0x40, 0xe3, 0x00, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x02, 0x03, 0x06, 0x07, 0x0a,
	0x0d, 0x0f, 0x12, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_98[] = {
	0x1c, 0x00, 0x39, 0x40, 0xea, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_99[] = {
	0x0a, 0x00, 0x39, 0x40, 0xe4, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_100[] = {
	0x0a, 0x00, 0x39, 0x40, 0xe5, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_101[] = {
	0x0a, 0x00, 0x39, 0x40, 0xe6, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_102[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x08, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_103[] = {
	0xe8, 0x11, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_104[] = {
	0xe0, 0x01, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_105[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x00, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_106[] = {
	0x03, 0x00, 0x39, 0x40, 0xbe, 0x47, 0x45, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_107[] = {
	0x6f, 0x05, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_108[] = {
	0xbe, 0x08, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_109[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x03, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_110[] = {
	0x04, 0x00, 0x39, 0x40, 0xc8, 0x01, 0x02, 0x03
};
static char o11_42_02_0a_dsc_cmd_on_cmd_111[] = {
	0x05, 0x00, 0x39, 0x40, 0xff, 0xaa, 0x55, 0xa5,
	0x80, 0xff, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_112[] = {
	0x6f, 0x22, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_113[] = {
	0xfe, 0x06, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_114[] = {
	0x05, 0x00, 0x39, 0x40, 0xff, 0xaa, 0x55, 0xa5,
	0x82, 0xff, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_115[] = {
	0x6f, 0x05, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_116[] = {
	0xf3, 0x11, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_117[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x01, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_118[] = {
	0x6f, 0x05, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_119[] = {
	0x03, 0x00, 0x39, 0x40, 0xc5, 0x0a, 0x0a, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_120[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x00, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_121[] = {
	0x6f, 0x78, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_122[] = {
	0x18, 0x00, 0x39, 0x40, 0xb0, 0x11, 0x00, 0x2a,
	0x00, 0xc2, 0x01, 0xda, 0x03, 0x7c, 0x05, 0xb1,
	0x08, 0x80, 0x0b, 0xee, 0x0f, 0xff, 0x05, 0x55,
	0x05, 0x56, 0x05, 0x55
};
static char o11_42_02_0a_dsc_cmd_on_cmd_123[] = {
	0x6f, 0x6f, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_124[] = {
	0x07, 0x00, 0x39, 0x40, 0xb0, 0x02, 0xd0, 0x05,
	0xa0, 0x02, 0xd0, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_125[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x08, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_126[] = {
	0x17, 0x00, 0x39, 0x40, 0xc1, 0x8c, 0xff, 0xcc,
	0xff, 0xff, 0xcc, 0xff, 0xff, 0xcc, 0xff, 0xff,
	0xec, 0xff, 0x7f, 0xee, 0x7f, 0x7f, 0xff, 0x7f,
	0xff, 0x0e, 0x7f, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_127[] = {
	0x6f, 0x20, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_128[] = {
	0x04, 0x00, 0x39, 0x40, 0xc1, 0x4f, 0x00, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_129[] = {
	0x6f, 0x23, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_130[] = {
	0x15, 0x00, 0x39, 0x40, 0xc1, 0x0c, 0xff, 0xcc,
	0xff, 0xff, 0xcc, 0xff, 0xff, 0xcc, 0xff, 0xff,
	0xec, 0xff, 0x7f, 0xee, 0x7f, 0x7f, 0xcf, 0x7f,
	0x0a, 0xff, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_131[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x07, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_132[] = {
	0xc0, 0x87, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_133[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x01, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_134[] = {
	0x6f, 0x00, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_135[] = {
	0xc3, 0x99, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_136[] = {
	0x6f, 0x30, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_137[] = {
	0xc3, 0x00, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_138[] = {
	0x6f, 0x0b, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_139[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x20, 0x2f
};
static char o11_42_02_0a_dsc_cmd_on_cmd_140[] = {
	0x6f, 0x11, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_141[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x70, 0x2f
};
static char o11_42_02_0a_dsc_cmd_on_cmd_142[] = {
	0x6f, 0x17, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_143[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x26, 0x2f
};
static char o11_42_02_0a_dsc_cmd_on_cmd_144[] = {
	0x6f, 0x1d, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_145[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x20, 0x2f
};
static char o11_42_02_0a_dsc_cmd_on_cmd_146[] = {
	0x6f, 0x23, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_147[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x3a, 0x2f
};
static char o11_42_02_0a_dsc_cmd_on_cmd_148[] = {
	0x6f, 0x0e, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_149[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x62, 0xde
};
static char o11_42_02_0a_dsc_cmd_on_cmd_150[] = {
	0x6f, 0x14, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_151[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x62, 0xde
};
static char o11_42_02_0a_dsc_cmd_on_cmd_152[] = {
	0x6f, 0x1a, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_153[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x62, 0xde
};
static char o11_42_02_0a_dsc_cmd_on_cmd_154[] = {
	0x6f, 0x20, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_155[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x62, 0xde
};
static char o11_42_02_0a_dsc_cmd_on_cmd_156[] = {
	0x6f, 0x26, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_157[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x3f, 0x62, 0xde
};
static char o11_42_02_0a_dsc_cmd_on_cmd_158[] = {
	0x6f, 0x29, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_159[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x11, 0x11, 0x01
};
static char o11_42_02_0a_dsc_cmd_on_cmd_160[] = {
	0x6f, 0x2c, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_161[] = {
	0x04, 0x00, 0x39, 0x40, 0xc3, 0x00, 0x00, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_162[] = {
	0x6f, 0x31, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_163[] = {
	0x03, 0x00, 0x39, 0x40, 0xc3, 0xaa, 0x02, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_164[] = {
	0x6f, 0x33, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_165[] = {
	0x03, 0x00, 0x39, 0x40, 0xc3, 0xaa, 0x02, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_166[] = {
	0x6f, 0x04, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_167[] = {
	0xc3, 0xe3, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_168[] = {
	0x6f, 0x09, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_169[] = {
	0xc3, 0xe4, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_170[] = {
	0x6f, 0x01, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_171[] = {
	0xc3, 0x29, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_172[] = {
	0x6f, 0x06, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_173[] = {
	0xc3, 0x29, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_174[] = {
	0x6f, 0x02, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_175[] = {
	0x03, 0x00, 0x39, 0x40, 0xc3, 0x02, 0x70, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_176[] = {
	0x6f, 0x08, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_177[] = {
	0xc3, 0x70, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_178[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x01, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_179[] = {
	0xea, 0x11, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_180[] = {
	0x6f, 0x07, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_181[] = {
	0x03, 0x00, 0x39, 0x40, 0xea, 0x01, 0x39, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_182[] = {
	0x6f, 0x0b, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_183[] = {
	0xea, 0x11, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_184[] = {
	0x6f, 0x12, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_185[] = {
	0x03, 0x00, 0x39, 0x40, 0xea, 0x01, 0xac, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_186[] = {
	0x6f, 0x1a, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_187[] = {
	0x03, 0x00, 0x39, 0x40, 0xea, 0x01, 0x39, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_188[] = {
	0x6f, 0x1c, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_189[] = {
	0x03, 0x00, 0x39, 0x40, 0xea, 0x01, 0xac, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_190[] = {
	0x6f, 0x04, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_191[] = {
	0xc3, 0xea, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_192[] = {
	0x6f, 0x09, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_193[] = {
	0xc3, 0xea, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_194[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x01, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_195[] = {
	0x6f, 0x2f, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_196[] = {
	0xc3, 0x77, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_197[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x01, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_198[] = {
	0xe4, 0x90, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_199[] = {
	0x6f, 0x0a, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_200[] = {
	0xe4, 0x90, 0x15, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_201[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x05, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_202[] = {
	0x08, 0x00, 0x39, 0x40, 0xcb, 0x13, 0x13, 0x13,
	0x13, 0x13, 0x13, 0x13
};
static char o11_42_02_0a_dsc_cmd_on_cmd_203[] = {
	0x11, 0x00, 0x05, 0x00
};
static char o11_42_02_0a_dsc_cmd_on_cmd_204[] = {
	0x06, 0x00, 0x39, 0x40, 0xf0, 0x55, 0xaa, 0x52,
	0x08, 0x04, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_on_cmd_205[] = {
	0xeb, 0x01, 0x15, 0x00
};

static struct mipi_dsi_cmd o11_42_02_0a_dsc_cmd_on_command[] = {
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_0), o11_42_02_0a_dsc_cmd_on_cmd_0, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_1), o11_42_02_0a_dsc_cmd_on_cmd_1, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_2), o11_42_02_0a_dsc_cmd_on_cmd_2, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_3), o11_42_02_0a_dsc_cmd_on_cmd_3, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_4), o11_42_02_0a_dsc_cmd_on_cmd_4, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_5), o11_42_02_0a_dsc_cmd_on_cmd_5, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_6), o11_42_02_0a_dsc_cmd_on_cmd_6, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_7), o11_42_02_0a_dsc_cmd_on_cmd_7, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_8), o11_42_02_0a_dsc_cmd_on_cmd_8, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_9), o11_42_02_0a_dsc_cmd_on_cmd_9, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_10), o11_42_02_0a_dsc_cmd_on_cmd_10, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_11), o11_42_02_0a_dsc_cmd_on_cmd_11, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_12), o11_42_02_0a_dsc_cmd_on_cmd_12, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_13), o11_42_02_0a_dsc_cmd_on_cmd_13, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_14), o11_42_02_0a_dsc_cmd_on_cmd_14, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_15), o11_42_02_0a_dsc_cmd_on_cmd_15, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_16), o11_42_02_0a_dsc_cmd_on_cmd_16, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_17), o11_42_02_0a_dsc_cmd_on_cmd_17, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_18), o11_42_02_0a_dsc_cmd_on_cmd_18, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_19), o11_42_02_0a_dsc_cmd_on_cmd_19, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_20), o11_42_02_0a_dsc_cmd_on_cmd_20, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_21), o11_42_02_0a_dsc_cmd_on_cmd_21, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_22), o11_42_02_0a_dsc_cmd_on_cmd_22, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_23), o11_42_02_0a_dsc_cmd_on_cmd_23, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_24), o11_42_02_0a_dsc_cmd_on_cmd_24, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_25), o11_42_02_0a_dsc_cmd_on_cmd_25, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_26), o11_42_02_0a_dsc_cmd_on_cmd_26, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_27), o11_42_02_0a_dsc_cmd_on_cmd_27, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_28), o11_42_02_0a_dsc_cmd_on_cmd_28, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_29), o11_42_02_0a_dsc_cmd_on_cmd_29, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_30), o11_42_02_0a_dsc_cmd_on_cmd_30, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_31), o11_42_02_0a_dsc_cmd_on_cmd_31, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_32), o11_42_02_0a_dsc_cmd_on_cmd_32, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_33), o11_42_02_0a_dsc_cmd_on_cmd_33, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_34), o11_42_02_0a_dsc_cmd_on_cmd_34, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_35), o11_42_02_0a_dsc_cmd_on_cmd_35, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_36), o11_42_02_0a_dsc_cmd_on_cmd_36, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_37), o11_42_02_0a_dsc_cmd_on_cmd_37, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_38), o11_42_02_0a_dsc_cmd_on_cmd_38, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_39), o11_42_02_0a_dsc_cmd_on_cmd_39, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_40), o11_42_02_0a_dsc_cmd_on_cmd_40, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_41), o11_42_02_0a_dsc_cmd_on_cmd_41, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_42), o11_42_02_0a_dsc_cmd_on_cmd_42, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_43), o11_42_02_0a_dsc_cmd_on_cmd_43, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_44), o11_42_02_0a_dsc_cmd_on_cmd_44, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_45), o11_42_02_0a_dsc_cmd_on_cmd_45, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_46), o11_42_02_0a_dsc_cmd_on_cmd_46, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_47), o11_42_02_0a_dsc_cmd_on_cmd_47, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_48), o11_42_02_0a_dsc_cmd_on_cmd_48, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_49), o11_42_02_0a_dsc_cmd_on_cmd_49, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_50), o11_42_02_0a_dsc_cmd_on_cmd_50, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_51), o11_42_02_0a_dsc_cmd_on_cmd_51, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_52), o11_42_02_0a_dsc_cmd_on_cmd_52, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_53), o11_42_02_0a_dsc_cmd_on_cmd_53, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_54), o11_42_02_0a_dsc_cmd_on_cmd_54, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_55), o11_42_02_0a_dsc_cmd_on_cmd_55, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_56), o11_42_02_0a_dsc_cmd_on_cmd_56, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_57), o11_42_02_0a_dsc_cmd_on_cmd_57, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_58), o11_42_02_0a_dsc_cmd_on_cmd_58, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_59), o11_42_02_0a_dsc_cmd_on_cmd_59, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_60), o11_42_02_0a_dsc_cmd_on_cmd_60, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_61), o11_42_02_0a_dsc_cmd_on_cmd_61, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_62), o11_42_02_0a_dsc_cmd_on_cmd_62, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_63), o11_42_02_0a_dsc_cmd_on_cmd_63, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_64), o11_42_02_0a_dsc_cmd_on_cmd_64, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_65), o11_42_02_0a_dsc_cmd_on_cmd_65, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_66), o11_42_02_0a_dsc_cmd_on_cmd_66, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_67), o11_42_02_0a_dsc_cmd_on_cmd_67, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_68), o11_42_02_0a_dsc_cmd_on_cmd_68, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_69), o11_42_02_0a_dsc_cmd_on_cmd_69, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_70), o11_42_02_0a_dsc_cmd_on_cmd_70, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_71), o11_42_02_0a_dsc_cmd_on_cmd_71, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_72), o11_42_02_0a_dsc_cmd_on_cmd_72, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_73), o11_42_02_0a_dsc_cmd_on_cmd_73, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_74), o11_42_02_0a_dsc_cmd_on_cmd_74, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_75), o11_42_02_0a_dsc_cmd_on_cmd_75, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_76), o11_42_02_0a_dsc_cmd_on_cmd_76, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_77), o11_42_02_0a_dsc_cmd_on_cmd_77, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_78), o11_42_02_0a_dsc_cmd_on_cmd_78, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_79), o11_42_02_0a_dsc_cmd_on_cmd_79, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_80), o11_42_02_0a_dsc_cmd_on_cmd_80, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_81), o11_42_02_0a_dsc_cmd_on_cmd_81, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_82), o11_42_02_0a_dsc_cmd_on_cmd_82, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_83), o11_42_02_0a_dsc_cmd_on_cmd_83, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_84), o11_42_02_0a_dsc_cmd_on_cmd_84, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_85), o11_42_02_0a_dsc_cmd_on_cmd_85, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_86), o11_42_02_0a_dsc_cmd_on_cmd_86, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_87), o11_42_02_0a_dsc_cmd_on_cmd_87, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_88), o11_42_02_0a_dsc_cmd_on_cmd_88, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_89), o11_42_02_0a_dsc_cmd_on_cmd_89, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_90), o11_42_02_0a_dsc_cmd_on_cmd_90, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_91), o11_42_02_0a_dsc_cmd_on_cmd_91, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_92), o11_42_02_0a_dsc_cmd_on_cmd_92, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_93), o11_42_02_0a_dsc_cmd_on_cmd_93, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_94), o11_42_02_0a_dsc_cmd_on_cmd_94, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_95), o11_42_02_0a_dsc_cmd_on_cmd_95, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_96), o11_42_02_0a_dsc_cmd_on_cmd_96, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_97), o11_42_02_0a_dsc_cmd_on_cmd_97, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_98), o11_42_02_0a_dsc_cmd_on_cmd_98, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_99), o11_42_02_0a_dsc_cmd_on_cmd_99, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_100), o11_42_02_0a_dsc_cmd_on_cmd_100, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_101), o11_42_02_0a_dsc_cmd_on_cmd_101, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_102), o11_42_02_0a_dsc_cmd_on_cmd_102, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_103), o11_42_02_0a_dsc_cmd_on_cmd_103, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_104), o11_42_02_0a_dsc_cmd_on_cmd_104, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_105), o11_42_02_0a_dsc_cmd_on_cmd_105, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_106), o11_42_02_0a_dsc_cmd_on_cmd_106, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_107), o11_42_02_0a_dsc_cmd_on_cmd_107, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_108), o11_42_02_0a_dsc_cmd_on_cmd_108, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_109), o11_42_02_0a_dsc_cmd_on_cmd_109, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_110), o11_42_02_0a_dsc_cmd_on_cmd_110, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_111), o11_42_02_0a_dsc_cmd_on_cmd_111, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_112), o11_42_02_0a_dsc_cmd_on_cmd_112, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_113), o11_42_02_0a_dsc_cmd_on_cmd_113, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_114), o11_42_02_0a_dsc_cmd_on_cmd_114, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_115), o11_42_02_0a_dsc_cmd_on_cmd_115, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_116), o11_42_02_0a_dsc_cmd_on_cmd_116, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_117), o11_42_02_0a_dsc_cmd_on_cmd_117, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_118), o11_42_02_0a_dsc_cmd_on_cmd_118, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_119), o11_42_02_0a_dsc_cmd_on_cmd_119, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_120), o11_42_02_0a_dsc_cmd_on_cmd_120, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_121), o11_42_02_0a_dsc_cmd_on_cmd_121, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_122), o11_42_02_0a_dsc_cmd_on_cmd_122, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_123), o11_42_02_0a_dsc_cmd_on_cmd_123, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_124), o11_42_02_0a_dsc_cmd_on_cmd_124, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_125), o11_42_02_0a_dsc_cmd_on_cmd_125, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_126), o11_42_02_0a_dsc_cmd_on_cmd_126, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_127), o11_42_02_0a_dsc_cmd_on_cmd_127, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_128), o11_42_02_0a_dsc_cmd_on_cmd_128, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_129), o11_42_02_0a_dsc_cmd_on_cmd_129, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_130), o11_42_02_0a_dsc_cmd_on_cmd_130, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_131), o11_42_02_0a_dsc_cmd_on_cmd_131, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_132), o11_42_02_0a_dsc_cmd_on_cmd_132, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_133), o11_42_02_0a_dsc_cmd_on_cmd_133, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_134), o11_42_02_0a_dsc_cmd_on_cmd_134, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_135), o11_42_02_0a_dsc_cmd_on_cmd_135, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_136), o11_42_02_0a_dsc_cmd_on_cmd_136, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_137), o11_42_02_0a_dsc_cmd_on_cmd_137, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_138), o11_42_02_0a_dsc_cmd_on_cmd_138, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_139), o11_42_02_0a_dsc_cmd_on_cmd_139, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_140), o11_42_02_0a_dsc_cmd_on_cmd_140, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_141), o11_42_02_0a_dsc_cmd_on_cmd_141, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_142), o11_42_02_0a_dsc_cmd_on_cmd_142, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_143), o11_42_02_0a_dsc_cmd_on_cmd_143, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_144), o11_42_02_0a_dsc_cmd_on_cmd_144, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_145), o11_42_02_0a_dsc_cmd_on_cmd_145, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_146), o11_42_02_0a_dsc_cmd_on_cmd_146, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_147), o11_42_02_0a_dsc_cmd_on_cmd_147, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_148), o11_42_02_0a_dsc_cmd_on_cmd_148, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_149), o11_42_02_0a_dsc_cmd_on_cmd_149, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_150), o11_42_02_0a_dsc_cmd_on_cmd_150, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_151), o11_42_02_0a_dsc_cmd_on_cmd_151, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_152), o11_42_02_0a_dsc_cmd_on_cmd_152, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_153), o11_42_02_0a_dsc_cmd_on_cmd_153, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_154), o11_42_02_0a_dsc_cmd_on_cmd_154, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_155), o11_42_02_0a_dsc_cmd_on_cmd_155, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_156), o11_42_02_0a_dsc_cmd_on_cmd_156, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_157), o11_42_02_0a_dsc_cmd_on_cmd_157, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_158), o11_42_02_0a_dsc_cmd_on_cmd_158, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_159), o11_42_02_0a_dsc_cmd_on_cmd_159, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_160), o11_42_02_0a_dsc_cmd_on_cmd_160, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_161), o11_42_02_0a_dsc_cmd_on_cmd_161, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_162), o11_42_02_0a_dsc_cmd_on_cmd_162, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_163), o11_42_02_0a_dsc_cmd_on_cmd_163, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_164), o11_42_02_0a_dsc_cmd_on_cmd_164, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_165), o11_42_02_0a_dsc_cmd_on_cmd_165, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_166), o11_42_02_0a_dsc_cmd_on_cmd_166, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_167), o11_42_02_0a_dsc_cmd_on_cmd_167, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_168), o11_42_02_0a_dsc_cmd_on_cmd_168, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_169), o11_42_02_0a_dsc_cmd_on_cmd_169, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_170), o11_42_02_0a_dsc_cmd_on_cmd_170, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_171), o11_42_02_0a_dsc_cmd_on_cmd_171, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_172), o11_42_02_0a_dsc_cmd_on_cmd_172, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_173), o11_42_02_0a_dsc_cmd_on_cmd_173, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_174), o11_42_02_0a_dsc_cmd_on_cmd_174, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_175), o11_42_02_0a_dsc_cmd_on_cmd_175, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_176), o11_42_02_0a_dsc_cmd_on_cmd_176, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_177), o11_42_02_0a_dsc_cmd_on_cmd_177, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_178), o11_42_02_0a_dsc_cmd_on_cmd_178, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_179), o11_42_02_0a_dsc_cmd_on_cmd_179, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_180), o11_42_02_0a_dsc_cmd_on_cmd_180, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_181), o11_42_02_0a_dsc_cmd_on_cmd_181, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_182), o11_42_02_0a_dsc_cmd_on_cmd_182, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_183), o11_42_02_0a_dsc_cmd_on_cmd_183, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_184), o11_42_02_0a_dsc_cmd_on_cmd_184, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_185), o11_42_02_0a_dsc_cmd_on_cmd_185, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_186), o11_42_02_0a_dsc_cmd_on_cmd_186, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_187), o11_42_02_0a_dsc_cmd_on_cmd_187, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_188), o11_42_02_0a_dsc_cmd_on_cmd_188, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_189), o11_42_02_0a_dsc_cmd_on_cmd_189, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_190), o11_42_02_0a_dsc_cmd_on_cmd_190, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_191), o11_42_02_0a_dsc_cmd_on_cmd_191, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_192), o11_42_02_0a_dsc_cmd_on_cmd_192, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_193), o11_42_02_0a_dsc_cmd_on_cmd_193, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_194), o11_42_02_0a_dsc_cmd_on_cmd_194, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_195), o11_42_02_0a_dsc_cmd_on_cmd_195, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_196), o11_42_02_0a_dsc_cmd_on_cmd_196, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_197), o11_42_02_0a_dsc_cmd_on_cmd_197, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_198), o11_42_02_0a_dsc_cmd_on_cmd_198, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_199), o11_42_02_0a_dsc_cmd_on_cmd_199, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_200), o11_42_02_0a_dsc_cmd_on_cmd_200, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_201), o11_42_02_0a_dsc_cmd_on_cmd_201, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_202), o11_42_02_0a_dsc_cmd_on_cmd_202, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_203), o11_42_02_0a_dsc_cmd_on_cmd_203, 120 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_204), o11_42_02_0a_dsc_cmd_on_cmd_204, 0 },
	{ sizeof(o11_42_02_0a_dsc_cmd_on_cmd_205), o11_42_02_0a_dsc_cmd_on_cmd_205, 0 },
};

static char o11_42_02_0a_dsc_cmd_off_cmd_0[] = {
	0x02, 0x00, 0x39, 0x40, 0x28, 0x00, 0xff, 0xff
};
static char o11_42_02_0a_dsc_cmd_off_cmd_1[] = {
	0x02, 0x00, 0x39, 0x40, 0x10, 0x00, 0xff, 0xff
};

static struct mipi_dsi_cmd o11_42_02_0a_dsc_cmd_off_command[] = {
	{ sizeof(o11_42_02_0a_dsc_cmd_off_cmd_0), o11_42_02_0a_dsc_cmd_off_cmd_0, 10 },
	{ sizeof(o11_42_02_0a_dsc_cmd_off_cmd_1), o11_42_02_0a_dsc_cmd_off_cmd_1, 105 },
};

static struct command_state o11_42_02_0a_dsc_cmd_state = {
	.oncommand_state = 0,
	.offcommand_state = 0,
};

static struct commandpanel_info o11_42_02_0a_dsc_cmd_command_panel = {
	/* FIXME: This is a command mode panel */
};

static struct videopanel_info o11_42_02_0a_dsc_cmd_video_panel = {
	.hsync_pulse = 0,
	.hfp_power_mode = 0,
	.hbp_power_mode = 0,
	.hsa_power_mode = 0,
	.bllp_eof_power_mode = 1,
	.bllp_power_mode = 1,
	.traffic_mode = 2,
	/* This is bllp_eof_power_mode and bllp_power_mode combined */
	.bllp_eof_power = 1 << 3 | 1 << 0,
};

static struct lane_configuration o11_42_02_0a_dsc_cmd_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t o11_42_02_0a_dsc_cmd_timings[] = {
	
};

static struct panel_timing o11_42_02_0a_dsc_cmd_timing_info = {
	.tclk_post = 0x00,
	.tclk_pre = 0x00,
};

static struct panel_reset_sequence o11_42_02_0a_dsc_cmd_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 11, 1, 11 },
	.pin_direction = 2,
};

static struct backlight o11_42_02_0a_dsc_cmd_backlight = {
	.bl_interface_type = BL_DCS,
	.bl_min_level = 1,
	.bl_max_level = 16383,
};

static inline void panel_o11_42_02_0a_dsc_cmd_select(struct panel_struct *panel,
						     struct msm_panel_info *pinfo,
						     struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &o11_42_02_0a_dsc_cmd_panel_data;
	panel->panelres = &o11_42_02_0a_dsc_cmd_panel_res;
	panel->color = &o11_42_02_0a_dsc_cmd_color;
	panel->videopanel = &o11_42_02_0a_dsc_cmd_video_panel;
	panel->commandpanel = &o11_42_02_0a_dsc_cmd_command_panel;
	panel->state = &o11_42_02_0a_dsc_cmd_state;
	panel->laneconfig = &o11_42_02_0a_dsc_cmd_lane_config;
	panel->paneltiminginfo = &o11_42_02_0a_dsc_cmd_timing_info;
	panel->panelresetseq = &o11_42_02_0a_dsc_cmd_reset_seq;
	panel->backlightinfo = &o11_42_02_0a_dsc_cmd_backlight;
	pinfo->mipi.panel_on_cmds = o11_42_02_0a_dsc_cmd_on_command;
	pinfo->mipi.panel_off_cmds = o11_42_02_0a_dsc_cmd_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(o11_42_02_0a_dsc_cmd_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(o11_42_02_0a_dsc_cmd_off_command);
	memcpy(phy_db->timing, o11_42_02_0a_dsc_cmd_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_O11_42_02_0A_DSC_CMD_H_ */

// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_mainScreen_screen_init(void)
{
    ui_mainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_mainScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_mainScreen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_mainScreen, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_set_style_bg_color(ui_mainScreen, lv_color_hex(0x111111), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_mainScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_topBar = lv_obj_create(ui_mainScreen);
    lv_obj_set_height(ui_topBar, 36);
    lv_obj_set_width(ui_topBar, lv_pct(100));
    lv_obj_set_align(ui_topBar, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_topBar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_topBar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_topBar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_topBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_topBar, lv_color_hex(0x353536), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_topBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_topBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_topBar, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_topBar, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_topBar, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_topBar, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_clock = lv_label_create(ui_topBar);
    lv_obj_set_width(ui_clock, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_clock, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_clock, 0);
    lv_obj_set_y(ui_clock, 140);
    lv_obj_set_align(ui_clock, LV_ALIGN_CENTER);
    lv_label_set_text(ui_clock, "17:34:21");
    lv_obj_add_flag(ui_clock, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_clear_flag(ui_clock, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_font(ui_clock, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_filler = lv_obj_create(ui_topBar);
    lv_obj_set_width(ui_filler, 203);
    lv_obj_set_height(ui_filler, 28);
    lv_obj_set_align(ui_filler, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_filler, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_filler, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_filler, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_filler, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_filler, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_filler, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_filler, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_batteryBar = lv_bar_create(ui_filler);
    lv_bar_set_value(ui_batteryBar, 25, LV_ANIM_OFF);
    lv_obj_set_width(ui_batteryBar, 150);
    lv_obj_set_height(ui_batteryBar, 10);
    lv_obj_set_align(ui_batteryBar, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_batteryBar, lv_color_hex(0x696A6B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_batteryBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_batteryBar, lv_color_hex(0x0FF216), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_batteryBar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_batteryPercentage = lv_label_create(ui_filler);
    lv_obj_set_width(ui_batteryPercentage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_batteryPercentage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_batteryPercentage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_batteryPercentage, "39%");

    ui_speedGauge = lv_arc_create(ui_mainScreen);
    lv_obj_set_width(ui_speedGauge, 320);
    lv_obj_set_height(ui_speedGauge, 320);
    lv_obj_set_x(ui_speedGauge, 0);
    lv_obj_set_y(ui_speedGauge, -65);
    lv_obj_set_align(ui_speedGauge, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_speedGauge, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_arc_set_range(ui_speedGauge, 0, 60);
    lv_arc_set_value(ui_speedGauge, 50);
    lv_obj_set_style_bg_color(ui_speedGauge, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_speedGauge, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_speedGauge, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_speedGauge, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_speedGauge, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_speedGauge, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_speedGauge, lv_color_hex(0x353536), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_speedGauge, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_speedGauge, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_speedGauge, lv_color_hex(0xF25D0F), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_speedGauge, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_speedGauge, 30, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_speedGauge, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_speedGauge, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_speed = lv_label_create(ui_speedGauge);
    lv_obj_set_width(ui_speed, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_speed, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_speed, LV_ALIGN_CENTER);
    lv_label_set_text(ui_speed, "46");
    lv_obj_clear_flag(ui_speed, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_font(ui_speed, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_kmphLabel = lv_label_create(ui_speedGauge);
    lv_obj_set_width(ui_kmphLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_kmphLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_kmphLabel, 0);
    lv_obj_set_y(ui_kmphLabel, 75);
    lv_obj_set_align(ui_kmphLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_kmphLabel, "km/h");
    lv_obj_set_style_text_color(ui_kmphLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_kmphLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_kmphLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_infoPanel = lv_obj_create(ui_mainScreen);
    lv_obj_set_height(ui_infoPanel, 114);
    lv_obj_set_width(ui_infoPanel, lv_pct(100));
    lv_obj_set_x(ui_infoPanel, -14);
    lv_obj_set_y(ui_infoPanel, -104);
    lv_obj_set_align(ui_infoPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_infoPanel, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui_infoPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_infoPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_infoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_infoPanel, lv_color_hex(0x353536), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_infoPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_infoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_infoPanel, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_infoPanel, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_infoPanel, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_infoPanel, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_motorTempPanel = lv_obj_create(ui_infoPanel);
    lv_obj_set_width(ui_motorTempPanel, 72);
    lv_obj_set_height(ui_motorTempPanel, 50);
    lv_obj_set_align(ui_motorTempPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_motorTempPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_motorTempPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_motorTempPanel,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_radius(ui_motorTempPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_motorTempPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_motorTempPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_motorTempPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_motorTempPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_motorTempPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_motorTempPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_motorTempPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_motorTempLabel = lv_label_create(ui_motorTempPanel);
    lv_obj_set_width(ui_motorTempLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_motorTempLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_motorTempLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_motorTempLabel, "MOTOR");
    lv_obj_clear_flag(ui_motorTempLabel,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(ui_motorTempLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_motorTempLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_motorTempLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_motorTemp = lv_label_create(ui_motorTempPanel);
    lv_obj_set_width(ui_motorTemp, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_motorTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_motorTemp, LV_ALIGN_CENTER);
    lv_label_set_text(ui_motorTemp, "45°C");
    lv_obj_set_style_text_font(ui_motorTemp, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_mosfetTempPanel = lv_obj_create(ui_infoPanel);
    lv_obj_set_width(ui_mosfetTempPanel, 72);
    lv_obj_set_height(ui_mosfetTempPanel, 50);
    lv_obj_set_align(ui_mosfetTempPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_mosfetTempPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_mosfetTempPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_mosfetTempPanel,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_radius(ui_mosfetTempPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_mosfetTempPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_mosfetTempPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_mosfetTempPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_mosfetTempPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_mosfetTempPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_mosfetTempPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_mosfetTempPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_mosfetTempLabel = lv_label_create(ui_mosfetTempPanel);
    lv_obj_set_width(ui_mosfetTempLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_mosfetTempLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_mosfetTempLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_mosfetTempLabel, "MOSFET");
    lv_obj_clear_flag(ui_mosfetTempLabel,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(ui_mosfetTempLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_mosfetTempLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_mosfetTempLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_mosfetTemp = lv_label_create(ui_mosfetTempPanel);
    lv_obj_set_width(ui_mosfetTemp, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_mosfetTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_mosfetTemp, LV_ALIGN_CENTER);
    lv_label_set_text(ui_mosfetTemp, "45°C");
    lv_obj_set_style_text_font(ui_mosfetTemp, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_batteryPanel = lv_obj_create(ui_infoPanel);
    lv_obj_set_width(ui_batteryPanel, 72);
    lv_obj_set_height(ui_batteryPanel, 50);
    lv_obj_set_align(ui_batteryPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_batteryPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_batteryPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_batteryPanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_radius(ui_batteryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_batteryPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_batteryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_batteryPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_batteryPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_batteryPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_batteryPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_batteryPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_batteryLabel = lv_label_create(ui_batteryPanel);
    lv_obj_set_width(ui_batteryLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_batteryLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_batteryLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_batteryLabel, "BATTERY");
    lv_obj_clear_flag(ui_batteryLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(ui_batteryLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_batteryLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_batteryLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_batteryVoltage = lv_label_create(ui_batteryPanel);
    lv_obj_set_width(ui_batteryVoltage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_batteryVoltage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_batteryVoltage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_batteryVoltage, "72.1V");
    lv_obj_set_style_text_font(ui_batteryVoltage, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dutyPanel = lv_obj_create(ui_infoPanel);
    lv_obj_set_width(ui_dutyPanel, 72);
    lv_obj_set_height(ui_dutyPanel, 50);
    lv_obj_set_align(ui_dutyPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_dutyPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_dutyPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dutyPanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_radius(ui_dutyPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dutyPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dutyPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_dutyPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_dutyPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_dutyPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_dutyPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_dutyPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dutyLabel = lv_label_create(ui_dutyPanel);
    lv_obj_set_width(ui_dutyLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_dutyLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_dutyLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_dutyLabel, "DUTY");
    lv_obj_clear_flag(ui_dutyLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(ui_dutyLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_dutyLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_dutyLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_duty = lv_label_create(ui_dutyPanel);
    lv_obj_set_width(ui_duty, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_duty, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_duty, LV_ALIGN_CENTER);
    lv_label_set_text(ui_duty, "55%");
    lv_obj_set_style_text_font(ui_duty, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_odoPanel = lv_obj_create(ui_infoPanel);
    lv_obj_set_width(ui_odoPanel, 72);
    lv_obj_set_height(ui_odoPanel, 50);
    lv_obj_set_align(ui_odoPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_odoPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_odoPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_odoPanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_radius(ui_odoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_odoPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_odoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_odoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_odoPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_odoPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_odoPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_odoPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_odoLabel = lv_label_create(ui_odoPanel);
    lv_obj_set_width(ui_odoLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_odoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_odoLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_odoLabel, "ODO");
    lv_obj_clear_flag(ui_odoLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(ui_odoLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_odoLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_odoLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_odo = lv_label_create(ui_odoPanel);
    lv_obj_set_width(ui_odo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_odo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_odo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_odo, "267km");
    lv_obj_set_style_text_font(ui_odo, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tripPanel = lv_obj_create(ui_infoPanel);
    lv_obj_set_width(ui_tripPanel, 72);
    lv_obj_set_height(ui_tripPanel, 50);
    lv_obj_set_align(ui_tripPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_tripPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_tripPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_tripPanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_radius(ui_tripPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_tripPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tripPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_tripPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_tripPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_tripPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_tripPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_tripPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tripLabel = lv_label_create(ui_tripPanel);
    lv_obj_set_width(ui_tripLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_tripLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_tripLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_tripLabel, "TRIP");
    lv_obj_clear_flag(ui_tripLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(ui_tripLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_tripLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_tripLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_trip = lv_label_create(ui_tripPanel);
    lv_obj_set_width(ui_trip, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_trip, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_trip, LV_ALIGN_CENTER);
    lv_label_set_text(ui_trip, "26.7km");
    lv_obj_add_flag(ui_trip, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_clear_flag(ui_trip, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_font(ui_trip, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_maxSpeedPanel = lv_obj_create(ui_infoPanel);
    lv_obj_set_width(ui_maxSpeedPanel, 72);
    lv_obj_set_height(ui_maxSpeedPanel, 50);
    lv_obj_set_align(ui_maxSpeedPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_maxSpeedPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_maxSpeedPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_maxSpeedPanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_radius(ui_maxSpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_maxSpeedPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_maxSpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_maxSpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_maxSpeedPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_maxSpeedPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_maxSpeedPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_maxSpeedPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_maxSpeedLabel = lv_label_create(ui_maxSpeedPanel);
    lv_obj_set_width(ui_maxSpeedLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_maxSpeedLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_maxSpeedLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_maxSpeedLabel, "MAX");
    lv_obj_clear_flag(ui_maxSpeedLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(ui_maxSpeedLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_maxSpeedLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_maxSpeedLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_maxSpeed = lv_label_create(ui_maxSpeedPanel);
    lv_obj_set_width(ui_maxSpeed, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_maxSpeed, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_maxSpeed, LV_ALIGN_CENTER);
    lv_label_set_text(ui_maxSpeed, "42km/h");
    lv_obj_add_flag(ui_maxSpeed, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_clear_flag(ui_maxSpeed, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_font(ui_maxSpeed, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_avgSpeedPanel = lv_obj_create(ui_infoPanel);
    lv_obj_set_width(ui_avgSpeedPanel, 72);
    lv_obj_set_height(ui_avgSpeedPanel, 50);
    lv_obj_set_align(ui_avgSpeedPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_avgSpeedPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_avgSpeedPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_avgSpeedPanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_radius(ui_avgSpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_avgSpeedPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_avgSpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_avgSpeedPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_avgSpeedPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_avgSpeedPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_avgSpeedPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_avgSpeedPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_avgSpeedLabel = lv_label_create(ui_avgSpeedPanel);
    lv_obj_set_width(ui_avgSpeedLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_avgSpeedLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_avgSpeedLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_avgSpeedLabel, "AVG");
    lv_obj_clear_flag(ui_avgSpeedLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(ui_avgSpeedLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_avgSpeedLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_avgSpeedLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_avgSpeed = lv_label_create(ui_avgSpeedPanel);
    lv_obj_set_width(ui_avgSpeed, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_avgSpeed, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_avgSpeed, LV_ALIGN_CENTER);
    lv_label_set_text(ui_avgSpeed, "12km/h");
    lv_obj_set_style_text_font(ui_avgSpeed, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_clock, ui_event_clock, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_filler, ui_event_filler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_topBar, ui_event_topBar, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_odoLabel, ui_event_odoLabel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_odo, ui_event_odo, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_tripLabel, ui_event_tripLabel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_trip, ui_event_trip, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_maxSpeedLabel, ui_event_maxSpeedLabel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_maxSpeed, ui_event_maxSpeed, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_avgSpeedLabel, ui_event_avgSpeedLabel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_avgSpeed, ui_event_avgSpeed, LV_EVENT_ALL, NULL);

}

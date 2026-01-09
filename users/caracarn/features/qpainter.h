#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"

extern bool lcd_dirty;
extern bool layer_dirty;
extern painter_font_handle_t mononoki, bbt;
extern painter_device_t lcd;
extern painter_device_t lcd_surface;
void display_make_dirty(bool dirty);
bool display_is_dirty(void);
bool display_power_up(void);
bool display_power_down(void);
bool display_post_init_user(void);
void housekeeping_task_keymap(void);
bool display_module_housekeeping_task_keymap(void);

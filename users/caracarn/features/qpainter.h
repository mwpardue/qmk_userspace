#pragma once
#include "quantum.h"

extern bool lcd_dirty;
extern bool layer_dirty;
painter_font_handle_t mononoki, bbt;
painter_device_t lcd;
painter_device_t lcd_surface;

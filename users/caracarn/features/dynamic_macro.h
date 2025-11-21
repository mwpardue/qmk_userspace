#pragma once

#include QMK_KEYBOARD_H

#include "definitions/keycodes.h"
#include "features/process_record_result.h"

typedef struct {
    uint16_t recording;
} dyn_macro_t;

void dyn_macro_play(uint16_t keycode);
void dyn_macro_toggle(uint16_t keycode);
void dyn_macro_reset(void);
void dyn_macro_stop(void);

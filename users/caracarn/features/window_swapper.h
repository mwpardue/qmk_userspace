#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "process_record_result.h"
#include "custom_oneshot_mods.h"
#include "features/transport_sync.h"

typedef enum {
  NONE,
  SWAPPING_START,
  TABBING_START,
  ZOOMING_START,
  BROWSING_START,
  SWAPPING_CONTINUE,
  TABBING_CONTINUE,
  ZOOMING_CONTINUE,
  BROWSING_CONTINUE
} swapper_state_t;

typedef struct {
    swapper_state_t state;
} swapper_t;

process_record_result_t process_window_swapper(uint16_t keycode, keyrecord_t *record);

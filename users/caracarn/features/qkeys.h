#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "process_record_result.h"
#include "features/qmenu.h"
#include "quantum.h"


uint8_t rgb_matrix_get_heatmap_spread(void);
uint8_t rgb_matrix_get_area_limit(void);
#ifdef ACHORDION_ENABLE
uint16_t get_achordion_tapping_term(void);
#endif

process_record_result_t process_qmenu_keys(uint16_t keycode, keyrecord_t *record);

#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "tapdance.h"

uint16_t get_tapping_term_result(uint16_t keycode);
bool get_hold_on_other_key_press_result(uint16_t keycode);
uint16_t get_quick_tap_term_result(uint16_t keycode);
bool get_permissive_hold_result(uint16_t keycode);
uint8_t rgb_matrix_get_heatmap_spread(void);
uint8_t rgb_matrix_get_area_limit(void);
uint16_t get_custom_tapping_term(uint16_t custom_tapping_term);
void increase_modtap_tapping_term(void);
void increase_shift_tapping_term(void);
void increase_gqt_tapping_term(void);
void increase_shift_gqt_tapping_term(void);
void decrease_modtap_tapping_term(void);
void decrease_shift_tapping_term(void);
void decrease_gqt_tapping_term(void);
void decrease_shift_gqt_tapping_term(void);

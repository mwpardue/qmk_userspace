#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "process_record_result.h"
#include "quantum.h"


/*uint8_t rgb_matrix_get_heatmap_spread(void);*/
/*uint8_t rgb_matrix_get_area_limit(void);*/
/*uint16_t get_achordion_tapping_term(void);*/
/*uint16_t get_sft_tapping_term(void);*/
/*uint16_t get_modtap_tapping_term(void);*/
/*uint16_t get_achordion_tapping_term(void);*/
/*uint16_t get_gqt_tapping_term(void);*/
/*uint16_t sget_gqt_tapping_term(void);*/

process_record_result_t process_rgb_matrix_keys(uint16_t keycode, keyrecord_t *record);

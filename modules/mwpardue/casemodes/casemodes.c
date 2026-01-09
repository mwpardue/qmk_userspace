/* Copyright 2021 Andrew Rae ajrae.nv@gmail.com @andrewjrae
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "casemodes.h"
#ifdef QUANTUM_PAINTER_ENABLE
// extern bool lcd_dirty;
#include "features/qpainter.h"
#endif

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(0, 1, 0);
#pragma message \
    "Including casemodes module"

#ifndef DEFAULT_XCASE_SEPARATOR
#define DEFAULT_XCASE_SEPARATOR KC_UNDS
#endif

#ifndef DEFAULT_DELIMITERS_TERMINATE_COUNT
#define DEFAULT_DELIMITERS_TERMINATE_COUNT 2
#endif

#define IS_OSM(keycode) (keycode >= QK_ONE_SHOT_MOD && keycode <= QK_ONE_SHOT_MOD_MAX)

enum xcase_state xcase_state = XCASE_OFF;
static uint16_t xcase_delimiter;
static int8_t distance_to_last_delim = -1;
static int8_t delimiters_count = 0;
#ifdef QUANTUM_PAINTER_ENABLE
// extern bool lcd_dirty;
#endif

// Get xcase state
enum xcase_state get_xcase_state(void) {
    return xcase_state;
}

// Check if xcase is active.
bool is_xcase(void) {
    if (xcase_state == XCASE_OFF) {
        return false;
    } else {
        return true;
    }
}

// Enable xcase and pickup the next keystroke as the delimiter
void enable_xcase(void) {
    xcase_state = XCASE_WAIT;
    dprintln("enabling xcase with default delimiter");
#ifdef QUANTUM_PAINTER_ENABLE
    display_make_dirty(true);
    dprintln("casemode lcd_dirty4");
#endif
}

// Enable xcase with the specified delimiter
void enable_xcase_with(uint16_t delimiter) {
    xcase_state = XCASE_ON;
#ifdef QUANTUM_PAINTER_ENABLE
    display_make_dirty(true);
    dprintln("casemode lcd_dirty5");
#endif
    xcase_delimiter = delimiter;
    distance_to_last_delim = -1;
    delimiters_count = 0;
    dprintf("xcase_delimiter set to %d\n",xcase_delimiter);
}

// Disable xcase
void disable_xcase(void) {
    xcase_state = XCASE_OFF;
    dprintln("disabling xcase");
#ifdef QUANTUM_PAINTER_ENABLE
    display_make_dirty(true);
    dprintln("casemode lcd_dirty1");
#endif
}

// Place the current xcase delimiter
static void place_delimiter(void) {
    if (IS_OSM(xcase_delimiter)) {
        // apparently set_oneshot_mods() is dumb and doesn't deal with handedness for you
        uint8_t mods = xcase_delimiter & 0x10 ? (xcase_delimiter & 0x0F) << 4 : xcase_delimiter & 0x0F;
        set_oneshot_mods(mods);
        dprintf("xcase_delimiter modifier=%d\n",xcase_delimiter);
    } else {
        tap_code16(xcase_delimiter);
        dprintf("xcase_delimiter=%d\n",xcase_delimiter);
    }
}

// Removes a delimiter, used for double tap space exit
static void remove_delimiter(void) {
    if (IS_OSM(xcase_delimiter)) {
        clear_oneshot_mods();
        dprintln("clear_oneshot_mods in xcase");
    } else {
        for (int8_t i = 0; i < DEFAULT_DELIMITERS_TERMINATE_COUNT - 1; i++) {
            tap_code(KC_BSPC);
        }
    }
}

// overrideable function to determine whether the case mode should stop
__attribute__ ((weak))
bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
        // keycode = extract_base_tapping_keycode(keycode);
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word)
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
            case KC_MINS:
            case KC_UNDS:
            case KC_BSPC:
            dprintln("terminate_case_modes");
                // If mod chording disable the mods
                if (record->event.pressed && (get_mods() != 0)) {
                    return true;
                }
                break;
            default:
                dprintln("terminate default action");
                if (record->event.pressed) {
                    return true;
                }
                break;
        }
        return false;
}

/* overrideable function to determine whether to use the default separator on
 * first keypress when waiting for the separator. */
__attribute__ ((weak))
bool use_default_xcase_separator(uint16_t keycode, const keyrecord_t *record) {
    // for example:
    switch (keycode) {
         case KC_A ... KC_Z:
         case KC_1 ... KC_0:
             return true;
         default:
            return false;
     }
     dprintf("default xcase separator\n");
    return false;
}

// process_record_result_t process_case_modes(uint16_t keycode, keyrecord_t *record) {
bool process_record_casemodes(uint16_t keycode, keyrecord_t *record) {
    if (xcase_state) {
        if ((QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX)
            || (QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX)) {
            // Earlier return if this has not been considered tapped yet
            if (record->tap.count == 0)
                return true;
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            dprintln("base tapping keycode");
        }

        if (keycode >= QK_LAYER_TAP && keycode <= QK_ONE_SHOT_LAYER_MAX) {
            // let special keys and normal modifiers go through
            return true;
        }

        if (xcase_state == XCASE_WAIT) {
            // grab the next input to be the delimiter
            if (use_default_xcase_separator(keycode, record)) {
                dprintln("Enabling XCASE using Default Separator from WAIT");
                enable_xcase_with(DEFAULT_XCASE_SEPARATOR);
            }
            else if (record->event.pressed) {
                // factor in mods
                if (get_mods() & MOD_MASK_SHIFT) {
                    keycode = LSFT(keycode);
                }
                else if (get_mods() & MOD_BIT(KC_RALT)) {
                    keycode = RALT(keycode);
                }
                switch (keycode) {
                    case XCASE:
                        return false;
                        dprintln("xcase pcm met first switch condition");
                    default:
                        dprintln("Enabling xcase under XCASE WAIT pcm");
                        enable_xcase_with(keycode);
                        return false;
                }
            }
            else {
                if (IS_OSM(keycode)) {
                    // this catches the OSM release if no other key was pressed
                    set_oneshot_mods(0);
                    enable_xcase_with(keycode);
                    return false;
                }
                // let other special keys go through
                return true;
            }
        }

        if (record->event.pressed) {
            // handle xcase mode
            if (xcase_state == XCASE_ON) {
                // place the delimiter if space is tapped
                if (keycode == KC_SPACE) {
                    delimiters_count++;
                    dprintln("Increaseing delimiter count");
                    if (delimiters_count < DEFAULT_DELIMITERS_TERMINATE_COUNT) {
                        place_delimiter();
                        distance_to_last_delim = 0;
                        return false;
                    }

                    // remove the delimiter and disable modes
                    else {
                        remove_delimiter();
                        disable_xcase();
                        dprintln("Disabling xcase and capsword under XCASE_ON");
                        return true;
                    }
                }
                // decrement distance to delimiter on back space
                else if (keycode == KC_BSPC) {
                    --distance_to_last_delim;
                    if (delimiters_count > 0) {
                        --delimiters_count;
                    }
                }
                // don't increment distance to last delim if negative
                else if (distance_to_last_delim >= 0) {
                    // puts back a one shot delimiter if you we're back to the delimiter pos
                    if (distance_to_last_delim == 0 && (IS_OSM(xcase_delimiter))) {
                        place_delimiter();
                    }
                    ++distance_to_last_delim;
                    delimiters_count = 0;
                }

            } // end XCASE_ON

            // check if the case modes have been terminated
            if (terminate_case_modes(keycode, record)) {
                caps_word_off();
                dprintln("Disabling caps word and xcase under terminate_case_modes");
                disable_xcase();
            }

        } // end if event.pressed

        return true;
    }
    return true;
}

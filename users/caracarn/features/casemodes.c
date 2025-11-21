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

#ifdef CASEMODE_ENABLE
#include "casemodes.h"
#endif
#include "definitions/keycodes.h"
#ifdef HLC_TFT_DISPLAY
    #include "features/qpainter.h"
#endif

/* The caps word concept started with me @iaap on splitkb.com discord.
 * However it has been implemented and extended by many splitkb.com users:
 * - @theol0403 made many improvements to initial implementation
 * - @precondition used caps lock rather than shifting
 * - @dnaq his own implementation which also used caps lock
 * - @sevanteri added underscores on spaces
 * - @metheon extended on @sevanteri's work and added specific modes for
 *   snake_case and SCREAMING_SNAKE_CASE
 * - @baffalop came up with the idea for xcase, which he implements in his own
 *   repo, however this is implemented by @iaap with support also for one-shot-shift.
 * - @sevanteri
 *     - fixed xcase waiting mode to allow more modified keys and keys from other layers.
 *     - Added @baffalop's separator defaulting on first keypress, with a
 *       configurable default separator and overrideable function to determine
 *       if the default should be used.
 */

#ifndef DEFAULT_XCASE_SEPARATOR
#define DEFAULT_XCASE_SEPARATOR KC_UNDS
#endif

#ifndef DEFAULT_DELIMITERS_TERMINATE_COUNT
#define DEFAULT_DELIMITERS_TERMINATE_COUNT 2
#endif

#if CAPS_WORD_IDLE_TIMEOUT > 0
  #if CAPS_WORD_IDLE_TIMEOUT < 100 || CAPS_WORD_IDLE_TIMEOUT > 30000
    // Constrain timeout to a sensible range. With the 16-bit timer, the longest
    // representable timeout is 32768 ms, rounded here to 30000 ms = half a minute.
  #error "caps_word: CAPS_WORD_IDLE_TIMEOUT must be between 100 and 30000 ms"
  #endif
#endif

uint16_t idle_timer = 0;

#define IS_OSM(keycode) (keycode >= QK_ONE_SHOT_MOD && keycode <= QK_ONE_SHOT_MOD_MAX)

// bool to keep track of the caps word state
bool caps_word_on = false;

// enum to keep track of the xcase state
enum xcase_state xcase_state = XCASE_OFF;
// the keycode of the xcase delimiter
static uint16_t xcase_delimiter;
// the number of keys to the last delimiter
static int8_t distance_to_last_delim = -1;
// the number of delimiters in a row
static int8_t delimiters_count = 0;

// Check whether caps word is on
bool caps_word_enabled(void) {
    return caps_word_on;
}

// Enable caps word
void enable_caps_word(void) {
    caps_word_on = true;
    idle_timer = timer_read();
#ifndef CAPSWORD_USE_SHIFT
    if (!host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
#endif
#ifdef HLC_TFT_DISPLAY
    lcd_dirty = true;
    dprintln("casemode lcd_dirty2");
#endif
#ifdef VOYAGER
    STATUS_LED_3(true);
#endif
}

// Disable caps word
void disable_caps_word(void) {
    dprintln("Disable Caps_Word");
    caps_word_on = false;
#ifndef CAPSWORD_USE_SHIFT
    if (host_keyboard_led_state().caps_lock) {
        dprintln("Disabling Caps Word by Caps Lock");
        tap_code(KC_CAPS);
    }
#else
    unregister_mods(MOD_LSFT);
#endif
#ifdef HLC_TFT_DISPLAY
    lcd_dirty = true;
    dprintln("casemode lcd_dirty3");
#endif
#ifdef VOYAGER
    STATUS_LED_3(false);
#endif
}

// Toggle caps word
void toggle_caps_word(void) {
    if (caps_word_on) {
        disable_caps_word();
    }
    else {
        enable_caps_word();
    }
}

void caps_word_idle_timer(void) {
  if (xcase_state != XCASE_ON && (timer_read() > idle_timer + CAPS_WORD_IDLE_TIMEOUT)) {
    if (caps_word_on) {
      disable_caps_word();
    }
  }
}

// Get xcase state
enum xcase_state get_xcase_state(void) {
    return xcase_state;
}

// Enable xcase and pickup the next keystroke as the delimiter
void enable_xcase(void) {
    xcase_state = XCASE_WAIT;
#ifdef HLC_TFT_DISPLAY
    lcd_dirty = true;
    dprintln("casemode lcd_dirty4");
#endif
}

// Enable xcase with the specified delimiter
void enable_xcase_with(uint16_t delimiter) {
    xcase_state = XCASE_ON;
#ifdef HLC_TFT_DISPLAY
    lcd_dirty = true;
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
#ifdef HLC_TFT_DISPLAY
    lcd_dirty = true;
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
            case UOL_THM:
            case LUTHUM1:
            case LUTHUM2:
            case LIL_THM:
            case CLIL_THM:
            case LOL_THM:
            case UOR_THM:
            case LIR_THM:
            case LOR_THM:
            case CLOR_THM:
            case CLOL_THM:
            case SLOR_THM:
            case SLOL_THM:
            case CRUTHUM2:
            case CLUTHUM2:
            case RUTHUM2:
            case RUTHUM1:
            case KC_UP:
            case KC_DOWN:
            case KC_RIGHT:
            case KC_LEFT:
            case KC_LPRN:
            case KC_RPRN:
            case KC_LBRC:
            case KC_RBRC:
            case KC_LCBR:
            case KC_RCBR:
            case KC_SCLN:
            case KC_COLN:
            case UIL_THM:
            case UIR_THM:
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
    // switch (keycode) {
    //      case KC_A ... KC_Z:
    //      case KC_1 ... KC_0:
    //          return true;
    //      case (XCASE & 0xff):
    //      case IL_THUM:
    //      default:
    //         return false;
    //  }
    //  dprintf("default xcase separator\n");
    return false;
}

// process_record_result_t process_case_modes(uint16_t keycode, keyrecord_t *record) {
bool process_case_modes(uint16_t keycode, const keyrecord_t *record) {
    if (caps_word_on || xcase_state) {
        if ((QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX)
            || (QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX)) {
            // Earlier return if this has not been considered tapped yet
            if (record->tap.count == 0)
                return true;
            // keycode = keycode & 0xFF;
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            dprintln("base tapping keycode");
            // keycode = extract_base_tapping_keycode(keycode);
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
                    case RUTHUM2:
                    case XCASE:
                    case (XCASE & 0xff):
                    // case SP_CAP:
                    // case (SP_CAP & 0xFF):
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
                        disable_caps_word();
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
                disable_caps_word();
                dprintln("Disabling caps word and xcase under terminate_case_modes");
                disable_xcase();
            }

            if (caps_word_on || host_keyboard_led_state().caps_lock) {
              idle_timer = timer_read();
            }

#ifdef CAPSWORD_USE_SHIFT
            else if (caps_word_on){
                switch (keycode) {
                    // Keycodes to ignore (don't disable caps word)
                    case KC_A ... KC_Z:
                    case KC_1 ... KC_0:
                    case KC_MINS:
                    case KC_UNDS:
                        tap_code16(LSFT(keycode));
                        break;
                        return false;
                    default:
                        break;
                }
            }
#endif

        } // end if event.pressed

        return true;
    }
    return true;
}

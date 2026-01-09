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

#include "leader.h"
#include "secrets.h"
#include "features/rgb_matrix_custom.h"

#ifdef QUANTUM_PAINTER_ENABLE
    #include "features/qpainter.h"
#endif

#include "features/dynamic_macro.h"
#include "caracarn_runtime.h"

#include <string.h>

#ifndef LEADER_ESC_KEY
#define LEADER_ESC_KEY KC_ESC
#endif

menu_t menu = {.state = NO_MENU};
static leader_func_t leader_func = NULL;

#ifdef LEADER_DISPLAY_STR

#ifndef LEADER_DISPLAY_LEN
#define LEADER_DISPLAY_LEN 8
#endif

static const char keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'};

static uint8_t leader_display_size;
static const char space_ascii[] = "SPC";
static char leader_display[LEADER_DISPLAY_LEN + 1]; // add space for null terminator

static void update_leader_display(uint16_t keycode) {
    leader_display[leader_display_size] = ' ';
    ++leader_display_size;
    if (leader_display_size < LEADER_DISPLAY_LEN) {
        switch (keycode) {
            case KC_SPC:
                memcpy(leader_display + leader_display_size, space_ascii, sizeof(space_ascii));
                leader_display_size += sizeof(space_ascii);
                break;
            default:
                if (keycode < sizeof(keycode_to_ascii_lut)) {
                    leader_display[leader_display_size] = keycode_to_ascii_lut[keycode];
                }
                else {
                    leader_display[leader_display_size] = '?';
                }
                ++leader_display_size;
                break;
        }
        leader_display[leader_display_size] = '-';
    }
}

char *leader_display_str(void) {
    return leader_display;
}
#endif

void *adjust_layer(void) {
    #ifdef QMENU_ENABLE
        painter_menu.state.menu_selector = 1;
        painter_menu.state.submenu_selector = 1;
        // qp_clear(lcd_surface);
    #endif
        layer_on(_ADJUST);
    return NULL;
}

void *leader_tips_func(uint16_t keycode) {
        switch (keycode) {
            case KC_A:
                send_string_with_delay("@trueipsolutions.com", MACRO_TIMER);
                break;
            case KC_T:
                send_string_with_delay("trueipsolutions.com", MACRO_TIMER);
                break;
            default:
                break;
        }
        return NULL;
    }

void *leader_adjust_func(uint16_t keycode) {
        switch (keycode) {
            case KC_D:
                adjust_layer();
                break;
            default:
                break;
        }
        return NULL;
    }
#ifdef DYNAMIC_MACRO_ENABLE
void *leader_dmacro_func(uint16_t keycode) {
        switch (keycode) {
            case KC_1:
                dyn_macro_toggle(QK_DYNAMIC_MACRO_RECORD_START_1);
                break;
            case KC_2:
                dyn_macro_toggle(QK_DYNAMIC_MACRO_RECORD_START_2);
                break;
            case KC_S:
                dyn_macro_stop();
                break;
            default:
                break;
        }
        return NULL;
    }
#endif

#ifdef DYNAMIC_MACRO_ENABLE
void *leader_dmacro_play_func(uint16_t keycode) {
        switch (keycode) {
            case KC_1:
                dyn_macro_play(QK_DYNAMIC_MACRO_PLAY_1);
                break;
            case KC_2:
                dyn_macro_play(QK_DYNAMIC_MACRO_PLAY_2);
                break;
            default:
                break;
        }
        return NULL;
    }
#endif

void *leader_email_func(uint16_t keycode) {
        switch (keycode) {
            case KC_C:
                send_string_with_delay("@caracarn.anonaddy.com", MACRO_TIMER);
                break;
            case KC_T:
                send_string_with_delay("mpardue@trueipsolutions.com", MACRO_TIMER);
                break;
            default:
                break;
        }
        return NULL;
    }

void *leader_keyb_func(uint16_t keycode) {
        switch (keycode) {
            case KC_C:
                tap_code16(KC_CAPS);
                break;
            default:
                break;
        }
        return NULL;
    }

void *leader_reset_func(uint16_t keycode) {
        switch (keycode) {
            case KC_R:
                reset_keyboard();
                break;
            default:
                break;
        }
        return NULL;
    }

void *leader_screen_func(uint16_t keycode) {
        switch (keycode) {
            case KC_A:
                tap_code16(G(S(A(C(KC_A)))));
                break;
            case KC_S:
                tap_code16(LGUI(LSFT(KC_4)));
                break;
            case KC_C:
                tap_code16(LGUI(LSFT(LCTL(KC_4))));
                break;
            default:
                break;
        }
        return NULL;
    }

void *leader_pass_func(uint16_t keycode) {
    switch (keycode) {
        case KC_5:
            send_string_with_delay(secrets[4], MACRO_TIMER);
            break;
        case KC_A:
            send_string_with_delay(secrets[0], MACRO_TIMER);
            break;
        case KC_B:
            send_string_with_delay(secrets[2], MACRO_TIMER);
            break;
        case KC_D:
            send_string_with_delay(secrets[12], MACRO_TIMER);
            break;
        case KC_J:
            send_string_with_delay(secrets[3], MACRO_TIMER);
            break;
        case KC_I:
            send_string_with_delay(secrets[14], MACRO_TIMER);
            break;
        case KC_L:
            send_string_with_delay(secrets[9], MACRO_TIMER);
            break;
        case KC_N:
            send_string_with_delay(secrets[11], MACRO_TIMER);
            break;
        case KC_O:
            send_string_with_delay(secrets[6], MACRO_TIMER);
            break;
        case KC_P:
            send_string_with_delay(secrets[7], MACRO_TIMER);
            break;
        case KC_R:
            send_string_with_delay(secrets[13], MACRO_TIMER);
            break;
        case KC_S:
            send_string_with_delay(secrets[8], MACRO_TIMER);
            break;
        case KC_T:
            send_string_with_delay(secrets[5], MACRO_TIMER);
            break;
        case KC_U:
            send_string_with_delay(secrets[15], MACRO_TIMER);
            break;
        case KC_Q:
            send_string_with_delay(secrets[10], MACRO_TIMER);
            break;
        case KC_Y:
            send_string_with_delay(secrets[16], MACRO_TIMER);
            break;
        case KC_4:
            send_string_with_delay(secrets[17], MACRO_TIMER);
            break;
        case KC_V:
            send_string_with_delay(secrets[18], MACRO_TIMER);
            break;
        case KC_1:
            send_string_with_delay(secrets[19], MACRO_TIMER);
            break;
        case KC_M:
            send_string_with_delay(secrets[1], MACRO_TIMER);
            break;
        default:
            break;
    }
    return NULL;
}

// The entry point for leader sequenc functions
__attribute__ ((weak))
void *leader_start_func(uint16_t keycode) {
    switch (keycode) {
        case KC_A:
            return leader_adjust_func;
            break;
        case KC_T:
            return leader_tips_func;
            break;
        case KC_E:
            return leader_email_func;
            break;
        case KC_K:
            return leader_keyb_func;
            break;
        case KC_S:
            return leader_screen_func;
            break;
#ifdef DYNAMIC_MACRO_ENABLE
        case KC_P:
            return leader_dmacro_play_func;
            break;
#endif
        case KC_R:
            return leader_reset_func;
            break;
#ifdef DYNAMIC_MACRO_ENABLE
        case KC_M:
            return leader_dmacro_func;
            break;
#endif
    default:
        return NULL;
    }
    return NULL;
}

// Check to see if we are leading
bool is_leading(void) {
    if (menu.state == LEADING_MENU) {
        return true;
    } else {
        return false;
    }
    // return leading;
}

// Check to see if we are leading
bool is_passing(void) {
    if (menu.state == PASSING_MENU) {
        return true;
    } else {
        return false;
    }
    // return leading;
}

// Start leader sequence
void start_leading(void) {
    menu.state = LEADING_MENU;
    leader_func = leader_start_func;
#ifdef LEADER_DISPLAY_STR
    memset(leader_display, 0, sizeof(leader_display));
    leader_display[0] = 'L';
    leader_display[1] = 'D';
    leader_display[2] = 'R';
    leader_display[3] = '-';
    leader_display_size = 3;
#endif
#ifdef QUANTUM_PAINTER_ENABLE
    display_make_dirty(true);
    dprintln("leader lcd_dirty2");
#endif
}

void start_pass_leading(void) {
    // leading = true;
    menu.state = PASSING_MENU;
    leader_func = leader_pass_func;
#ifdef LEADER_DISPLAY_STR
    memset(leader_display, 0, sizeof(leader_display));
    leader_display[0] = 'P';
    leader_display[1] = 'S';
    leader_display[2] = 'W';
    leader_display[3] = '-';
    leader_display_size = 3;
#endif
#ifdef QUANTUM_PAINTER_ENABLE
    display_make_dirty(true);
    dprintln("leader lcd_dirty3");
#endif
}

// Stop leader sequence
void stop_leading(void) {
    menu.state = NO_MENU;
    leader_func = NULL;
#ifdef LEADER_DISPLAY_STR
    leader_display[leader_display_size] = ' ';
#endif
#ifdef QUANTUM_PAINTER_ENABLE
    display_make_dirty(true);
    dprintln("leader lcd_dirty1");
#endif
}

// Process keycode for leader sequences
bool process_leader(uint16_t keycode, const keyrecord_t *record) {
    if ((is_leading() || is_passing()) && record->event.pressed) {
        // Get the base keycode of a mod or layer tap key
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0)
                    return true;
                keycode = keycode & 0xFF;
                break;
            default:
                break;
        }

        // let through anything above that's normal keyboard keycode or a mod
        if (keycode > QK_MODS_MAX || IS_MODIFIER_KEYCODE(keycode)) {
            return true;
        }
        // early exit if the esc key was hit
        if (keycode == LEADER_ESC_KEY) {
            stop_leading();
            return false;
        }

#ifdef LEADER_DISPLAY_STR
        update_leader_display(keycode);
#endif
        // update the leader function
        leader_func = leader_func(keycode);
        // Put RGB changes here since this runs each time a key is pressed
        if (leader_func == NULL) {
            stop_leading();
        }
        return false;
    }
    return true;
}

#include QMK_KEYBOARD_H

#include "combos.h"

#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
    menu_t menu;
#endif

#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
#endif

// extern enum xcase_state xcase_state;
// extern bool caps_word_on;

// extern os_t os;

#ifndef DEFAULT_MOD_ENABLE
    #ifndef SHORTCUTS_ENABLE
        bool should_send_ctrl(bool isWindowsOrLinux, bool isOneShotShift) {
            return (isWindowsOrLinux && !isOneShotShift) || (!isWindowsOrLinux && isOneShotShift);
        }
    #endif
#endif

bool get_combo_must_tap(uint16_t index, combo_t *combo) {

    uint16_t key;
    uint8_t idx = 0;
    bool combo_must_tap = false;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                combo_must_tap = true;
                break;
            default:
                combo_must_tap = false;
                break;
        }
        if (!combo_must_tap) {
            return false;
        }
        idx += 1;
    }
    return combo_must_tap;
}

uint8_t combo_ref_from_layer(uint8_t layer) {
    switch (get_highest_layer(layer_state)) {
        case _NAVIGATION:
            return _NAVIGATION;
        default:
            return _BASE;
    }
    return layer;
}

 process_record_result_t process_combos(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case SM_LOGN:
            if (record->event.pressed) {
                    send_string(secrets[1]);
                    tap_code16(KC_ENTER);
                    return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        // case SM_CW:
        //     if (record->event.pressed) {
        //             toggle_caps_word();
        //             return PROCESS_RECORD_RETURN_FALSE;
        //     }
        //     break;

        case SM_PAR:
            if (record->event.pressed) {
                tap_code16(KC_LPRN);
                tap_code16(KC_RPRN);
                tap_code16(KC_LEFT);
            }
            break;

        case SM_CUR:
            if (record->event.pressed) {
                tap_code16(KC_LCBR);
                tap_code16(KC_RCBR);
                tap_code16(KC_LEFT);
            }
            break;

        case SM_BRC:
            if (record->event.pressed) {
                tap_code16(KC_LBRC);
                tap_code16(KC_RBRC);
                tap_code16(KC_LEFT);
            }
            break;

        case SM_ANG:
            if (record->event.pressed) {
                tap_code16(KC_LT);
                tap_code16(KC_GT);
                tap_code16(KC_LEFT);
            }
            break;

        case LEADER:
        if (record->event.pressed) {
                start_leading();
        }
        break;

}


    return PROCESS_RECORD_CONTINUE;
}

#include "select_word.h"
#include "../caracarn_runtime.h"

extern user_config_t user_config;

void clear_locked_and_oneshot_mods(void) {
    uint8_t oneshot_locked_mods = get_oneshot_locked_mods();
    uint8_t oneshot_mods = get_oneshot_mods();
    if (oneshot_locked_mods || oneshot_mods) {
        clear_oneshot_mods();
        clear_oneshot_locked_mods();
        unregister_mods(MOD_LSFT);
        unregister_mods(MOD_LCTL);
        unregister_mods(MOD_LALT);
        unregister_mods(MOD_RALT);
        unregister_mods(MOD_LGUI);
    }
//    dyn_macro_reset();
}

select_word_t select_word = {.state = STATE_NONE};

process_record_result_t process_select_word(uint16_t keycode, keyrecord_t* record) {
    if (keycode == MC_SELW && record->event.pressed) {
        bool isShifted = get_mods() & MOD_MASK_SHIFT || get_oneshot_mods() & MOD_MASK_SHIFT ||
                         get_oneshot_locked_mods() & MOD_MASK_SHIFT;
        if (isShifted || select_word.state == STATE_LINE_SELECTED) {
            // Select Line
            clear_mods();
            clear_locked_and_oneshot_mods();
            if (select_word.state == STATE_NONE) {
                tap_code(KC_HOME);
                register_mods(MOD_LSFT);
                tap_code(KC_END);
                select_word.state = STATE_FIRST_LINE;
            } else {
                register_mods(MOD_LSFT);
                register_code(KC_DOWN);
                select_word.state = STATE_LINE;
            }
        } else {
            // Select Word
            if (user_config.system.os == MACOS) {
                register_code(KC_LALT);
            } else {
                register_code(KC_LCTL);
            }
            if (select_word.state == STATE_NONE) {
                tap_code(KC_RIGHT);
                tap_code(KC_LEFT);
            }
            register_mods(MOD_LSFT);
            register_code(KC_RGHT);
            select_word.state = STATE_WORD;
        }
        return PROCESS_RECORD_RETURN_FALSE;
    }

    switch (select_word.state) {
        case STATE_WORD:
            unregister_code(KC_RGHT);
            unregister_mods(MOD_LSFT);
            if (user_config.system.os == MACOS) {
                unregister_code(KC_LALT);
            } else {
                unregister_code(KC_LCTL);
            }
            select_word.state = STATE_WORD_SELECTED;
            break;

        case STATE_FIRST_LINE:
            unregister_mods(MOD_LSFT);
            select_word.state = STATE_LINE_SELECTED;
            break;

        case STATE_LINE:
            unregister_mods(MOD_LSFT);
            unregister_code(KC_DOWN);
            select_word.state = STATE_LINE_SELECTED;
            break;

        case STATE_WORD_SELECTED:
        case STATE_LINE_SELECTED:
            if (keycode != MC_SELW && record->event.pressed) {
                unregister_mods(MOD_LSFT);
                // tap_code(KC_RGHT);
                select_word.state = STATE_NONE;
                return PROCESS_RECORD_CONTINUE;
            }
        default:
            select_word.state = STATE_NONE;
    }

    return PROCESS_RECORD_CONTINUE;
}

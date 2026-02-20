#include QMK_KEYBOARD_H

#include "smart_thumb_keys.h"
#include "leader.h"
#include "features/custom_shortcuts.h"
#include "modules/mwpardue/casemodes/casemodes.h"
#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
#endif

#ifdef QUANTUM_PAINTER_ENABLE
    #include "features/qpainter.h"
#endif

uint8_t smart_mods = 0;
extern enum xcase_state xcase_state;
// extern bool caps_word_on;
extern uint16_t idle_timer;

bool should_send_ctrl(bool isWindowsOrLinux, bool isOneShotShift) {
    return (isWindowsOrLinux && !isOneShotShift) || (!isWindowsOrLinux && isOneShotShift);
}

process_record_result_t process_smart_thumb_keys(uint16_t keycode, keyrecord_t *record) {
    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotShift       = get_oneshot_mods() & MOD_MASK_SHIFT || isOneShotLockedShift;
    bool isOneShotCtrl        = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;
    bool isOneShotAlt         = get_oneshot_mods() & MOD_MASK_ALT || get_oneshot_locked_mods() & MOD_MASK_ALT;
    // bool isOneShotGui         = get_oneshot_mods() & MOD_MASK_GUI || get_oneshot_locked_mods() & MOD_MASK_GUI;
    bool isCtrl               = get_mods() & MOD_MASK_CTRL || isOneShotCtrl;
    bool isShift               = get_mods() & MOD_MASK_SHIFT || isOneShotShift || isOneShotLockedShift;
    bool isAlt               = get_mods() & MOD_MASK_ALT || isOneShotAlt;
    // bool isGui               = get_mods() & MOD_MASK_GUI || isOneShotGui;



    switch (keycode) {
        case CLIL_THM:
        case MEH_ESC:
        case SFT_ESC:
            if (record->event.pressed) {
                if (record->tap.count > 0) {
                        smart_escape();
            return PROCESS_RECORD_RETURN_FALSE;
                    }
        return PROCESS_RECORD_CONTINUE;
                }
        break;

        case XCTHUM:
            if (record->event.pressed) {
                dprintln("XCTHUM pressed");
                    caps_word_on();
                // if (xcase_state == XCASE_ON || xcase_state == XCASE_WAIT) {
                //     disable_xcase();
                // } else {
                //     enable_xcase();
                // }
            return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case GMG_CW:
            if (record->event.pressed) {
                if (record->tap.count > 0) {
                        if (isAlt) {
                            enable_xcase();
                            dprintln("enable_xcase");
                        }

                        if (isCtrl || host_keyboard_led_state().caps_lock) {
                            tap_code16(KC_CAPS);
                            dprintln("caps_lock");
                        }

                        if (isShift) {
                            caps_word_on();
                            dprintln("caps_word_on");
                            return PROCESS_RECORD_RETURN_FALSE;
                        }

                        if (get_mods() == 0) {
                            if (is_caps_word_on()) {
                                caps_word_off();
                                dprintln("caps_word_off");
                            } else {
                                set_oneshot_mods(MOD_BIT(KC_LSFT));
                                dprintln("oneshot_shift");
                            }
                        }
                return PROCESS_RECORD_RETURN_FALSE;
                }
            return PROCESS_RECORD_CONTINUE;
            }
            break;

        case MEH_XCS:
            if (record->event.pressed) {
                if (record->tap.count > 0) {
                    if (isCtrl || host_keyboard_led_state().caps_lock) {
                        tap_code16(KC_CAPS);
                        dprintln("caps_lock");
                        return PROCESS_RECORD_RETURN_FALSE;
                    }

                    if (isShift) {
                        caps_word_on();
                        dprintln("SHIFT caps_word_on");
                    }

                    enable_xcase();
                    dprintln("enable xcase");
                    return PROCESS_RECORD_RETURN_FALSE;
                }
            return PROCESS_RECORD_CONTINUE;
            }
            break;

        case XCASE:
            if (record->event.pressed) {
                if (isCtrl || host_keyboard_led_state().caps_lock) {
                    tap_code16(KC_CAPS);
                    dprintln("caps_lock");
                    return PROCESS_RECORD_RETURN_FALSE;
                }

                if (isShift) {
                    caps_word_on();
                    dprintln("SHIFT caps_word_on");
                }

                enable_xcase();
                dprintln("enable xcase");
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_RETURN_FALSE;
        break;

        case SXCASE:
            if (record->event.pressed) {
                    caps_word_on();
                    dprintln("enable strong xcase");
                    enable_xcase();
            }
            return PROCESS_RECORD_RETURN_FALSE;
        break;

    }
    return PROCESS_RECORD_CONTINUE;
}

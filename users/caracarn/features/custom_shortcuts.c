#include QMK_KEYBOARD_H

#include "caracarn.h"
#include "custom_shortcuts.h"
#include "caracarn_runtime.h"
#include "definitions/keycodes.h"
#include "features/taphold.h"

#ifdef QMENU_ENABLE
#include "features/qhelper.h"
#include "features/qpainter.h"
#endif

#ifdef CUSTOM_LEADER_ENABLE
  #include "leader.h"
#endif

// #ifdef CASEMODE_ENABLE
    #include "modules/mwpardue/casemodes/casemodes.h"
// #endif

// extern enum xcase_state xcase_state;

void smart_escape(void) {
    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotLockedCtrl = get_oneshot_locked_mods() & MOD_MASK_CTRL;
    bool isOneShotLockedAlt = get_oneshot_locked_mods() & MOD_MASK_ALT;
    bool isOneShotLockedGui = get_oneshot_locked_mods() & MOD_MASK_GUI;
    bool isAnyOneShotLockedMod = isOneShotLockedShift || isOneShotLockedCtrl || isOneShotLockedAlt || isOneShotLockedGui;
    // bool isXcase = (xcase_state == XCASE_WAIT) && (xcase_state == XCASE_ON);
    bool kbFeature = is_caps_word_on() || \
        isAnyOneShotLockedMod || \
        is_leading() || \
        host_keyboard_led_state().caps_lock || \
        is_xcase() || \
        is_passing();

    if (kbFeature) {
        if (host_keyboard_led_state().caps_lock) {
            dprintln("Disabling Caps Lock");
            tap_code16(KC_CAPS);
        }
        caps_word_off();
        dprintln("Disabling keyboard feature");
        disable_xcase();
        clear_locked_and_oneshot_mods();
        stop_leading();
        return;
    } else if (IS_LAYER_ON(_FUNCTION) || IS_LAYER_ON(_ADJUST) || IS_LAYER_ON(_HEX)) {
        layer_off(_FUNCTION);
        layer_off(_ADJUST);
        layer_off(_HEX);
        dprintln("SM_ESC function/adjust layer off");
        return;
    } else {
        tap_code16(KC_ESC);
        dprintln("SM_ESC default");
    }
}

process_record_result_t process_custom_shortcuts(uint16_t keycode, keyrecord_t *record) {
    // bool isXcase = (xcase_state == XCASE_WAIT) && (xcase_state == XCASE_ON);
    bool isMacOS = user_config.system.os == MACOS;
    // bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    // bool isOneShotShift       = get_oneshot_mods() & MOD_MASK_SHIFT || isOneShotLockedShift;
    // bool isOneShotCtrl        = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;
    // bool isOneShotAlt         = get_oneshot_mods() & MOD_MASK_ALT || get_oneshot_locked_mods() & MOD_MASK_ALT;
    // bool isOneShotGui         = get_oneshot_mods() & MOD_MASK_GUI || get_oneshot_locked_mods() & MOD_MASK_GUI;
    // bool isCtrl               = get_mods() & MOD_MASK_CTRL || isOneShotCtrl;
    // bool isShift               = get_mods() & MOD_MASK_SHIFT || isOneShotShift || isOneShotLockedShift;
    // bool isAlt               = get_mods() & MOD_MASK_ALT || isOneShotAlt;
    // bool isGui               = get_mods() & MOD_MASK_GUI || isOneShotGui;

    switch (keycode) {

        case SM_CW:
            if (record->event.pressed) {
                #ifdef CASEMODE_ENABLE
                if (isXcase || caps_word_on) {
                    disable_xcase();
                    disable_caps_word();
                    return PROCESS_RECORD_RETURN_FALSE;
                }
                if (isCtrl || host_keyboard_led_state().caps_lock) {
                    tap_code16(KC_CAPS);
                }

                if (isAlt) {
                    enable_xcase();
                }

                if (isShift) {
                    enable_caps_word();
                }

                if (!isCtrl && !isAlt && !isShift && !host_keyboard_led_state().caps_lock) {
                    toggle_caps_word();
                }
                #endif
                #ifdef CAPS_WORD_ENABLE
                    caps_word_toggle();
                #endif
                    return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case SM_CAP:
            if (record->event.pressed) {
                    tap_code_delay(KC_CAPS, 500);
                return PROCESS_RECORD_RETURN_FALSE;
            }
        return PROCESS_RECORD_RETURN_FALSE;
        break;

        // case RHM_SCN:
        //     if (record->event.pressed) {
        //         if (record->tap.count > 0) {
        //                 tap_code16(KC_COLN);
        //                 return PROCESS_RECORD_RETURN_FALSE;
        //         }
        //     return PROCESS_RECORD_CONTINUE;
        //     }
        //     break;

        case QWERTY:
            if (record->event.pressed) {
                dprintf("Base layer changed to QWERTY\n");
                set_single_persistent_default_layer(_BASE);
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK_DH);
                dprintf("Base layer changed to COLEMAK\n");
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case DF_LAYR:
            if (record->event.pressed) {
                switch (get_highest_layer(default_layer_state)) {
                    case _BASE:
                        set_single_persistent_default_layer(_GAMING);
                        break;
                    case _GAMING:
                        set_single_persistent_default_layer(_COLEMAK_DH);
                        break;
                    case _COLEMAK_DH:
                        set_single_persistent_default_layer(_BASE);
                        break;
                    default:
                        set_single_persistent_default_layer(_BASE);
                        break;
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case DF_LYR1:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE);
                layer_off(_FUNCTION);
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case DF_LYR2:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAMING);
                layer_off(_FUNCTION);
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case DF_LYR3:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK_DH);
                layer_off(_FUNCTION);
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case DF_LYR4:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAMENUM);
                layer_off(_FUNCTION);
            }
            return PROCESS_RECORD_RETURN_FALSE;

       case PASSPAL:
            if (record->event.pressed) {
                  start_pass_leading();
                }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

         case SEL_WRD:
            if (record->event.pressed) {
                if (isMacOS) {
                  tap_code16(A(KC_LEFT));
                  tap_code16(A(S(KC_RIGHT)));
                } else {
                    tap_code16(C(KC_LEFT));
                    tap_code16(C(S(KC_RIGHT)));
                }
            return PROCESS_RECORD_RETURN_FALSE;
            }

         case SEL_LIN:
            if (record->event.pressed) {
                if (isMacOS) {
                  tap_code16(G(KC_LEFT));
                  tap_code16(G(S(KC_RIGHT)));
                } else {
                    tap_code16(KC_HOME);
                    tap_code16(S(KC_END));
                }
            return PROCESS_RECORD_RETURN_FALSE;
            }

         case SM_SWIT: if (record->event.pressed) {
              layer_on(_APPSWITCH);
              register_mods(MOD_MASK_GUI);
              tap_code16(KC_TAB);
            } else {
              layer_off(_APPSWITCH);
              unregister_mods(MOD_MASK_GUI);
              }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case SM_ESC:
            if (record->event.pressed) {
                smart_escape();
                // if (kbFeature) {
                //     if (host_keyboard_led_state().caps_lock) {
                //         tap_code16(KC_CAPS);
                //     }
                //     disable_caps_word();
                //     disable_xcase();
                //     clear_locked_and_oneshot_mods();
                //     stop_leading();
                //     return PROCESS_RECORD_RETURN_FALSE;
                // } else {
                //     tap_code16(KC_ESC);
                //     dprintln("SM_ESC default");
                //     return PROCESS_RECORD_RETURN_FALSE;
                // }
            }
            return PROCESS_RECORD_RETURN_FALSE;
        break;

        case TG_OS:
            if (record->event.pressed) {
                switch (user_config.system.os) {

                    case MACOS:
                        user_config.system.os = WINDOWS;
                        SEND_STRING("win");
                        eeconfig_update_user_datablock(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                        break;

                    case WINDOWS:
                        user_config.system.os = LINUX;
                        SEND_STRING("lin");
                        eeconfig_update_user_datablock(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                        break;

                    case LINUX:
                        user_config.system.os = MACOS;
                        SEND_STRING("mac");
                        eeconfig_update_user_datablock(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                        break;

                }
            return PROCESS_RECORD_RETURN_FALSE;
            }

        case ADJ_LYR:
            if (record->event.pressed) {
                #ifdef QMENU_ENABLE
                    painter_menu.state.menu_selector = 1;
                    painter_menu.state.submenu_selector = 1;
                    // qp_clear(lcd_surface);
                #endif
                layer_on(_ADJUST);
                return PROCESS_RECORD_RETURN_FALSE;
            }
        return PROCESS_RECORD_RETURN_TRUE;


    case NUM_PP:
    case VIM_PP:
        if (record->event.pressed) {
            if (record->tap.count > 0) {
                start_pass_leading();
                return PROCESS_RECORD_RETURN_FALSE;
            }
        return PROCESS_RECORD_CONTINUE;
        }
    break;

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

    case MEH_PP:
    case LSFT_PP:
    case RSFT_PP:
        if (record->event.pressed) {
        if (record->tap.count > 0) {
            start_pass_leading();
            return PROCESS_RECORD_RETURN_FALSE;
        }
        return PROCESS_RECORD_CONTINUE;
        }
    break;

        case ADJ_EXT:
            if (record->event.pressed) {
                #ifdef QMENU_ENABLE
                    if (user_runtime_state.kb.write_to_eeprom) {
                        painter_sethsv(painter_get_hue(true), painter_get_sat(true), painter_get_val(true), true);
                        painter_sethsv(painter_get_hue(false), painter_get_sat(false), painter_get_val(false), false);
                        user_runtime_state.kb.write_to_eeprom = false;
                    }
                #endif
                layer_off(_ADJUST);
                return PROCESS_RECORD_RETURN_FALSE;
            }
        return PROCESS_RECORD_RETURN_TRUE;

        case MT_STTI:
            if (record->event.pressed) {
                // increase_shift_tapping_term();
                increase_custom_tapping_term(user_config.tapping_term.shift);
                dprintf("Shift Tapping Term = %d\n", user_config.tapping_term.shift);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_DTTI:
            if (record->event.pressed) {
                // g_tapping_term = g_tapping_term + 5;
                increase_custom_tapping_term(g_tapping_term);
                dprintf("General Tapping Term = %d\n", g_tapping_term);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_MTTI:
            if (record->event.pressed) {
                // increase_modtap_tapping_term();
                increase_custom_tapping_term(user_config.tapping_term.modtap);
                eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                dprintf("Mod-Tap Tapping Term = %d\n", user_config.tapping_term.modtap);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_GTTI:
            if (record->event.pressed) {
                // increase_gqt_tapping_term();
                increase_custom_tapping_term(user_config.tapping_term.gqt);
                eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                dprintf("GQT Tapping Term = %d\n", user_config.tapping_term.gqt);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_SGTI:
            if (record->event.pressed) {
                // increase_shift_gqt_tapping_term();
                increase_custom_tapping_term(user_config.tapping_term.shift_gqt);
                eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                dprintf("SGQT Tapping Term = %d\n", user_config.tapping_term.shift_gqt);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_STTD:
            if (record->event.pressed) {
                // decrease_shift_tapping_term();
                decrease_custom_tapping_term(user_config.tapping_term.shift);
                dprintf("Shift Tapping Term = %d\n", user_config.tapping_term.shift);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_DTTD:
            if (record->event.pressed) {
                decrease_custom_tapping_term(g_tapping_term);
                // g_tapping_term = g_tapping_term - 5;
                dprintf("General Tapping Term = %d\n", g_tapping_term);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_MTTD:
            if (record->event.pressed) {
                // decrease_modtap_tapping_term();
                decrease_custom_tapping_term(user_config.tapping_term.modtap);
                eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                dprintf("Mod-Tap Tapping Term = %d\n", user_config.tapping_term.modtap);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_GTTD:
            if (record->event.pressed) {
                // decrease_gqt_tapping_term();
                decrease_custom_tapping_term(user_config.tapping_term.gqt);
                eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                dprintf("GQT Tapping Term = %d\n", user_config.tapping_term.gqt);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case MT_SGTD:
            if (record->event.pressed) {
                // decrease_shift_gqt_tapping_term();
                decrease_custom_tapping_term(user_config.tapping_term.shift_gqt);
                eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
                dprintf("SGQT Tapping Term = %d\n", user_config.tapping_term.shift_gqt);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case TT_CHEK:
            if (record->event.pressed) {
                dprintf("[Z:?]Shift Mod Tapping Term:     %d\n", user_config.tapping_term.shift);
                dprintf("[X:>]General Tapping Term:       %d\n", g_tapping_term);
                dprintf("[C:<]Modtap Tapping Term:        %d\n", user_config.tapping_term.modtap);
                dprintf("[V:M]Flowtap Tapping Term:       %d\n", user_config.tapping_term.gqt);
                dprintf("[B:N]Flowtap Shift Tapping Term: %d\n", user_config.tapping_term.shift_gqt);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case TIPS:
            if(record->event.pressed) {
                clear_mods();
                clear_weak_mods();
                SEND_STRING("trueipsolutions.com");
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case M_EXIT:
            if(record->event.pressed) {
                clear_mods();
                clear_weak_mods();
                SEND_STRING("exit");
                tap_code16(KC_ENTER);
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case M_ARROW:
            if (record->event.pressed) {
                tap_code16(KC_EQL);
                tap_code16(S(KC_DOT));
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        case RGB_SLD:
            if (record->event.pressed) {
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_RETURN_FALSE;
        break;

        case RGB_REC:
            if (record->event.pressed) {
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_RETURN_FALSE;
        break;

        case UNDO:
            if (record->event.pressed) {
                if (isMacOS) {
                    tap_code16(G(KC_Z));
                } else {
                    tap_code16(C(KC_Z));
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case REDO:
            if (record->event.pressed) {
                if (isMacOS) {
                    tap_code16(G(S(KC_Z)));
                } else {
                    tap_code16(C(S(KC_Z)));
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_RETURN_FALSE;

    }
    return PROCESS_RECORD_CONTINUE;
}

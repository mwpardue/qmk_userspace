#include QMK_KEYBOARD_H

#include "caracarn.h"
#include "rgb_matrix.h"
#ifdef QMENU_ENABLE
#include "qkeys.h"
#include "features/qmenu.h"
#include "features/qpainter.h"
#include "features/qhelper.h"
#endif
#include "features/taphold.h"

#ifdef ACHORDION_ENABLE
extern uint16_t achordion_tapping_term;
#endif

extern user_runtime_state_t user_runtime_state;
extern painter_menu_t painter_menu;

process_record_result_t process_qmenu_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_CHG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                    dprintf("rgb_matrix_get_flags (KMI)= %d\n", rgb_matrix_get_flags());
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                    dprintf("rgb_matrix_get_flags (UG)= %d\n", rgb_matrix_get_flags());
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                    dprintf("rgb_matrix_get_flags (OFF)= %d\n", rgb_matrix_get_flags());
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                    dprintf("rgb_matrix_get_flags (ALL)= %d\n", rgb_matrix_get_flags());
                  }
                  break;
              }
              return PROCESS_RECORD_RETURN_FALSE;
            }

        case MENU_MD:
            if (record->event.pressed) {
                switch (painter_menu.state.submenu_selector) {
                    case SUBMENU_LIGHTING:
                        if (painter_menu.state.menu_selector == LIGHTING_END - 1) {
                            painter_menu.state.menu_selector = LIGHTING_HEADING + 1;
                        } else {
                            painter_menu.state.menu_selector = painter_menu.state.menu_selector + 1;
                        };
                        start_index = 0;
                        lcd_dirty = true;
                        dprintln("qkeys lcd_dirty1");
                        break;
                    case SUBMENU_MODTAP:
                        if (painter_menu.state.menu_selector == MODTAP_END - 1) {
                            painter_menu.state.menu_selector = MODTAP_HEADING + 1;
                        } else {
                            painter_menu.state.menu_selector = painter_menu.state.menu_selector + 1;
                        };
                        lcd_dirty = true;
                        dprintln("qkeys lcd_dirty2");
                        break;
                    case SUBMENU_PAINTER:
                        if (painter_menu.state.menu_selector == PAINTER_END - 1) {
                            painter_menu.state.menu_selector = PAINTER_HEADING + 1;
                        } else {
                            painter_menu.state.menu_selector = painter_menu.state.menu_selector + 1;
                        }
                        lcd_dirty = true;
                        dprintln("qkeys lcd_dirty3");
                        break;
                    case SUBMENU_KB:
                        if (painter_menu.state.menu_selector == KB_END - 1) {
                            painter_menu.state.menu_selector = KB_HEADING + 1;
                        } else {
                            painter_menu.state.menu_selector = painter_menu.state.menu_selector + 1;
                        };
                        lcd_dirty = true;
                        dprintln("qkeys lcd_dirty4");
                        break;
                }
                dprintf("Menu Selector is %d\n", painter_menu.state.menu_selector);
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case MENU_MU:
            if (record->event.pressed) {
                switch (painter_menu.state.submenu_selector) {
                    case SUBMENU_LIGHTING:
                        if (painter_menu.state.menu_selector == LIGHTING_HEADING + 1) {
                            painter_menu.state.menu_selector = LIGHTING_END - 1;
                        } else {
                            painter_menu.state.menu_selector = painter_menu.state.menu_selector - 1;
                        }
                        start_index = 0;
                        lcd_dirty = true;
                        dprintln("qkeys lcd_dirty5");
                        break;
                    case SUBMENU_MODTAP:
                        if (painter_menu.state.menu_selector == MODTAP_HEADING + 1) {
                            painter_menu.state.menu_selector = MODTAP_END - 1;
                        } else {
                            painter_menu.state.menu_selector = painter_menu.state.menu_selector - 1;
                        }
                        lcd_dirty = true;
                        dprintln("qkeys lcd_dirty6");
                        break;
                    case SUBMENU_PAINTER:
                        if (painter_menu.state.menu_selector == PAINTER_HEADING + 1) {
                            painter_menu.state.menu_selector = PAINTER_END - 1;
                        } else {
                            painter_menu.state.menu_selector = painter_menu.state.menu_selector - 1;
                        }
                        lcd_dirty = true;
                        dprintln("qkeys lcd_dirty7");
                        break;
                    case SUBMENU_KB:
                        if (painter_menu.state.menu_selector == KB_HEADING + 1) {
                            painter_menu.state.menu_selector = KB_END - 1;
                        } else {
                            painter_menu.state.menu_selector = painter_menu.state.menu_selector - 1;
                        }
                        lcd_dirty = true;
                        dprintln("qkeys lcd_dirty8");
                        break;
                    }
                dprintf("Menu Selector is %d\n", painter_menu.state.menu_selector);
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case MENU_AU:
            if (record->event.pressed) {
                dprintln("MENU_AU pressed");
                switch (painter_menu.state.submenu_selector) {
                    case SUBMENU_LIGHTING:
                        switch (painter_menu.state.menu_selector) {
                            case LIGHTING_HEADING:
                                qp_clear(lcd_surface);
                                painter_menu.state.submenu_selector = SUBMENU_MODTAP;
                                break;
                            case MENU_HUE:
                                rgb_matrix_increase_hue();
                                break;
                            case MENU_SAT:
                                rgb_matrix_increase_sat();
                                break;
                            case MENU_VAL:
                                rgb_matrix_increase_val();
                                break;
                            case MENU_SPEED:
                                rgb_matrix_increase_speed();
                                break;
                            case MENU_RGBMODE:
                                rgb_matrix_step();
                                start_index = 0;
                                break;
                            case MENU_FLAGS:
                                switch (rgb_matrix_get_flags()) {
                                    case LED_FLAG_ALL: {
                                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                                        dprintf("rgb_matrix_get_flags (KMI)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                                        dprintf("rgb_matrix_get_flags (UG)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    case LED_FLAG_UNDERGLOW: {
                                        rgb_matrix_set_flags(LED_FLAG_NONE);
                                        rgb_matrix_disable_noeeprom();
                                        dprintf("rgb_matrix_get_flags (OFF)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    default: {
                                        rgb_matrix_set_flags(LED_FLAG_ALL);
                                        rgb_matrix_enable_noeeprom();
                                        dprintf("rgb_matrix_get_flags (ALL)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                            }
                            break;
                        }
                        break;
                    case SUBMENU_MODTAP:
                        switch (painter_menu.state.menu_selector) {
                            case MODTAP_HEADING:
                                qp_clear(lcd_surface);
                                painter_menu.state.submenu_selector = SUBMENU_PAINTER;
                                break;
                            case MENU_STT:
                                increase_shift_tapping_term();
                                user_runtime_state.kb.write_to_eeprom = true;
                                dprintf("Shift Tapping Term = %d\n", user_config.tapping_term.shift);
                                break;
                            case MENU_TT:
                                g_tapping_term = g_tapping_term + 5;
                                dprintf("General Tapping Term = %d\n", g_tapping_term);
                                break;
                            case MENU_MT:
                                increase_modtap_tapping_term();
                                user_runtime_state.kb.write_to_eeprom = true;
                                dprintf("Mod-Tap Tapping Term = %d\n", user_config.tapping_term.modtap);
                                break;
                            #ifdef ACHORDION_ENABLE
                            case MENU_AT:
                                achordion_tapping_term = achordion_tapping_term + 50;
                                dprintf("Achordion Tapping Term = %d\n", achordion_tapping_term);
                                break;
                            #endif
                            #if defined(GQT_ENABLE) || defined(TAP_FLOW_ENABLE)
                            case MENU_GQT:
                                increase_gqt_tapping_term();
                                user_runtime_state.kb.write_to_eeprom = true;
                                dprintf("GQT Tapping Term = %d\n", user_config.tapping_term.gqt);
                                break;
                            case MENU_SGQT:
                                increase_shift_gqt_tapping_term();
                                user_runtime_state.kb.write_to_eeprom = true;
                                dprintf("SGQT Tapping Term = %d\n", user_config.tapping_term.shift_gqt);
                                break;
                            #endif
                        } //MODTAP menu switch
                    break;
                    case SUBMENU_PAINTER:
                        switch (painter_menu.state.menu_selector) {
                            case PAINTER_HEADING:
                                qp_clear(lcd_surface);
                                painter_menu.state.submenu_selector = SUBMENU_KB;
                                break;
                            case MENU_PHUE:
                                painter_increase_hue_noeeprom(true);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_PSAT:
                                painter_increase_sat_noeeprom(true);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_PVAL:
                                painter_increase_val_noeeprom(true);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_SHUE:
                                painter_increase_hue_noeeprom(false);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_SSAT:
                                painter_increase_sat_noeeprom(false);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_SVAL:
                                painter_increase_val_noeeprom(false);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                        } //PAINTER menu switch
                    break;
                    case SUBMENU_KB:
                        switch (painter_menu.state.menu_selector) {
                            case KB_HEADING:
                                qp_clear(lcd_surface);
                                painter_menu.state.submenu_selector = SUBMENU_LIGHTING;
                                break;
                            case MENU_EECLEAR:
                                #ifdef NO_RESET
                                    eeconfig_init();
                                #else
                                    eeconfig_disable();
                                    soft_reset_keyboard();
                                #endif
                                break;
                            case MENU_DEBUG:
                                #ifndef NO_DEBUG
                                    debug_enable ^= 1;
                                    user_runtime_state.kb.debug_enabled = debug_enable;
                                    if (debug_enable) {
                                        print("DEBUG: enabled.\n");
                                    } else {
                                        print("DEBUG: disabled.\n");
                                    }
                                #endif
                                break;
                            case MENU_OSFLAG:
                                switch (user_config.system.os) {
                                    case MACOS:
                                        user_config.system.os = WINDOWS;
                                        eeconfig_update_user_datablock(&user_config);
                                        break;
                                    case WINDOWS:
                                        user_config.system.os = LINUX;
                                        eeconfig_update_user_datablock(&user_config);
                                        break;
                                    case LINUX:
                                        user_config.system.os = MACOS;
                                        eeconfig_update_user_datablock(&user_config);
                                        break;
                                }
                                break;
                            case MENU_NKRO:
                                if (keymap_config.nkro) {
                                    clear_keyboard(); // clear first buffer to prevent stuck keys
                                    keymap_config.nkro = false;
                                } else {
                                    clear_keyboard(); // clear first buffer to prevent stuck keys
                                    keymap_config.nkro = true;
                                }
                                break;
                            case MENU_BOOTLOADER:
                                reset_keyboard();
                                break;
                            case MENU_DEFAULTLAYER:
                                switch (get_highest_layer(default_layer_state)) {
                                    case _BASE:
                                        set_single_persistent_default_layer(_GAMING);
                                        break;
                                    case _COLEMAK_DH:
                                        set_single_persistent_default_layer(_BASE);
                                        break;
                                    case _GAMING:
                                        set_single_persistent_default_layer(_COLEMAK_DH);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                        }
                    break;
                }
                lcd_dirty = true;
                        dprintln("qkeys lcd_dirty8");
                return PROCESS_RECORD_RETURN_FALSE;
            }
        break;

        case MENU_AD:
                dprintln("MENU_AD pressed");
            if (record->event.pressed) {
                switch (painter_menu.state.submenu_selector) {
                    case SUBMENU_LIGHTING:
                        switch (painter_menu.state.menu_selector) {
                            case LIGHTING_HEADING:
                                qp_clear(lcd_surface);
                                painter_menu.state.submenu_selector = SUBMENU_KB;
                                break;
                            case MENU_HUE:
                                rgb_matrix_decrease_hue();
                                break;
                            case MENU_SAT:
                                rgb_matrix_decrease_sat();
                                break;
                            case MENU_VAL:
                                rgb_matrix_decrease_val();
                                break;
                            case MENU_SPEED:
                                rgb_matrix_decrease_speed();
                                break;
                            case MENU_RGBMODE:
                                rgb_matrix_step_reverse();
                                start_index = 0;
                                break;
                            case MENU_FLAGS:
                                switch (rgb_matrix_get_flags()) {
                                    case LED_FLAG_ALL: {
                                        rgb_matrix_set_flags(LED_FLAG_NONE);
                                        rgb_matrix_disable_noeeprom();
                                        dprintf("rgb_matrix_get_flags (OFF)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                                        rgb_matrix_set_flags(LED_FLAG_ALL);
                                        dprintf("rgb_matrix_get_flags (ALL)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    case LED_FLAG_UNDERGLOW: {
                                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                                        dprintf("rgb_matrix_get_flags (KMI)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    default: {
                                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                                        rgb_matrix_enable_noeeprom();
                                        dprintf("rgb_matrix_get_flags (UG)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                }
                                break;
                        }
                    break;
                    case SUBMENU_MODTAP:
                        switch (painter_menu.state.menu_selector) {
                            case MODTAP_HEADING:
                                qp_clear(lcd_surface);
                                painter_menu.state.submenu_selector = SUBMENU_LIGHTING;
                                break;
                            case MENU_STT:
                                decrease_shift_tapping_term();
                                user_runtime_state.kb.write_to_eeprom = true;
                                dprintf("Shift Tapping Term = %d\n", user_config.tapping_term.shift);
                                break;
                            case MENU_TT:
                                g_tapping_term = g_tapping_term - 5;
                                dprintf("General Tapping Term = %d\n", g_tapping_term);
                                break;
                            case MENU_MT:
                                decrease_modtap_tapping_term();
                                user_runtime_state.kb.write_to_eeprom = true;
                                dprintf("Mod-Tap Tapping Term = %d\n", user_config.tapping_term.modtap);
                                break;
                            #ifdef ACHORDION_ENABLE
                            case MENU_AT:
                                achordion_tapping_term = achordion_tapping_term - 50;
                                dprintf("Achordion Tapping Term = %d\n", achordion_tapping_term);
                                break;
                            #endif
                            #if defined(GQT_ENABLE) || defined(TAP_FLOW_ENABLE)
                            case MENU_GQT:
                                decrease_gqt_tapping_term();
                                user_runtime_state.kb.write_to_eeprom = true;
                                dprintf("GQT Tapping Term = %d\n", user_config.tapping_term.gqt);
                                break;
                            case MENU_SGQT:
                                decrease_shift_gqt_tapping_term();
                                user_runtime_state.kb.write_to_eeprom = true;
                                dprintf("SGQT Tapping Term = %d\n", user_config.tapping_term.shift_gqt);
                                break;
                            #endif
                        }
                    break;
                    case SUBMENU_PAINTER:
                        switch (painter_menu.state.menu_selector) {
                            case PAINTER_HEADING:
                                qp_clear(lcd_surface);
                                painter_menu.state.submenu_selector = SUBMENU_MODTAP;
                                break;
                            case MENU_PHUE:
                                painter_decrease_hue_noeeprom(true);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_PSAT:
                                painter_decrease_sat_noeeprom(true);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_PVAL:
                                painter_decrease_val_noeeprom(true);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_SHUE:
                                painter_decrease_hue_noeeprom(false);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_SSAT:
                                painter_decrease_sat_noeeprom(false);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                            case MENU_SVAL:
                                painter_decrease_val_noeeprom(false);
                                user_runtime_state.kb.write_to_eeprom = true;
                                break;
                        } //MODTAP menu switch
                    break;
                    case SUBMENU_KB:
                        switch (painter_menu.state.menu_selector) {
                            case KB_HEADING:
                                qp_clear(lcd_surface);
                                painter_menu.state.submenu_selector = SUBMENU_PAINTER;
                                break;
                            case MENU_EECLEAR:
                                #ifdef NO_RESET
                                    eeconfig_init();
                                #else
                                    eeconfig_disable();
                                    soft_reset_keyboard();
                                #endif
                                break;
                            case MENU_DEBUG:
                                #ifndef NO_DEBUG
                                    debug_enable ^= 1;
                                    user_runtime_state.kb.debug_enabled = debug_enable;
                                    if (debug_enable) {
                                        print("DEBUG: enabled.\n");
                                    } else {
                                        print("DEBUG: disabled.\n");
                                    }
                                #endif
                                break;
                            case MENU_OSFLAG:
                                switch (user_config.system.os) {
                                    case MACOS:
                                        user_config.system.os = LINUX;
                                        eeconfig_update_user_datablock(&user_config);
                                        break;
                                    case WINDOWS:
                                        user_config.system.os = MACOS;
                                        eeconfig_update_user_datablock(&user_config);
                                        break;
                                    case LINUX:
                                        user_config.system.os = WINDOWS;
                                        eeconfig_update_user_datablock(&user_config);
                                        break;
                                }
                                break;
                            case MENU_NKRO:
                                if (keymap_config.nkro) {
                                    clear_keyboard(); // clear first buffer to prevent stuck keys
                                    keymap_config.nkro = false;
                                } else {
                                    clear_keyboard(); // clear first buffer to prevent stuck keys
                                    keymap_config.nkro = true;
                                }
                                break;
                            case MENU_BOOTLOADER:
                                reset_keyboard();
                                break;
                            case MENU_DEFAULTLAYER:
                                switch (get_highest_layer(default_layer_state)) {
                                    case _BASE:
                                        set_single_persistent_default_layer(_COLEMAK_DH);
                                        break;
                                    case _COLEMAK_DH:
                                        set_single_persistent_default_layer(_GAMING);
                                        break;
                                    case _GAMING:
                                        set_single_persistent_default_layer(_BASE);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                        }
                    break;
                }
                lcd_dirty = true;
                        dprintln("qkeys lcd_dirty9");
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
            case TB_MENU:
                if (record->event.pressed) {
                    switch (painter_menu.state.submenu_selector) {
                        case SUBMENU_LIGHTING:
                            painter_menu.state.submenu_selector = SUBMENU_MODTAP;
                            break;
                        case SUBMENU_MODTAP:
                            painter_menu.state.submenu_selector = SUBMENU_PAINTER;
                            break;
                        case SUBMENU_PAINTER:
                            painter_menu.state.submenu_selector = SUBMENU_KB;
                            break;
                        case SUBMENU_KB:
                            painter_menu.state.submenu_selector = SUBMENU_LIGHTING;
                            break;
                    }
                }
            painter_menu.state.menu_selector = 1;
            qp_clear(lcd_surface);
            lcd_dirty = true;
                        dprintln("qkeys lcd_dirty10");
            return PROCESS_RECORD_RETURN_FALSE;
            break;
    }
    return PROCESS_RECORD_CONTINUE; // Process all other keycodes normally
}

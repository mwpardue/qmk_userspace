#include QMK_KEYBOARD_H

#include <ctype.h>
#include "caracarn.h"

extern uint16_t sft_tapping_term;

extern uint16_t modtap_tapping_term;

extern uint16_t achordion_tapping_term;

extern uint16_t gqt_tapping_term;

extern uint16_t sgqt_tapping_term;

__attribute__((unused)) int            start_index = 0;

__attribute__((unused)) uint32_t        substring_timer = 0;

__attribute__((unused)) uint32_t scroll_time = 1000;
//----------------------------------------------------------
// RGB Matrix naming
#include <rgb_matrix.h>

#if defined(RGB_MATRIX_EFFECT)
#    undef RGB_MATRIX_EFFECT
#endif // defined(RGB_MATRIX_EFFECT)

#define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
};

#define RGB_MATRIX_EFFECT(x)    \
    case RGB_MATRIX_EFFECT_##x: \
        return #x;
const char* rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
        default:
            return "UNKNOWN";
    }
}

// GENERAL MENU FUNCTIONS

bool check_menu(uint8_t menu_item) {
    if (user_config.menu_selector == menu_item) {
        return true;
    } else {
        return false;
    }
}

uint8_t viewport_begin(void) {
    if (user_config.menu_selector <= 3) {
        return 1;
    } else if (user_config.menu_selector >= (MENU_MAX - 3)) {
        return (MENU_MAX - VIEWPORT_HEIGHT);
    } else {
        return (user_config.menu_selector - 3);
    }
}

void render_menu_item(const char *label, uint16_t property, uint8_t menu_item) {
    size_t label_length = strlen(label);

    char property_str[20];
    snprintf(property_str, sizeof(property_str), "%d", property);
    uint8_t property_length = strlen(property_str);

    uint8_t spacer_length = (VIEWPORT_WIDTH - label_length - property_length);
    oled_write_P(PSTR(label), check_menu(menu_item));
    for (uint8_t i = 1; i <= spacer_length; i++) {
        oled_write_P(PSTR(" "), check_menu(menu_item));
    }
    oled_write_P(PSTR(property_str), check_menu(menu_item));
}

void render_bool_menu_item(const char *label, bool property, uint8_t menu_item) {
    char property_str[4];
    uint8_t property_length = strlen(property_str);
    size_t label_length = strlen(label);

    if (property) {
        strcpy(property_str, "ON");
    } else {
        strcpy(property_str, "OFF");
    }
    property_length = strlen(property_str);

    uint8_t spacer_length = (VIEWPORT_WIDTH - label_length - property_length);
    oled_write_P(PSTR(label), check_menu(menu_item));
    for (uint8_t i = 1; i <= spacer_length; i++) {
        oled_write_P(PSTR(" "), check_menu(menu_item));
    }
    oled_write_P(PSTR(property_str), check_menu(menu_item));
}

void render_rgb_mode(const char *label, uint8_t menu_item) {
    // oled_set_cursor(col, line);
    __attribute__((unused)) static uint8_t mode;
    // bool                                   need_update = false;
    static char                            buf[41]     = {0};
    int                                    STRING_LENGTH = strlen(rgb_matrix_name(rgb_matrix_get_mode()));
    static char                            substring[22];
    size_t                                 LABEL_LENGTH = strlen(label);
    size_t                                 PROPERTY_LENGTH = (VIEWPORT_WIDTH - LABEL_LENGTH);

    oled_write_P(PSTR(label), check_menu(menu_item));
    if (mode != rgb_matrix_get_mode()) {
        mode        = rgb_matrix_get_mode();
        start_index = 0;
        snprintf(buf, sizeof(buf), "%*s", PROPERTY_LENGTH, rgb_matrix_name(rgb_matrix_get_mode()));
        STRING_LENGTH = strlen(strcat(buf, ""));
        for (uint8_t i = 1; i < sizeof(buf); ++i) {
            if (buf[i] == 0)
                break;
            else if (buf[i] == '_')
                buf[i] = ' ';
        }
    }

    if ( STRING_LENGTH > PROPERTY_LENGTH ) {
        strncpy(substring, buf + start_index, PROPERTY_LENGTH);
        oled_write(substring, check_menu(menu_item));
        if (!check_menu(menu_item)) {
            start_index = 0;
            scroll_time = 1000;
        } else {
            if ((timer_elapsed32(substring_timer) > scroll_time) && (start_index <= STRING_LENGTH - (PROPERTY_LENGTH + 1))) {
                start_index++;
                substring_timer = timer_read32();
                scroll_time = 500;
            }
        }
    } else {
        oled_write(buf, check_menu(menu_item));
    }
}

void menu_items(void) {
    oled_write_P(PSTR(" Kyria Configuration "), false);
    for (uint8_t i = viewport_begin(); i <= (viewport_begin() + 6); i++) {
        switch(i) {
            case MENU_FLAGS:
                oled_write_P(PSTR("LED FLAGS:"), check_menu(MENU_FLAGS));
                    switch (rgb_matrix_get_flags()) {
                        case LED_FLAG_ALL: {
                            oled_write_P(PSTR("        ALL"), check_menu(MENU_FLAGS));
                        }
                        break;
                        case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                            oled_write_P(PSTR("        KMI"), check_menu(MENU_FLAGS));
                        }
                        break;
                        case LED_FLAG_UNDERGLOW: {
                            oled_write_P(PSTR("  UNDERGLOW"), check_menu(MENU_FLAGS));
                        }
                        break;
                        default: {
                            oled_write_P(PSTR("       NONE"), check_menu(MENU_FLAGS));
                        }
                        break;
                    }
                    break;
            case MENU_SPEED:
                render_menu_item("RGB SPEED:", rgb_matrix_get_speed(), i);
                break;
            case MENU_HUE:
                render_menu_item("RGB HUE:", rgb_matrix_get_hue(), i);
                break;
            case MENU_SAT:
                render_menu_item("RGB SAT:", rgb_matrix_get_sat(), i);
                break;
            case MENU_VAL:
                render_menu_item("RGB VAL:", rgb_matrix_get_val(), i);
                break;
            case MENU_RGBMODE:
                render_rgb_mode("MODE: ", i);
                break;
            // case MENU_HMAREA:
            //     render_menu_item("HEATMAP AREA:", user_config.rgb_matrix_heatmap_area, i);
            //     break;
            // case MENU_HMSPREAD:
            //     render_menu_item("HEATMAP SPREAD:", user_config.rgb_matrix_heatmap_spread, i);
            //     break;
            case MENU_STT:
                render_menu_item("SHIFT TAP TERM:", sft_tapping_term, i);
                break;
            case MENU_TT:
                render_menu_item("TAPPING TERM:", g_tapping_term, i);
                break;
            case MENU_MT:
                render_menu_item("MOD TAP TERM:", modtap_tapping_term, i);
                break;
            case MENU_AT:
                render_menu_item("ACH TAP TERM:", achordion_tapping_term, i);
                break;
            case MENU_GQT:
                render_menu_item("GQT TAP TERM:", gqt_tapping_term, i);
                break;
            case MENU_SGQT:
                render_menu_item("SGQT TAP TERM:", sgqt_tapping_term, i);
                break;
            case MENU_DEFAULTLAYER:
                switch (get_highest_layer(default_layer_state)) {
                    case _BASE:
                        oled_write_P(PSTR("DF LAYER:     COLEMAK"), check_menu(MENU_DEFAULTLAYER));
                        break;
                    case _COLEMAK_DH:
                        oled_write_P(PSTR("DF LAYER:    ALT BASE"), check_menu(MENU_DEFAULTLAYER));
                        break;
                    case _GAMING:
                        oled_write_P(PSTR("DF LAYER:      GAMING"), check_menu(MENU_DEFAULTLAYER));
                        break;
                    default:
                        oled_write_P(PSTR("DF LAYER:       OTHER"), check_menu(MENU_DEFAULTLAYER));
                        break;
                }
                break;
            case MENU_OSFLAG:
                oled_write_P(PSTR("CURRENT OS:"), check_menu(MENU_OSFLAG));
                switch (user_config.os) {
                    case WINDOWS:
                        oled_write_P(PSTR("   WINDOWS"), check_menu(MENU_OSFLAG));
                        break;
                    case LINUX:
                        oled_write_P(PSTR("     LINUX"), check_menu(MENU_OSFLAG));
                        break;
                    default:
                        oled_write_P(PSTR("     MACOS"), check_menu(MENU_OSFLAG));
                        break;
                }
                break;
            case MENU_DEBUG:
                if (kb_state.debug_enabled) {
                oled_write_P(PSTR("DEBUG STATUS:      ON"), check_menu(MENU_DEBUG));
                } else {
                oled_write_P(PSTR("DEBUG STATUS:     OFF"), check_menu(MENU_DEBUG));
                }
                break;
            case MENU_EECLEAR:
                oled_write_P(PSTR("CLEAR EEPROM: EXECUTE"), check_menu(MENU_EECLEAR));
                break;
            case MENU_NKRO:
                render_bool_menu_item("NKRO:", keymap_config.nkro, i);
                break;
            case MENU_BOOTLOADER:
                oled_write_P(PSTR("FLASH FW:     EXECUTE"), check_menu(MENU_BOOTLOADER));
                break;
            default:
            break;
        }
    }
}

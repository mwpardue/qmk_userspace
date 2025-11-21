#include QMK_KEYBOARD_H

#include <ctype.h>
#include "caracarn.h"
#include "features/qpainter.h"
#include "features/qmenu.h"

#ifdef ACHORDION_ENABLE
extern uint16_t achordion_tapping_term;
#endif

__attribute__((unused)) int            start_index = 0;

__attribute__((unused)) int            oversize_length = 0;

__attribute__((unused)) uint32_t        substring_timer = 0;

__attribute__((unused)) uint32_t scroll_time = 250;

__attribute__((unused)) bool dyn_display = false;
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
    if (painter_menu.state.menu_selector == menu_item) {
        return true;
    } else {
        return false;
    }
}

#define MAX_LABEL_SIZE 16
#define MAX_PROP_SIZE 16
#define MAX_MENU_SIZE 14
#define HEADER_ROW_Y 9
#define ROW_HEIGHT mononoki->line_height
#define ROW_OFFSET (menu_item*2)
#define MENU_START_Y bbt->line_height+ROW_OFFSET
#define ROW_CALC (menu_item*(mononoki->line_height))+(menu_item*2) + HEADER_ROW_Y - 4
#define BOX_LEFT 2
#define BOX_TOP ROW_CALC - 1
#define BOX_RIGHT LCD_WIDTH - 2
#define BOX_BOTTOM BOX_TOP + mononoki->line_height + 2

static char label[MAX_LABEL_SIZE];  // Static array to hold the string
static char prop[MAX_PROP_SIZE];  // Static array to hold the string

void set_prop(const char *new_value) {
    // Ensure the buffer is clean before copying new content
    memset(prop, 0, MAX_PROP_SIZE);

    // Safely copy the new string into the buffer
    strncpy(prop, new_value, MAX_PROP_SIZE - 1);

    // Explicitly set the last character to '\0' to ensure null termination
    prop[MAX_PROP_SIZE - 1] = '\0';
}

void set_label(const char *new_value) {
    // Ensure the buffer is clean before copying new content
    memset(label, 0, MAX_LABEL_SIZE);

    // Safely copy the new string into the buffer
    strncpy(label, new_value, MAX_LABEL_SIZE - 1);

    // Explicitly set the last character to '\0' to ensure null termination
    prop[MAX_LABEL_SIZE - 1] = '\0';
}

void render_menu_item(const char *label, char *property, uint8_t menu_item) {
    uint8_t property_length = strlen(property);

    uint8_t label_length = strlen(label);
    char menu_row[MAX_MENU_SIZE+1];
    uint8_t property_start = MAX_MENU_SIZE - property_length;
    memset(menu_row, ' ', MAX_MENU_SIZE);
    memcpy(menu_row, label, label_length);
    memcpy(menu_row + property_start, property, property_length);
    menu_row[MAX_MENU_SIZE] = '\0';

    qp_rect(lcd_surface, BOX_LEFT, BOX_TOP, BOX_RIGHT, BOX_BOTTOM, CLR_IDL_FG, false);
    if (check_menu(menu_item)) {
        qp_drawtext_recolor(lcd_surface, 5, ROW_CALC + 1, mononoki, menu_row, CLR_SEL_FG, CLR_SEL_BG);
    } else {
        qp_drawtext_recolor(lcd_surface, 5, ROW_CALC + 1, mononoki, menu_row, CLR_IDL_FG, CLR_IDL_BG);
    }
}

void prerender_menu_item(const char *label, uint16_t property, uint8_t menu_item) {

    uint8_t property_length = snprintf(NULL, 0, "%d", property);
    char property_str[property_length + 1];
    snprintf(property_str, sizeof(property_str), "%d", property);

    render_menu_item(label, property_str, menu_item);
}

void prerender_painter_item(const char *label, uint8_t property, uint8_t menu_item) {

    uint8_t property_length = snprintf(NULL, 0, "%d", property);
    char property_str[property_length + 1];
    snprintf(property_str, sizeof(property_str), "%d", property);

    render_menu_item(label, property_str, menu_item);
}

void qmenu_timer(void) {
    if ((dyn_display == true) && (timer_elapsed32(substring_timer) > scroll_time)) {
        dprintln("qmenu_timer expired");
        lcd_dirty = true;
    }
}

void render_rgb_mode(uint8_t menu_item) {
    __attribute__((unused)) static uint8_t mode;
    static char                            buf[41] = {0};
    int                                    STRING_LENGTH;
    static char                            livestring[MAX_MENU_SIZE + 1];
    size_t                                 PROPERTY_LENGTH = MAX_MENU_SIZE - 4;

    if (mode != rgb_matrix_get_mode()) {

        memset(buf, ' ', 41);
        mode        = rgb_matrix_get_mode();
        STRING_LENGTH = strlen(rgb_matrix_name(rgb_matrix_get_mode()));

        snprintf(buf, sizeof(buf), "%*s", PROPERTY_LENGTH, rgb_matrix_name(rgb_matrix_get_mode()));
        STRING_LENGTH = strlen(strcat(buf, ""));
        for (uint8_t i = 1; i < sizeof(buf); ++i) {
            if (buf[i] == 0)
                break;
            else if (buf[i] == '_')
                buf[i] = ' ';
        }
        if ( STRING_LENGTH > PROPERTY_LENGTH ) {
            strncpy(livestring, buf, PROPERTY_LENGTH);
            oversize_length = STRING_LENGTH - PROPERTY_LENGTH;
        } else {
            strncpy(livestring, buf, PROPERTY_LENGTH);
        }
    }


    render_menu_item("MD: ", livestring, menu_item);
    if (check_menu(menu_item)) {
        dyn_display = true;
        dprintln("RGB menu check");
        dprintf("start_index = %d\n", start_index);
        dprintf("oversize_length = %d\n", oversize_length);
        if ((dyn_display) && (start_index < oversize_length)) {
            start_index++;
            dprintf("start_index = %d\n", start_index);
            strncpy(livestring, buf + start_index, PROPERTY_LENGTH);
            substring_timer = timer_read32();
        }
    } else {
        start_index = 0;
        strncpy(livestring, buf + start_index, PROPERTY_LENGTH);
        dyn_display = false;
    }
}


void render_menu_heading(const char *heading) {
    uint16_t heading_width = qp_textwidth(bbt, heading);
    uint16_t left = ((LCD_WIDTH - heading_width)/2) - 3;
    uint16_t right = LCD_WIDTH - ((LCD_WIDTH - heading_width)/2) + 3;
    uint16_t top = 5;
    uint16_t bottom = top + bbt->line_height + 5;

    qp_rect(lcd_surface, left, top, right, bottom, CLR_MENU_BG, true);
    qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), HEADER_ROW_Y, bbt, heading, CLR_MENU_FG, CLR_MENU_BG);
    qp_rect(lcd_surface, left, top, right, bottom, HSV_BLACK, false);
}

void render_menu_rgb(const char *heading, uint8_t sm_start, uint8_t sm_end) {
    // render_menu_heading(heading);
    for (uint8_t i = (sm_start); i < sm_end; i++) {
        switch(i) {
            // case LIGHTING_HEADING:
                    // qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), HEADER_ROW_Y, bbt, heading, CLR_MENU_FG, CLR_MENU_BG);
                    // render_menu_heading(heading);
                // break;
            case MENU_FLAGS:
                    switch (rgb_matrix_get_flags()) {
                        case LED_FLAG_ALL: {
                        render_menu_item("FLAGS:", "ALL", MENU_FLAGS);
                        }
                        break;
                        case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        render_menu_item("FLAGS:", "KMI", MENU_FLAGS);
                        }
                        break;
                        case LED_FLAG_UNDERGLOW: {
                        render_menu_item("FLAGS:", "UG", MENU_FLAGS);
                        }
                        break;
                        default: {
                        render_menu_item("FLAGS:", "NONE", MENU_FLAGS);
                        }
                        break;
                    }
                    break;
            case MENU_SPEED:
                prerender_menu_item("SPEED:", rgb_matrix_get_speed(), i);
                break;
            case MENU_HUE:
                prerender_menu_item("HUE:", rgb_matrix_get_hue(), i);
                break;
            case MENU_SAT:
                prerender_menu_item("SAT:", rgb_matrix_get_sat(), i);
                break;
            case MENU_VAL:
                prerender_menu_item("VAL:", rgb_matrix_get_val(), i);
                break;
            case MENU_RGBMODE:
                render_rgb_mode(i);
                break;
         }
    }
    render_menu_heading(heading);
}

void render_menu_modtap(const char *heading, uint8_t sm_start, uint8_t sm_end) {
    // render_menu_heading(heading);
    for (uint8_t i = (sm_start); i < sm_end; i++) {
        switch(i) {
            // case MODTAP_HEADING:
            //         // qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), HEADER_ROW_Y, bbt, heading, CLR_MENU_FG, CLR_MENU_BG);
            //     break;
            case MENU_STT:
                prerender_menu_item("SHIFT:", user_config.tapping_term.shift, i);
                break;
            case MENU_TT:
                prerender_menu_item("DEFAULT:", g_tapping_term, i);
                break;
            case MENU_MT:
                prerender_menu_item("MOD TAP:", user_config.tapping_term.modtap, i);
                break;
            #ifdef ACHORDION_ENABLE
            case MENU_AT:
                prerender_menu_item("ACHORDION:", achordion_tapping_term, i);
                break;
            #endif
            #if defined(GQT_ENABLE) || defined(TAP_FLOW_ENABLE)
            case MENU_GQT:
                prerender_menu_item("GQT:", user_config.tapping_term.gqt, i);
                break;
            case MENU_SGQT:
                prerender_menu_item("SGQT:", user_config.tapping_term.shift_gqt, i);
                break;
            #endif
         }
    }
    render_menu_heading(heading);
}

void render_menu_kb(const char *heading, uint8_t sm_start, uint8_t sm_end) {
    for (uint8_t i = (sm_start); i < sm_end; i++) {
        switch(i) {
            // case KB_HEADING:
            // qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), HEADER_ROW_Y, bbt, heading, CLR_MENU_FG, CLR_MENU_BG);
            //     break;
            case MENU_DEFAULTLAYER:
                switch (get_highest_layer(default_layer_state)) {
                    case _BASE:
                        render_menu_item("LAYER:", "BASE", MENU_DEFAULTLAYER);
                        break;
                    case _COLEMAK_DH:
                        render_menu_item("LAYER:", "TYPE", MENU_DEFAULTLAYER);
                        break;
                    case _GAMING:
                        render_menu_item("LAYER:", "GAMING", MENU_DEFAULTLAYER);
                        break;
                    default:
                        render_menu_item("LAYER:", "OTHER", MENU_DEFAULTLAYER);
                        break;
                }
                break;
            case MENU_OSFLAG:
                switch (user_config.system.os) {
                    case WINDOWS:
                        render_menu_item("OS:", "WINDOWS", MENU_OSFLAG);
                        break;
                    case LINUX:
                        render_menu_item("OS:", "LINUX", MENU_OSFLAG);
                        break;
                    default:
                        render_menu_item("OS:", "MAC OS", MENU_OSFLAG);
                        break;
                }
                break;
            case MENU_DEBUG:
                if (user_runtime_state.kb.debug_enabled) {
                    render_menu_item("DEBUG:", "ON", MENU_DEBUG);
                } else {
                    render_menu_item("DEBUG:", "OFF", MENU_DEBUG);
                }
                break;
            case MENU_EECLEAR:
                render_menu_item("CLEAR", "EEPROM", MENU_EECLEAR);
                break;
            case MENU_NKRO:
                set_label("NKRO:");
                if (keymap_config.nkro) {
                    render_menu_item("NKRO:", "ON", MENU_NKRO);
                } else {
                    render_menu_item("NKRO:", "OFF", MENU_NKRO);
                }
                break;
            case MENU_BOOTLOADER:
                render_menu_item("FLASH", "FIRMWARE", MENU_BOOTLOADER);
                break;
            default:
            break;
        }
    }
    render_menu_heading(heading);
}

void render_menu_painter(const char *heading, uint8_t sm_start, uint8_t sm_end) {
    for (uint8_t i = (sm_start); i < sm_end; i++) {
        switch(i) {
            // case PAINTER_HEADING:
                    // qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), HEADER_ROW_Y, bbt, heading, CLR_MENU_FG, CLR_MENU_BG);
                // break;
            case MENU_PHUE:
                prerender_painter_item("PRI HUE:", user_config.painter.hsv.primary.h, i);
                break;
            case MENU_PSAT:
                prerender_painter_item("PRI SAT:", user_config.painter.hsv.primary.s, i);
                break;
            case MENU_PVAL:
                prerender_painter_item("PRI VAL:", user_config.painter.hsv.primary.v, i);
                break;
            case MENU_SHUE:
                prerender_painter_item("SEC HUE:", user_config.painter.hsv.secondary.h, i);
                break;
            case MENU_SSAT:
                prerender_painter_item("SEC SAT:", user_config.painter.hsv.secondary.s, i);
                break;
            case MENU_SVAL:
                prerender_painter_item("SEC VAL:", user_config.painter.hsv.secondary.v, i);
                break;
         }
    }
    render_menu_heading(heading);
}

void render_menu(void) {
    if (lcd_dirty) {
        switch (painter_menu.state.submenu_selector) {
            case SUBMENU_LIGHTING:
                render_menu_rgb("RGB", LIGHTING_HEADING, LIGHTING_END);
                break;
            case SUBMENU_MODTAP:
                render_menu_modtap("MODTAP", MODTAP_HEADING, MODTAP_END);
                break;
            case SUBMENU_PAINTER:
                render_menu_painter("PAINTER", PAINTER_HEADING, PAINTER_END);
                break;
            case SUBMENU_KB:
                render_menu_kb("KB", KB_HEADING, KB_END);
                break;
        }
    }
}

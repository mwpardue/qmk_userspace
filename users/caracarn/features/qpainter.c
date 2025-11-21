#include "splitkb/hlc_tft_display/hlc_tft_display.h"
#include "qp_surface.h"
#include "features/mononoki.qff.h"
#include "features/kyria_logo-mono.qgf.h"
#include "../fonts/bigbluetermmono.qff.h"
#include "../images/glyphs.qgf.h"
#ifdef CASEMODE_ENABLE
#include "features/casemodes.h"
#endif
#include "features/leader.h"
#include "definitions/layers.h"
#include "features/qmenu.h"

extern bool caps_word_on;
extern enum xcase_state xcase_state;
bool lcd_dirty = false;

painter_font_handle_t mononoki, bbt;

painter_device_t lcd;
painter_device_t lcd_surface;
painter_image_handle_t  os_glyph,
                        command_glyph, ctrl_glyph, option_glyph, shift_glyph,
                        capslock_glyph, capsword_glyph, xcase_glyph, layer_border;

#define HEADER_ROW_Y 6
#define ROW_HEIGHT mononoki->line_height
#define ROW_OFFSET (menu_item*2)
#define MENU_START_Y bbt->line_height+ROW_OFFSET
#define ROW_CALC (menu_item*(mononoki->line_height))+(menu_item*2) + HEADER_ROW_Y
#define ROW_Y ((row+1)*(mononoki->line_height) + 2) + HEADER_ROW_Y
#define BOX_ROW_Y (mononoki->line_height) + HEADER_ROW_Y

char* leaders[][2] = {

    {"[AD]", "Adjust"},
    {"[DD]", "Dyn Macro"},
    {"[EC]", "@caracarn"},
    {"[ET]", "@trueip"},
    {"[SA]", "Arr Apps"},
    {"[SC]", "Scrn Clip"},
    {"[SS]", "Scrn Snag"},
    {"[RR]", "FW Flash"}
 };


 char* passers[][2] = {

     {"[A]", "Ad!"},
     {"[B]", "LbD"},
     {"[D]", "D!2"},
     {"[I]", "T!P"},
     {"[J]", "JbD"},
     {"[L]", "L2c"},
     {"[N]", "Nv_"},
     {"[O]", "Pdn"},
     {"[P]", "P@s"},
     {"[Q]", "StQ"},
     {"[R]", "IWR"},
     {"[S]", "S1b"},
     {"[T]", "Tit"},
     {"[Y]", "Lab"}
 };

#define LCD_LINE_ONE LCD_HEIGHT - 14*(mononoki->line_height)
#define LCD_LINE_TWO LCD_HEIGHT - 13*(mononoki->line_height)
#define LCD_LINE_THREE LCD_HEIGHT - 12*(mononoki->line_height)
#define LCD_LINE_FOUR LCD_HEIGHT - 11*(mononoki->line_height)
#define LCD_LINE_FIVE LCD_HEIGHT - 10*(mononoki->line_height)
#define LCD_LINE_SIX LCD_HEIGHT - 9*(mononoki->line_height)
#define LCD_LINE_SEVEN LCD_HEIGHT - 8*(mononoki->line_height)
#define LCD_LINE_EIGHT LCD_HEIGHT - 7*(mononoki->line_height)
#define LCD_LINE_NINE LCD_HEIGHT - 6*(mononoki->line_height)
#define LCD_LINE_TEN LCD_HEIGHT - 5*(mononoki->line_height)
#define LCD_LINE_ELEVEN LCD_HEIGHT - 4*(mononoki->line_height)
#define LCD_LINE_TWELVE LCD_HEIGHT - 3*(mononoki->line_height)
#define LCD_LINE_THIRTEEN LCD_HEIGHT - 2*(mononoki->line_height)
#define LCD_LINE_FOURTEEN LCD_HEIGHT - 1*(mononoki->line_height)
#define LCD_LINE_FIFTEEN LCD_HEIGHT - mononoki->line_height

#define LCD_LAYER_LINE LCD_HEIGHT - 5*(mononoki->line_height)
#define LCD_MOD_LINE LCD_HEIGHT - (command_glyph->height+20)
#define LCD_STATUS_LINE os_glyph->height+40

#define HSV_INACTIVE 0, 0, 128
#define HSV_ACTIVE CLR_THM2

void draw_layer(void) {
    if (lcd_dirty) {
        qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (layer_border->width))/2), LCD_LAYER_LINE - 5, layer_border, HSV_WHITE, HSV_BLACK);
        dprintln("Drawing border");
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _BASE:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "BASE"))/2), LCD_LAYER_LINE, mononoki, "BASE", CLR_THM2, HSV_BLACK);
                break;
            case _COLEMAK_DH:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "TYPING"))/2), LCD_LAYER_LINE, mononoki, "TYPING", CLR_THM2, HSV_BLACK);
                break;
            case _GAMING:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "GAMING"))/2), LCD_LAYER_LINE, mononoki, "GAMING", CLR_THM2, HSV_BLACK);
                break;
            case _GAMENUM:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "GAMENUM"))/2), LCD_LAYER_LINE, mononoki, "GAMENUM", CLR_THM2, HSV_BLACK);
                break;
            case _HEX:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "HEX"))/2), LCD_LAYER_LINE, mononoki, "HEX", CLR_THM2, HSV_BLACK);
                break;
            case _NAVIGATION:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "NAVIGATION"))/2), LCD_LAYER_LINE, mononoki, "NAVIGATION", CLR_THM2, HSV_BLACK);
                break;
            case _NUMPAD:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "NUMPAD"))/2), LCD_LAYER_LINE, mononoki, "NUMPAD", CLR_THM2, HSV_BLACK);
                break;
            case _SYMBOL:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "SYMBOL"))/2), LCD_LAYER_LINE, mononoki, "SYMBOL", CLR_THM2, HSV_BLACK);
                break;
            case _VIM:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "VIM"))/2), LCD_LAYER_LINE, mononoki, "VIM", CLR_THM2, HSV_BLACK);
                break;
            case _FUNCTION:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "FUNCTION"))/2), LCD_LAYER_LINE, mononoki, "FUNCTION", CLR_THM2, HSV_BLACK);
                break;
            case _APPSWITCH:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "APPSWITCH"))/2), LCD_LAYER_LINE, mononoki, "APPSWITCH", CLR_THM2, HSV_BLACK);
                break;
            case _ADJUST:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "ADJUST"))/2), LCD_LAYER_LINE, mononoki, "ADJUST", CLR_THM2, HSV_BLACK);
                break;
        }
    }
}

void draw_header(void) {
    if (lcd_dirty) {
        #ifdef KYRIA_KEYBOARD
            qp_drawtext_recolor(lcd_surface, 10, (os_glyph->height-mononoki->line_height), mononoki, "Kyria", CLR_THM2, HSV_BLACK);
            qp_drawtext_recolor(lcd_surface, 10, (os_glyph->height), mononoki, "rev 4.1", CLR_THM2, HSV_BLACK);
        #endif
        #ifdef ELORA_KEYBOARD
            qp_drawtext_recolor(lcd_surface, 10, (os_glyph->height-mononoki->line_height), mononoki, "Elora", CLR_THM2, HSV_BLACK);
            qp_drawtext_recolor(lcd_surface, 10, (os_glyph->height), mononoki, "rev 2.0", CLR_THM2, HSV_BLACK);
        #endif
    }
}

void draw_os(void) {
    static uint8_t last_os = 0;
    if (lcd_dirty || last_os != user_config.system.os) {
        if (last_os != user_config.system.os) {
            qp_close_image(os_glyph);
            switch(user_config.system.os) {
                case MACOS:
                    os_glyph = qp_load_image_mem(gfx_apple_glyph);
                break;
                case WINDOWS:
                    os_glyph = qp_load_image_mem(gfx_windows_glyph);
                break;
                case LINUX:
                    os_glyph = qp_load_image_mem(gfx_linux_glyph);
                break;
                default:
                    os_glyph = qp_load_image_mem(gfx_circle_x);
                break;
            }
            last_os = user_config.system.os;
        }
        switch(user_config.system.os) {
            case MACOS:
                qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (os_glyph->width + 2))), 10, os_glyph, HSV_WHITE, HSV_BLACK);
            break;
            case WINDOWS:
                qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (os_glyph->width + 2))), 10, os_glyph, HSV_BLUE, HSV_BLACK);
            break;
            case LINUX:
                qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (os_glyph->width + 2))), 10, os_glyph, HSV_WHITE, HSV_BLACK);
            break;
            default:
                qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (os_glyph->width + 2))), 10, os_glyph, HSV_RED, HSV_BLACK);
            break;
        }
    }
}

void draw_status(void) {
    #define STATUS_GLYPH_WIDTH capsword_glyph->width
    #define STATUS_INTERSPACE ((LCD_WIDTH-(STATUS_GLYPH_WIDTH*3))/4)
    #define LEFT_GLYPH_POS STATUS_INTERSPACE
    #define CENTER_GLYPH_POS LEFT_GLYPH_POS + STATUS_GLYPH_WIDTH + STATUS_INTERSPACE
    #define RIGHT_GLYPH_POS CENTER_GLYPH_POS + STATUS_GLYPH_WIDTH + STATUS_INTERSPACE

    if (lcd_dirty) {
        if (caps_word_on) {
            qp_drawimage_recolor(lcd_surface, LEFT_GLYPH_POS, LCD_STATUS_LINE, capsword_glyph, HSV_ACTIVE, HSV_BLACK);
            qp_drawimage_recolor(lcd_surface, RIGHT_GLYPH_POS, LCD_STATUS_LINE, capslock_glyph, HSV_INACTIVE, HSV_BLACK);
        } else if (host_keyboard_led_state().caps_lock) {
            qp_drawimage_recolor(lcd_surface, LEFT_GLYPH_POS, LCD_STATUS_LINE, capsword_glyph, HSV_INACTIVE, HSV_BLACK);
            qp_drawimage_recolor(lcd_surface, RIGHT_GLYPH_POS, LCD_STATUS_LINE, capslock_glyph, HSV_ACTIVE, HSV_BLACK);
        } else {
            qp_drawimage_recolor(lcd_surface, LEFT_GLYPH_POS, LCD_STATUS_LINE, capsword_glyph, HSV_INACTIVE, HSV_BLACK);
            qp_drawimage_recolor(lcd_surface, RIGHT_GLYPH_POS, LCD_STATUS_LINE, capslock_glyph, HSV_INACTIVE, HSV_BLACK);
        }

        switch(xcase_state) {
            case XCASE_ON:
                qp_drawimage_recolor(lcd_surface, CENTER_GLYPH_POS, LCD_STATUS_LINE, xcase_glyph, HSV_ACTIVE, HSV_BLACK);
            break;
            case XCASE_WAIT:
                qp_drawimage_recolor(lcd_surface, CENTER_GLYPH_POS, LCD_STATUS_LINE, xcase_glyph, HSV_WHITE, HSV_BLACK);
            break;
            default:
                qp_drawimage_recolor(lcd_surface, CENTER_GLYPH_POS, LCD_STATUS_LINE, xcase_glyph, HSV_INACTIVE, HSV_BLACK);
            break;
        }
    }
}

void draw_mods(void) {
    static uint8_t        last_mods           = 0;
           bool           isOneShotCtrl       = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;
           bool           isOneShotShift      = get_oneshot_mods() & MOD_MASK_SHIFT || get_oneshot_locked_mods() & MOD_MASK_SHIFT;
           bool           isOneShotAlt        = get_oneshot_mods() & MOD_MASK_ALT || get_oneshot_locked_mods() & MOD_MASK_ALT;
           bool           isOneShotGui        = get_oneshot_mods() & MOD_MASK_GUI || get_oneshot_locked_mods() & MOD_MASK_GUI;
           uint8_t        current_mods        = get_mods() | get_weak_mods() | get_oneshot_mods();
    if (lcd_dirty || last_mods != current_mods) {
        last_mods = current_mods;
        if (last_mods & MOD_MASK_GUI) {
            if (isOneShotGui) {
                qp_drawimage_recolor(lcd_surface, ((command_glyph->width*3)+20), LCD_MOD_LINE, command_glyph, HSV_WHITE, HSV_BLACK);
            } else {
                qp_drawimage_recolor(lcd_surface, ((command_glyph->width*3)+20), LCD_MOD_LINE, command_glyph, HSV_ACTIVE, HSV_BLACK);
            }
        } else {
            qp_drawimage_recolor(lcd_surface, ((command_glyph->width*3)+20), LCD_MOD_LINE, command_glyph, HSV_INACTIVE, HSV_BLACK);
        }

        if (last_mods & MOD_MASK_CTRL) {
            if (isOneShotCtrl) {
                qp_drawimage_recolor(lcd_surface, (5), LCD_MOD_LINE, ctrl_glyph, HSV_WHITE, HSV_BLACK);
            } else {
                qp_drawimage_recolor(lcd_surface, (5), LCD_MOD_LINE, ctrl_glyph, HSV_ACTIVE, HSV_BLACK);
            }
        } else {
            qp_drawimage_recolor(lcd_surface, (5), LCD_MOD_LINE, ctrl_glyph, HSV_INACTIVE, HSV_BLACK);
        }

        if (last_mods & MOD_MASK_ALT) {
            if (isOneShotAlt) {
                qp_drawimage_recolor(lcd_surface, (command_glyph->width+10), LCD_MOD_LINE, option_glyph, HSV_WHITE, HSV_BLACK);
            } else {
                qp_drawimage_recolor(lcd_surface, (command_glyph->width+10), LCD_MOD_LINE, option_glyph, HSV_ACTIVE, HSV_BLACK);
            }
        } else {
            qp_drawimage_recolor(lcd_surface, (command_glyph->width+10), LCD_MOD_LINE, option_glyph, HSV_INACTIVE, HSV_BLACK);
        }

        if (last_mods & MOD_MASK_SHIFT) {
            if (isOneShotShift) {
                qp_drawimage_recolor(lcd_surface, ((command_glyph->width*2)+15), LCD_MOD_LINE, shift_glyph, HSV_WHITE, HSV_BLACK);
            } else {
                qp_drawimage_recolor(lcd_surface, ((command_glyph->width*2)+15), LCD_MOD_LINE, shift_glyph, HSV_ACTIVE, HSV_BLACK);
            }
        } else {
            qp_drawimage_recolor(lcd_surface, ((command_glyph->width*2)+15), LCD_MOD_LINE, shift_glyph, HSV_INACTIVE, HSV_BLACK);
        }
    }
}


bool module_post_init_user(void) {
    os_glyph = qp_load_image_mem(gfx_circle_x);
    command_glyph = qp_load_image_mem(gfx_command_glyph);
    ctrl_glyph = qp_load_image_mem(gfx_ctrl_glyph);
    option_glyph = qp_load_image_mem(gfx_option_glyph);
    shift_glyph = qp_load_image_mem(gfx_shift_glyph);
    capsword_glyph = qp_load_image_mem(gfx_capsword);
    capslock_glyph = qp_load_image_mem(gfx_capslock);
    xcase_glyph = qp_load_image_mem(gfx_xcase);
    layer_border = qp_load_image_mem(gfx_layer_border);
    dprintln("Loading layer_border into memory");
    mononoki = qp_load_font_mem(font_mononoki);
    bbt = qp_load_font_mem(font_bigbluetermmono);
    lcd_dirty = true;
    dprintln("module_post_init_user");
    draw_status();
    draw_os();
    draw_status();
    draw_layer();
    draw_mods();
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);
    return false;
}

void render_menu_header(const char *heading) {
    uint16_t width = qp_textwidth(bbt, heading);
    uint16_t left = ((LCD_WIDTH - width)/2) - 3;
    uint16_t right = LCD_WIDTH - ((LCD_WIDTH - width)/2) + 3;
    uint16_t top = 4;
    uint16_t bottom = top + bbt->line_height + 2;

    qp_rect(lcd_surface, left, top, right, bottom, CLR_MENU_BG, true);
    qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), HEADER_ROW_Y, bbt, heading, CLR_MENU_FG, CLR_MENU_BG);
    qp_rect(lcd_surface, left, top, right, bottom, HSV_BLACK, false);
}

void draw_leader_screen(char* array[][2], int size) {
    if (lcd_dirty) {

        int row =0;

        qp_clear(lcd_surface);
        // render_menu_header("LEADING");

        int rows = size / sizeof(array[0]);
        for (int i = 0; i < rows; i++) {
            qp_drawtext_recolor(lcd_surface, 3, ROW_Y, mononoki, array[i][0], CLR_MENU_BG, HSV_BLACK);
            qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - 3) - qp_textwidth(mononoki, array[i][1])), ROW_Y, mononoki, array[i][1], CLR_SEL_BG, HSV_BLACK);
            row++;
        }
        qp_rect(lcd_surface, 0, BOX_ROW_Y - 2, LCD_WIDTH - 1, ((row + 1) * mononoki->line_height) + HEADER_ROW_Y + 3, CLR_MENU_BG, false);
        render_menu_header("LEADING");
    }
}

void draw_pass_screen(char* array[][2], int size) {
    if (lcd_dirty) {
        bool left_column = true;
        int row = 0;

        qp_clear(lcd_surface);
        // render_menu_header("PASS-KEYS");

        int rows = size / sizeof(array[0]);
        for (int i = 0; i < rows; i++) {
            if (left_column) {
                qp_drawtext_recolor(lcd_surface, 3, ROW_Y, mononoki, array[i][0], CLR_MENU_BG, HSV_BLACK);
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH/2) - qp_textwidth(mononoki, array[i][1]))-5, ROW_Y, mononoki, array[i][1], CLR_SEL_BG, HSV_BLACK);
                left_column = false;
            } else {
                qp_drawtext_recolor(lcd_surface, (LCD_WIDTH/2)+5, ROW_Y, mononoki, array[i][0], CLR_MENU_BG, HSV_BLACK);
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - 3) - qp_textwidth(mononoki, array[i][1])), ROW_Y, mononoki, array[i][1], CLR_SEL_BG, HSV_BLACK);
                left_column = true;
                row++;
            }
        }
        qp_rect(lcd_surface, 0, BOX_ROW_Y - 2, LCD_WIDTH - 1, ((row + 1) * mononoki->line_height) + HEADER_ROW_Y + 3, CLR_MENU_BG, false);
        render_menu_header("PASS-KEYS");
    }
}

void draw_macro_status(void) {
    if (lcd_dirty) {
        if (user_runtime_state.kb.dyn_recording) {
            qp_circle(lcd_surface, LCD_WIDTH/2, 8, 5, HSV_RED, true);
        }
    }
}

void housekeeping_task_keymap(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
            if (get_highest_layer(layer_state | default_layer_state) == _ADJUST) {
                render_menu();
            } else if (is_passing()) {
                dprintln("QPAINTER is_passing");
                draw_pass_screen(passers, sizeof(passers));
            }
            else if (is_leading()){
                draw_leader_screen(leaders, sizeof(leaders));
            }
            else {
                if (lcd_dirty) {
                    dprintln("QPAINTER lcd_dirty");
                    qp_clear(lcd_surface);
                }
                dyn_display = false;
                draw_header();
                draw_status();
                draw_os();
                draw_macro_status();
                draw_status();
                draw_layer();
                draw_mods();
            }
            lcd_dirty = false;
            qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
            qp_flush(lcd);
        // }
    }
}

bool display_module_housekeeping_task_user(bool second_display) {
    return false;
}

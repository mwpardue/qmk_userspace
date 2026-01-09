#include QMK_KEYBOARD_H

#include "qp.h"
#include "qp_surface.h"
#include "img/KEEBS-small.qgf.h"
#include "img/apple-glyph.qgf.h"
#include "img/PD.qgf.h"

const custom_shift_key_t custom_shift_keys[] = {
  {KC_LSFT, KC_DEL},
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                     KC_6, KC_7, KC_8, KC_9, KC_0, KC_ESC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                     KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TAB,
        KC_BSPC, KC_A, KC_S, KC_D, KC_F, KC_G,                    KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_BSPC,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MUTE, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_SPACE,
                        KC_LEFT, KC_RIGHT,                                    UG_SPDD, UG_SPDU,
                                            KC_BSPC, KC_ENTER, KC_ENTER, KC_SPACE),
};
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif

void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;
}
painter_device_t my_surface;
painter_device_t lcd;
painter_image_handle_t keebs, pd;

static uint8_t my_framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(240, 320, 16)]; // Allocate a buffer for a 16bpp 240x80 RGB565 display
void keyboard_post_init_kb(void) {
    keebs = qp_load_image_mem(gfx_apple_glyph);
    pd = qp_load_image_mem(gfx_PD);
    lcd = qp_ili9341_make_spi_device(240, 320, VIK_SPI_CS, DISPLAY_DC_PIN, DISPLAY_RST_PIN, 8, 0);
    my_surface = qp_make_rgb565_surface(240, 320, my_framebuffer);
    qp_power(lcd, true);
    qp_init(my_surface, QP_ROTATION_0);
    qp_init(lcd, QP_ROTATION_0);
    backlight_enable();
    backlight_level(BACKLIGHT_LEVELS);
    qp_clear(lcd);
    qp_drawimage(my_surface, 0, 0, keebs);
    qp_drawimage(my_surface, 100, 100, pd);
    qp_surface_draw(my_surface, lcd, 0, 0, true);
    qp_flush(lcd);
    keyboard_post_init_user();
}

void housekeeping_task_keymap(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        qp_drawimage(my_surface, 0, 0, keebs);
        qp_drawimage(my_surface, 100, 100, pd);
        qp_surface_draw(my_surface, lcd, 0, 0, 0);
        qp_flush(lcd);
        // }
    }
}


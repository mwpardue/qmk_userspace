#include "caracarn.h"
#include "features/rgb_matrix_custom.h"
#include "definitions/layers.h"
#include "modules/mwpardue/casemodes/casemodes.h"
#include "features/secrets.h"
#ifdef SMART_CASE_ENABLE
    #include "features/smart_case.h"
#endif
#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

extern enum xcase_state xcase_state;
#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
// extern bool caps_word_on;
#endif

extern led_config_t g_led_config;

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return true;
}

void rgb_matrix_set_custom_indicators(uint8_t led_min, uint8_t led_max, int led_type, uint16_t hue, uint8_t sat, uint8_t val) {
        val = rgb_matrix_get_val();
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            HSV hsv = {
                .h = hue,
                .s = sat,
                .v = val,
            };
                if (HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB rgb = hsv_to_rgb(hsv);
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
               }
        }
}

//
void set_layer_rgb_matrix(uint16_t hue, uint8_t sat, uint8_t val, uint8_t led_min, uint8_t led_max) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    RGB rgb       = hsv_to_rgb(hsv);
    // rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        switch (rgb_matrix_get_flags()) {
            case LED_FLAG_ALL:
            case LED_FLAG_UNDERGLOW:
                if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
                break;
        }
    }
}

void rgb_custom_thumb_indicators(uint16_t hue, uint8_t sat, uint8_t val) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    RGB rgb       = hsv_to_rgb(hsv);
        rgb_matrix_set_color(11, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(42, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_user(void) { rgb_matrix_indicators_keymap(); return true; }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    bool isOneShotLockedCtrl = get_oneshot_locked_mods() & MOD_MASK_CTRL;
    bool isOneShotCtrl       = get_oneshot_mods() & MOD_MASK_CTRL;
    bool isOneShotLockedAlt = get_oneshot_locked_mods() & MOD_MASK_ALT;
    bool isOneShotAlt       = get_oneshot_mods() & MOD_MASK_ALT;
    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotShift       = get_oneshot_mods() & MOD_MASK_SHIFT;
    bool isOneShotLockedGui = get_oneshot_locked_mods() & MOD_MASK_GUI;
    bool isOneShotGui       = get_oneshot_mods() & MOD_MASK_GUI;
    // bool isXcase = (xcase_state == XCASE_WAIT) || (xcase_state == XCASE_ON);

    if (!rgb_matrix_indicators_advanced_keymap(led_min, led_max)) {
            return false;
        }

#ifdef RGB_MATRIX_CUSTOM_ENABLED

    switch (get_highest_layer(layer_state | default_layer_state)) {
        // case _FUNCTION:
        //     set_layer_rgb_matrix(FUNCTION_UNDERGLOW, led_min, led_max);
        //     break;
        // case _HEX:
        //     set_layer_rgb_matrix(HEX_UNDERGLOW, led_min, led_max);
        //     break;
        case _VIM:
            RGB_MATRIX_INDICATOR_SET_COLOR(26, 255, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(27, 0, 0, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(28, 255, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(29, 0, 0, 255);
            break;
        case _FUNCTION:
            switch (get_highest_layer(default_layer_state)) {
                case _BASE:
                    RGB_MATRIX_INDICATOR_SET_COLOR(1, 255, 0, 0);
                    break;
                case _GAMING:
                    RGB_MATRIX_INDICATOR_SET_COLOR(2, 255, 0, 0);
                    break;
                case _COLEMAK_DH:
                    RGB_MATRIX_INDICATOR_SET_COLOR(3, 255, 0, 0);
                    break;
                case _GAMENUM:
                    RGB_MATRIX_INDICATOR_SET_COLOR(4, 255, 0, 0);
                    break;
                break;
            };
        // case _VIM:
        //     rgb_matrix_set_color_all(255, 0, 0);
        //     break;
        // default:
        //     set_layer_rgb_matrix(rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val(), led_min, led_max);

 #endif
            break;
    }

    // if (is_typing_secrets()) {
    //     rgb_matrix_set_color_all(255, 0, 0);
    // }
    if (is_caps_word_on()) {
        RGB_MATRIX_INDICATOR_SET_COLOR(6, 128, 0, 128);
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(6, 255, 0, 0);
    }
    if (is_passing()) {
        RGB_MATRIX_INDICATOR_SET_COLOR(18, 252, 107, 3 );
        RGB_MATRIX_INDICATOR_SET_COLOR(49, 252, 107, 3 );
    }
    if (xcase_state == XCASE_ON || xcase_state == XCASE_WAIT) {
        RGB_MATRIX_INDICATOR_SET_COLOR(6, 0, 255, 0);
    }

    // if (get_highest_layer(layer_state) == _FUNCTION) {
    //     switch (get_highest_layer(default_layer_state)) {
    //         case _BASE:
    //             RGB_MATRIX_INDICATOR_SET_COLOR(1, 255, 0, 0);
    //             break;
    //         case _GAMING:
    //             RGB_MATRIX_INDICATOR_SET_COLOR(2, 255, 0, 0);
    //             break;
    //         case _COLEMAK_DH:
    //             RGB_MATRIX_INDICATOR_SET_COLOR(3, 255, 0, 0);
    //             break;
    //         case _GAMENUM:
    //             RGB_MATRIX_INDICATOR_SET_COLOR(4, 255, 0, 0);
    //             break;
    //     }
    // }

  if (isOneShotShift) {
    RGB_MATRIX_INDICATOR_SET_COLOR(15, 255, 225, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(40, 255, 225, 0);
  }

  if (isOneShotCtrl) {
    RGB_MATRIX_INDICATOR_SET_COLOR(13, 255, 225, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(42, 255, 225, 0);
  }

  if (isOneShotAlt) {
    RGB_MATRIX_INDICATOR_SET_COLOR(14, 255, 225, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(41, 255, 225, 0);
  }

  if (isOneShotGui) {
    RGB_MATRIX_INDICATOR_SET_COLOR(16, 255, 225, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(39, 255, 225, 0);
  }

  if (isOneShotLockedShift) {
    RGB_MATRIX_INDICATOR_SET_COLOR(15, 255, 0, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(40, 255, 0, 0);
  }

  if (isOneShotLockedCtrl) {
    RGB_MATRIX_INDICATOR_SET_COLOR(13, 255, 0, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(42, 255, 0, 0);
  }

  if (isOneShotLockedAlt) {
    RGB_MATRIX_INDICATOR_SET_COLOR(14, 255, 0, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(41, 255, 0, 0);
  }

  if (isOneShotLockedGui) {
    RGB_MATRIX_INDICATOR_SET_COLOR(16, 255, 0, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(39, 255, 0, 0);
  }


    // if (isXcase && caps_word_on) {
    //     RGB_MATRIX_INDICATOR_SET_COLOR(24, 255, 255, 255);
    // } else if (isXcase) {
    //     RGB_MATRIX_INDICATOR_SET_COLOR(24, 128, 0, 128);
    // }

    return false;
}

#include "caracarn.h"
#include "features/tapdance.h"

// #ifdef HLC_TFT_DISPLAY
// #include "features/qpainter.h"
// #endif

#include "caracarn_runtime.h"
// #ifdef RAW_ENABLE
//     #include "raw_hid.h"
// #endif

#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

// #ifdef QMENU_ENABLE
//     #include "features/qkeys.h"
// #endif

#ifdef CAPITALIZE_KEY_ENABLE
    #ifdef SMART_THUMB_KEYS_ENABLE
        #error Do not enable both Capitalize Key and Smart Thumb Key
    #endif
#endif

user_config_t user_config;
// painter_menu_t painter_menu;
// bool capslock_state = false;

uint32_t eeconfig_update_user_datablock_handler(const void *data, uint8_t offset, uint8_t size) {
    eeconfig_update_user_datablock(data, offset, size);
    return 0;
}

uint32_t eeconfig_read_user_datablock_handler(void *data, uint8_t offset, uint8_t size) {
    eeconfig_read_user_datablock(data, offset, size);
    return 0;
}

void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  eeconfig_read_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
// #ifdef KYRIA_KEYBOARD
//     #ifndef HALCYON_KEYBOARD
//         setPinOutput(24);
//         // Turn the LED off
//         // (Due to technical reasons, high is off and low is on)
//         writePinHigh(24);
//     #endif
// #endif
}

void keyboard_post_init_user(void) {
    // painter_menu.state.menu_selector = 0;
    // painter_menu.state.submenu_selector = 0;
    // #if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
    //     keyboard_post_init_transport_sync();
    // #endif
}

__attribute__((weak)) void eeconfig_init_keymap(void) {}
void                       eeconfig_init_user(void) {
    memset(&user_config, 0, sizeof(user_config_t));
    // user_config.painter.hsv.primary = (HSV) {
    //     .h = 118,
    //     .s = 255,
    //     .v = 255,
    // };
    // user_config.painter.hsv.secondary = (HSV) {
    //     .h = 43,
    //     .s = 255,
    //     .v = 255,
    // };
    user_config.system.os = MACOS;
    user_config.tapping_term.shift = 175;
    user_config.tapping_term.modtap = 200;
    user_config.tapping_term.gqt = 125;
    user_config.tapping_term.shift_gqt = 100;
    // dprintf("Initialized user_config.painter.hsv.primary: %d, %d, %d\n", user_config.painter.hsv.primary.h, user_config.painter.hsv.primary.s, user_config.painter.hsv.primary.v);
    // dprintf("Initialized user_config.painter.hsv.secondary: %d, %d, %d\n", user_config.painter.hsv.secondary.h, user_config.painter.hsv.secondary.s, user_config.painter.hsv.secondary.v);
    eeconfig_init_keymap();
    eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
}

// void matrix_init_user(void) {
     // Enable or disable debugging
     // debug_enable=true;
// }

// #ifdef RAW_ENABLE
// void raw_hid_receive(uint8_t *data, uint8_t length) {
//   raw_hid_send(data, length);
//   // Your code goes here. data is the packet received from host.
// }
// #endif

// Matrix scan

__attribute__ ((weak)) void matrix_scan_keymap(void) {
}

void matrix_scan_user(void) {
// #ifdef ACHORDION_ENABLE
//     achordion_task();
// #endif

// #ifdef SMART_CASE_ENABLE
//     check_disable_smart_case();
// #endif
//
// #ifdef CAPSLOCK_TIMER_ENABLE
//     check_disable_capslock();
// #endif

#ifdef CASEMODE_ENABLE
  caps_word_idle_timer();
#endif

#ifdef CAPSWORD_ENABLE
    caps_word_task();
#endif

#ifdef CUSTOM_ONESHOT_MODS_ENABLE
    check_oneshot_mods_timeout();
#endif

// #ifdef HLC_TFT_DISPLAY
//     qmenu_timer();
// #endif

    matrix_scan_keymap();
}

// #ifdef HLC_TFT_DISPLAY
//     layer_state_t layer_state_set_kb(layer_state_t state) {
//         dprintln("lcd_dirty layer change");
//         lcd_dirty = true;
//         return state;
//     }
// #endif

// #ifdef ACHORDION_ENABLE
//  bool achordion_chord(uint16_t tap_hold_keycode,
//                       keyrecord_t* tap_hold_record,
//                       uint16_t other_keycode,
//                       keyrecord_t* other_record) {
//   // Exceptionally consider the following chords as holds, even though they
//   // are on the same hand in Dvorak.
//   switch (tap_hold_keycode) {
//     case LHM_T: //F   + W, Q
//       if ((other_keycode == KC_W) || (other_keycode == KC_Q)) {return true;}
//     case LHM_R:
//       if (other_keycode == LIL_THM) {return true;}
//     case LQM_S:
//       if (other_keycode == LIL_THM) {return true;}
//     case LHM_A:
//       if ((other_keycode == KC_C) || (other_keycode == LOL_THM)) {return true;}
//     case LHM_S:
//       if ((other_keycode == KC_QUOT) || (other_keycode == KC_DOT) || (other_keycode == KC_SCLN)) {return true;}
//       break;
//   }
//
//   // Also allow same-hand holds when the other key is in the rows below the
//   // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
//   #ifdef SPLIT_KEYBOARD
//     //if (tap_hold_keycode->event.key.row % (MATRIX_ROWS / 2) >= 4) { return true; }
//   #endif
//   // Otherwise, follow the opposite hands rule.
//   return achordion_opposite_hands(tap_hold_record, other_record);
//   dprintf("Achordion opposite hands\n");
// }
//
//   uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
//    switch (tap_hold_keycode) {
//     case UIL_THM:
//     case UOL_THM:
//     case LUTHUM1:
//     case LUTHUM2:
//     case LIL_THM:
//     case LOL_THM:
//     case CLOL_THM:
//     case UOR_THM:
//     case UIR_THM:
//     case LIR_THM:
//     case LOR_THM:
//     case RUTHUM2:
//     case RUTHUM1:
//     case CLUTHUM2:
//     case CRUTHUM2:
//     case CLOR_THM:
//     case CLIL_THM:
//     case CUIL_THM:
//     case UIG_THM:
//     case LUGTHUM:
//     case LOG_THM:
//     case LIG_THM:
//     case LHM_MNL:
//     case LHM_MNR:
//     case CLIR_THM:
//        return 0;  // Bypass Achordion for these keys.
//        dprintln("Bypassing achordion for timeout");
//    }
//
//    return get_achordion_tapping_term();  // Otherwise use a timeout of 800 ms.
//    dprintln("Using achordion 800ms timeout");
//  }
// #endif

// Process record

#ifdef CASEMODE_ENABLE
bool use_default_xcase_separator(uint16_t keycode, const keyrecord_t *record) {
    // for example:
    switch (keycode) {
        case LUTHUM2:
        case LOL_THM:
        case RUTHUM2:
        case CRUTHUM2:
        case XCASE:
        case (XCASE & 0xff):
            return false;
         case KC_A ... KC_Z:
         case KC_1 ... KC_0:
          dprintf("default xcase separator from caracarn\n");
             return true;
         default:
            return false;
     }
    return false;
}
#endif

// #ifdef HLC_TFT_DISPLAY
//     bool led_update_user(led_t led_state) {
//         if (capslock_state != host_keyboard_led_state().caps_lock) {
//             lcd_dirty = true;
//             dprintln("caracarn lcd_dirty1");
//             capslock_state = host_keyboard_led_state().caps_lock;
//         }
//         return false;
//     }
// #endif

// #ifdef DYNAMIC_MACRO_ENABLE
// bool dynamic_macro_record_start_user(int8_t direction) {
//     user_runtime_state.kb.dyn_recording = true;
// #ifdef HLC_TFT_DISPLAY
//     lcd_dirty = true;
//         dprintln("caracarn lcd_dirty2");
// #endif
//     return true;
// }

// bool dynamic_macro_record_end_user(int8_t direction) {
//     user_runtime_state.kb.dyn_recording = false;
// #ifdef HLC_TFT_DISPLAY
//     lcd_dirty = false;
//         dprintln("caracarn lcd_dirty3");
// #endif
//     return true;
// }
// #endif

///////////////////////////////////////////////////////////////////////////////
// Debug logging
///////////////////////////////////////////////////////////////////////////////
#if !defined(NO_DEBUG) && defined(COMMUNITY_MODULE_KEYCODE_STRING_ENABLE)
#pragma message "dlog_record: enabled"

// KEYCODE_STRING_NAMES_USER(
//   KEYCODE_STRING_NAME(ARROW),
//   KEYCODE_STRING_NAME(UPDIR),
//   KEYCODE_STRING_NAME(STDCC),
//   KEYCODE_STRING_NAME(USRNAME),
//   KEYCODE_STRING_NAME(TMUXESC),
//   KEYCODE_STRING_NAME(SRCHSEL),
//   KEYCODE_STRING_NAME(SELWORD),
//   KEYCODE_STRING_NAME(SELWBAK),
//   KEYCODE_STRING_NAME(SELLINE),
//   KEYCODE_STRING_NAME(RGBBRI),
//   KEYCODE_STRING_NAME(RGBNEXT),
//   KEYCODE_STRING_NAME(RGBHUP),
//   KEYCODE_STRING_NAME(RGBHRND),
//   KEYCODE_STRING_NAME(RGBDEF1),
//   KEYCODE_STRING_NAME(RGBDEF2),
// );

static void dlog_record(uint16_t keycode, keyrecord_t* record) {
  if (!debug_enable) { return; }
  uint8_t layer = read_source_layers_cache(record->event.key);
  bool is_tap_hold = IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode);
  xprintf("L%-2u ", layer);  // Log the layer.
  if (IS_COMBOEVENT(record->event)) {  // Combos don't have a position.
    xprintf("combo   ");
  } else {  // Log the "(row,col)" position.
    xprintf("(%2u,%2u) ", record->event.key.row, record->event.key.col);
  }
  xprintf("%-4s %-7s %s\n",  // "(tap|hold) (press|release) <keycode>".
      is_tap_hold ? (record->tap.count ? "tap" : "hold") : "",
      record->event.pressed ? "press" : "release",
      get_keycode_string(keycode));
}
#else
#pragma message "dlog_record: disabled"
#define dlog_record(keycode, record)
#endif  // !defined(NO_DEBUG) && defined(COMMUNITY_MODULE_KEYCODE_STRING_ENABLE)

//
// Begin main user loop
//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

dlog_record(keycode, record);

#ifdef CUSTOM_LEADER_ENABLE
  if (!process_leader(keycode, record)) { return false; }
#endif

#ifdef COMBO_ENABLE

    // Process combos
    switch (process_combos(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

// #ifdef ACHORDION_ENABLE
//     if (!process_achordion(keycode, record)) { return false; }
// #endif

#ifdef CAPSWORD_ENABLE
    if (!process_caps_word(keycode, record)) { return false; }
#endif

// #ifdef GQT_ENABLE
//   if (!process_global_quick_tap(keycode, record)) { return false; }
// #endif

#ifdef SMART_THUMB_KEYS_ENABLE
  // Process smart thumb keys
  switch (process_smart_thumb_keys(keycode, record)) {
    case PROCESS_RECORD_RETURN_TRUE:
      return true;
    case PROCESS_RECORD_RETURN_FALSE:
      return false;
    default:
      break;
  };
#endif

// #ifdef SMART_CASE_ENABLE
//         // Process smart case
//     switch (process_smart_case(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
// #endif
//
#ifdef SHORTCUTS_ENABLE
    // Process custom_shortcuts
    switch (process_custom_shortcuts(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef CASEMODE_ENABLE
    // Process case modes
    if (!process_case_modes(keycode, record)) { return false; }
#endif

// #ifdef CAPSLOCK_TIMER_ENABLE
//     // Extend capslock timer
//      switch (process_capslock_timer_extension(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
// #endif

#ifdef SECRETS_ENABLE
    // Process secrets
     switch (process_secrets(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef WINDOW_SWAPPER_ENABLE
    // Process window swapper
    switch (process_window_swapper(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef RGB_MATRIX_ENABLED
    // Process RGB Toggle Key
    switch (process_rgb_matrix_keys(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

// #ifdef QMENU_ENABLE
//     // Process RGB Toggle Key
//     switch (process_qmenu_keys(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
// #endif
//
// #ifdef CUSTOM_SHIFT_ENABLE
//     // Process custom_shift
//    switch (process_custom_shift(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
// #endif

#ifdef MACRO_ENABLE
    // Process macros
    switch (process_macros(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

// #ifdef SELECT_WORD_ENABLE
//     // Process select word
//     switch (process_select_word(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
// #endif
//
// #ifdef EOS_ENABLE
//     process_eos(keycode, record);
// #endif
//
// #ifdef DEFAULT_MOD_ENABLE
//     // Process default modifier key
//     switch (process_default_mod_key(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
// #endif
//
// #ifdef CAPITALIZE_KEY_ENABLE
//      // Process capitalize key
//     switch (process_capitalize_key(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
// #endif

#ifdef OS_TOGGLE_ENABLE
    // Process OS toggle
    switch (process_os_toggle(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    if (debug_enable) {
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    };
#endif
    return true;
}

// Tap-hold configuration

#ifdef TAPHOLD_ENABLE
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return get_hold_on_other_key_press_result(keycode);
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    return get_quick_tap_term_result(keycode);
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return get_permissive_hold_result(keycode);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return get_tapping_term_result(keycode);
}
#endif

__attribute__((weak)) void housekeeping_task_keymap(void) {}
void housekeeping_task_user(void) {
#if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
    housekeeping_task_transport_sync();
#endif
    housekeeping_task_keymap();
}

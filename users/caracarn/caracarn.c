#include "caracarn.h"
#include "features/tapdance.h"

#ifdef QUANTUM_PAINTER_ENABLE
    #include "features/qpainter.h"
#endif

#include "caracarn_runtime.h"

#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

#ifdef CAPITALIZE_KEY_ENABLE
    #ifdef SMART_THUMB_KEYS_ENABLE
        #error Do not enable both Capitalize Key and Smart Thumb Key
    #endif
#endif

user_config_t user_config;

#ifdef QUANTUM_PAINTER_ENABLE
painter_menu_t painter_menu;
#endif // QUANTUM_PAINTER_ENABLE

bool capslock_state = false;

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
}

void keyboard_post_init_user(void) {
    dprintln("keyboard_post_init_user");
    #ifdef QUANTUM_PAINTER_ENABLE
        display_post_init_user();
    #endif

    #if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
        keyboard_post_init_transport_sync();
    #endif
}

void suspend_power_down_user(void) {
    #if !defined(HLC_TFT_DISPLAY) && defined(QUANTUM_PAINTER_ENABLE)
    display_power_down();
    #endif
}

void suspend_wakeup_init_user(void) {
    #if !defined(HLC_TFT_DISPLAY) && defined(QUANTUM_PAINTER_ENABLE)
    display_power_up();
    #endif
}

__attribute__((weak)) void eeconfig_init_keymap(void) {}
void                       eeconfig_init_user(void) {
    memset(&user_config, 0, sizeof(user_config_t));
    #ifdef QUANTUM_PAINTER_ENABLE
        user_config.painter.hsv.primary = (HSV) {
            .h = 118,
            .s = 255,
            .v = 255,
        };
        user_config.painter.hsv.secondary = (HSV) {
            .h = 43,
            .s = 255,
            .v = 255,
        };
    #endif
    user_config.system.os = MACOS;
    user_config.tapping_term.shift = 175;
    user_config.tapping_term.modtap = 200;
    user_config.tapping_term.gqt = 125;
    user_config.tapping_term.shift_gqt = 100;
    eeconfig_init_keymap();
    eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
}

__attribute__ ((weak)) void matrix_scan_keymap(void) {
}

void matrix_scan_user(void) {
#ifdef CASEMODE_ENABLE
  caps_word_idle_timer();
#endif

#ifdef CAPSWORD_ENABLE
    caps_word_task();
#endif

#ifdef CUSTOM_ONESHOT_MODS_ENABLE
    check_oneshot_mods_timeout();
#endif

#ifdef QMENU_ENABLE
    qmenu_timer();
#endif

    matrix_scan_keymap();
}

#ifdef QUANTUM_PAINTER_ENABLE
    layer_state_t layer_state_set_user(layer_state_t state) {
        dprintln("lcd_dirty layer change");
        display_make_dirty(true);
        return state;
    }
#endif

// Process record

#ifdef QUANTUM_PAINTER_ENABLE
    bool led_update_user(led_t led_state) {
        if (capslock_state != host_keyboard_led_state().caps_lock) {
            display_make_dirty(true);
            dprintln("caracarn lcd_dirty1");
            capslock_state = host_keyboard_led_state().caps_lock;
        }
        return false;
    }
#endif

#ifdef DYNAMIC_MACRO_ENABLE
bool dynamic_macro_record_start_user(int8_t direction) {
    user_runtime_state.kb.dyn_recording = true;
#ifdef QUANTUM_PAINTER_ENABLE
        display_make_dirty(true);
        dprintln("caracarn lcd_dirty2");
#endif
    return true;
}

bool dynamic_macro_record_end_user(int8_t direction) {
    user_runtime_state.kb.dyn_recording = false;
#ifdef QUANTUM_PAINTER_ENABLE
        display_make_dirty(false);
        dprintln("caracarn lcd_dirty3");
#endif
    return true;
}
#endif

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

#ifdef CAPSWORD_ENABLE
    if (!process_caps_word(keycode, record)) { return false; }
#endif

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

#ifdef QMENU_ENABLE
    // Process RGB Toggle Key
    switch (process_qmenu_keys(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

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

void housekeeping_task_keymap(void) {
}

void housekeeping_task_user(void) {
    #if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
        housekeeping_task_transport_sync();
    #endif
    #ifdef QUANTUM_PAINTER_ENABLE
        display_module_housekeeping_task_keymap();
    #endif
        housekeeping_task_keymap();
}

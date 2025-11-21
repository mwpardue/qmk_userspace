#include QMK_KEYBOARD_H

#include "eeprom.h"
#include "definitions/layers.h"
#include "definitions/keycodes.h"
#include "features/transport_sync.h"
#include "caracarn_runtime.h"

void keyboard_post_init_transport_sync(void);
void keyboard_post_init_keymap(void);
void housekeeping_task_transport_sync(void);
uint32_t eeconfig_update_user_datablock_handler(const void *data, uint8_t offset, uint8_t size);
uint32_t eeconfig_read_user_datablock_handler(void *data, uint8_t offset, uint8_t size);


#ifdef TAP_DANCE_ENABLE
    #include "features/tapdance.h"
#endif

#ifdef COMBO_ENABLE
    #include "features/combos.h"
#endif

#ifdef GQT_ENABLE
  #include "features/global_quick_tap.h"
#endif

#ifdef ACHORDION_ENABLE
    #include "features/achordion.h"
#endif

#ifdef SMART_CASE_ENABLE
    #include "features/smart_case.h"
#endif

#ifdef CASEMODE_ENABLE
    #include "features/casemodes.h"
#endif

#ifdef CUSTOM_ONESHOT_MODS_ENABLE
    #include "features/custom_oneshot_mods.h"
#endif

#ifdef SMART_THUMB_KEYS_ENABLE
    #include "features/smart_thumb_keys.h"
#endif

#ifdef SECRETS_ENABLE
    #include "features/secrets.h"
#endif

#ifdef CAPSWORD_ENABLE
    #include "features/caps_word.h"
#endif

#ifdef TAPHOLD_ENABLE
    #include "features/taphold.h"
#endif

#ifdef CAPSLOCK_TIMER_ENABLE
    #include "features/capslock_timer.h"
#endif

#ifdef OS_TOGGLE_ENABLE
    #include "features/os_toggle.h"
#endif

#ifdef MACRO_ENABLE
    #include "features/macros.h"
#endif

#ifdef DYNAMIC_MACRO_ENABLE
    #include "features/dynamic_macro.h"
#endif

#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

#ifdef DEFAULT_MOD_ENABLE
    #include "features/default_mod_key.h"
#endif

#ifdef CAPITALIZE_KEY_ENABLE
    #include "features/capitalize_key.h"
#endif

#ifdef SELECT_WORD_ENABLE
    #include "features/select_word.h"
#endif

#ifdef WINDOW_SWAPPER_ENABLE
    #include "features/window_swapper.h"
#endif

#ifdef SHORTCUTS_ENABLE
    #include "features/custom_shortcuts.h"
#endif

#ifdef CUSTOM_SHIFT_ENABLE
    #include "features/custom_shift.h"
#endif

#ifdef OLED_MENU_ENABLE
    #include "features/rgb_matrix_keys.h"
#endif

#ifdef QMENU_ENABLE
    #include "features/qkeys.h"
    #include "features/qhelper.h"
#endif

#ifdef RGB_MATRIX_LEDMAPS_ENABLED
    #include "features/rgb_matrix_ledmaps.h"
#endif

#ifdef EOS_ENABLE
  #include "features/eos_util.h"
#endif

#ifdef OLED_MENU_ENABLE
    #include "features/oled_menu.h"
#endif

void matrix_scan_keymap(void);

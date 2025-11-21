#pragma once

// Optimization to save memory
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_MUSIC_MODE
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#define EECONFIG_USER_DATA_SIZE 64

// Make it easier to work with tap hold
#ifdef CAPSWORD_ENABLE
    #define CAPS_WORD_IDLE_TIMEOUT 5000
#endif

#ifdef CASEMODE_ENABLE
  #define CAPS_WORD_IDLE_TIMEOUT 5000
#endif

#define FLOW_TAP_TERM 175

#ifdef TAPHOLD_ENABLE
    #define TAPPING_TERM_PER_KEY
    #define TAPPING_FORCE_HOLD_PER_KEY
    #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
    #define PERMISSIVE_HOLD_PER_KEY
    #define QUICK_TAP_TERM_PER_KEY
#endif

    #define ONESHOT_TAP_TOGGLE 2
    #define ONESHOT_TIMEOUT 5000
    #define TAPPING_TOGGLE 1
    #define SHIFT_TAPPING_TERM 150
    #define TAPPING_TERM 125
    #define MODTAP_TAPPING_TERM 200
#ifdef ACHORDION_ENABLE
    #define ACHORDION_TAPPING_TERM 800
#endif
#ifdef GQT_ENABLE
    #define GQT_TAPPING_TERM 175
    #define SGQT_TAPPING_TERM 150
#endif

#ifdef CUSTOM_ONESHOT_MODS_ENABLE
    #define CUSTOM_ONESHOT_TIMEOUT 2000
#endif

// Configure combos
#ifdef COMBO_ENABLE
    #define COMBO_TERM 40
    #define EXTRA_SHORT_COMBOS
    #define COMBO_STRICT_TIMER
    #define COMBO_HOLD_TERM 150
    #define COMBO_MUST_TAP_PER_COMBO
#endif

    #define MACRO_TIMER 10

// Mouse key speed and acceleration.
#ifdef MOUSEKEY_ENABLE
    #define MK_3_SPEED
    #define MK_W_OFFSET_UNMOD 5
    #define MK_W_INTERVAL_UNMOD 1
    #define MK_W_OFFSET_0 10
    #define MK_W_INTERVAL_0 120
    #define MK_W_OFFSET_1 5
    #define MK_W_INTERVAL_1 1
    #define MK_W_OFFSET_2 10
    #define MK_W_INTERVAL_2 20
#endif

#ifdef LAYER_LOCK_ENABLE
    #define LAYER_LOCK_IDLE_TIMEOUT 60000
#endif

#ifdef SPLIT_KEYBOARD
    #ifdef CUSTOM_SPLIT_TRANSPORT_SYNC
    #define SPLIT_TRANSACTION_IDS_USER RPC_ID_USER_RUNTIME_STATE_SYNC
    #endif
#endif

#ifdef OLED_ENABLE
    #define VIEWPORT_HEIGHT 7
    #define VIEWPORT_WIDTH 21
#endif


#define QUANTUM_PAINTER_NUM_IMAGES 12

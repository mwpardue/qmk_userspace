#pragma once

#include <quantum/color.h>

typedef struct PACKED {
    hsv_t primary;
    hsv_t secondary;
} dual_hsv_t;

typedef union {
    uint32_t raw;
    struct {
    // #ifdef COMMUNITY_MODULE_CASE_MODES_ENABLE
        uint8_t xcase_state :8;
        uint16_t llocked :8;
    #ifdef CUSTOM_LEADER_ENABLE
        uint8_t menu :8;
    #endif // CUSTOM_LEADER_ENABLE
        bool debug_enabled :1;
        bool caps_word_on :1;
    // #endif // COMMUNITY_MODULE_CASE_MODES_ENABLE
        bool write_to_eeprom :1;
        bool dyn_recording :1;
        bool secrets_typing :1;
    #ifdef QUANTUM_PAINTER_ENABLE
        bool lcd_dirty :1;
    #endif // QUANTUM_PAINTER_ENABLE
    } kb;
} user_runtime_state_t;

extern user_runtime_state_t user_runtime_state;

typedef struct PACKED {
    #ifdef QUANTUM_PAINTER_ENABLE
        struct {
            dual_hsv_t hsv;
        } painter;
    #endif // QUANTUM_PAINTER_ENABLE
        struct {
            uint8_t os :8;
        } system;
        struct {
            uint16_t shift :16;
            uint16_t modtap :16;
            uint16_t gqt :16;
            uint16_t shift_gqt :16;
        } tapping_term;
} user_config_t;

_Static_assert(sizeof(user_config_t) <= EECONFIG_USER_DATA_SIZE, "User EECONFIG block is not large enough.");

extern user_config_t user_config;

#ifdef QUANTUM_PAINTER_ENABLE
typedef struct {
    struct {
        uint8_t menu_selector :8;
        uint8_t submenu_selector :8;
    } state;
} painter_menu_t;

extern painter_menu_t painter_menu;
#endif //  QUANTUM_PAINTER_ENABLE

typedef enum {
    OTHER,
    MACOS,
    WINDOWS,
    LINUX
} os_t;

extern os_t os;

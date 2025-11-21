#pragma once

/*#include <quantum/color.h>*/

/*typedef struct PACKED {*/
/*    hsv_t primary;*/
/*    hsv_t secondary;*/
/*} dual_hsv_t;*/

typedef union {
    uint32_t raw;
    struct {
    #ifdef CASEMODE_ENABLE
        uint8_t xcase_state :8;
        uint16_t llocked :8;
    #ifdef CUSTOM_LEADER_ENABLE
        uint8_t menu :8;
    #endif
        bool debug_enabled :1;
        bool caps_word_on :1;
    #endif
        bool write_to_eeprom :1;
        bool dyn_recording :1;
    } kb;
} user_runtime_state_t;

extern user_runtime_state_t user_runtime_state;

typedef struct PACKED {
    /*struct {*/
    /*    dual_hsv_t hsv;*/
    /*} painter;*/
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

/*typedef struct {*/
/*    struct {*/
/*        uint8_t menu_selector :8;*/
/*        uint8_t submenu_selector :8;*/
/*    } state;*/
/*} painter_menu_t;*/
/**/
/*extern painter_menu_t painter_menu;*/

typedef enum {
    OTHER,
    MACOS,
    WINDOWS,
    LINUX
} os_t;

extern os_t os;

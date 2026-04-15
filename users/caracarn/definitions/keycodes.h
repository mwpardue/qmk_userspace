#pragma once

#include "layers.h"

// Custom keycodes

enum {
    CUSTOM_KEYCODE_START = QK_USER,

#ifdef MACRO_ENABLE
    TIPS,
#endif

#ifdef SECRETS_ENABLE
    KC_SECRET_1,
    KC_SECRET_2,
    KC_SECRET_3,
    KC_SECRET_4,
    KC_SECRET_5,
    KC_SECRET_6,
    KC_SECRET_7,
    KC_SECRET_8,
    KC_SECRET_9,
    KC_SECRET_10,
    KC_SECRET_11,
    KC_SECRET_12,
    KC_SECRET_13,
    KC_SECRET_14,
    KC_SECRET_15,
    KC_SECRET_16,
    KC_SECRET_17,
    KC_SECRET_18,
    KC_SECRET_19,
    KC_SECRET_20,
#endif

#ifdef OS_TOGGLE_ENABLE
    TG_MAC, TG_WIN, TG_LIN,
#endif

#ifdef CAPITALIZE_KEY_ENABLE
    SP_CAP, CAP_KEY, SS_CAPS,
#endif

#ifdef DEFAULT_MOD_KEY_ENABLE
    SP_MOD, DEF_MOD,
#endif

#ifdef SMART_THUMB_KEYS_ENABLE
    XCTHUM, SMCASE,
#endif

#ifdef SMART_CASE_ENABLE
    MC_CAPS, MC_WORD, MC_CAML, MC_SNAK, MC_KBAB,
#endif

#ifdef TAP_DANCE_ENABLE
    TD_COPY, TD_PAST, TD_SSFL, TD_SNIP, TD_SSEL,
#endif

#ifdef SHORTCUTS_ENABLE
    COLEMAK, QWERTY, DF_LAYR, DF_LYR1, DF_LYR2, DF_LYR3, DF_LYR4,
    GUI_ESC, PASSPAL, ADJ_EXT, SEL_WRD, SEL_LIN, CAP_MEH,
    SM_SWIT, TG_OS, ADJ_LYR, MT_STTI, MT_DTTI, MT_MTTI,
    MT_GTTI, MT_SGTI, MT_STTD, MT_DTTD, MT_MTTD, MT_GTTD,
    MT_SGTD, TT_CHEK, GMG_CW, SXCASE, M_EXIT, M_ARROW, MEH_ESC,
    UNDO, REDO, HTTPS,
#endif

#ifdef SELECT_WORD_ENABLE
    MC_SELW,
#endif

#ifdef WINDOW_SWAPPER_ENABLE
    MC_SWLE, MC_SWRI, MC_SWAP, MC_MODM, MC_MODP, SF_MODP,
#endif

#ifdef COMBO_ENABLE
    SM_LOGN, SM_ESC, SM_CW, SM_PAR, SM_CUR, SM_BRC, SM_ANG, SM_CAP,
#endif

#ifdef LAYER_LOCK_ENABLE
    LLOCK,
#endif

#ifdef CUSTOM_LEADER_ENABLE
  LEADER,
#endif

#ifdef RGB_MATRIX_ENABLE
    RGB_CHG, RGB_MDT, TB_MENU, MENU_AD, MENU_MD, MENU_MU, MENU_AU, RGB_SLD, RGB_REC,
#endif


    CUSTOM_KEYCODE_END
};

// Left thumb keys

    // Left Inner Thumb Keys
    #define LIL_THM LT(_NAVIGATION, KC_BSPC)
    #define GLIL_THM LT(_NAVIGATION, KC_TAB)
    #define CLIL_THM LT(_NAVIGATION, KC_T)

    // Left Outer Thumb Keys
    #define LOL_THM LT(_NUMPAD, KC_ENTER)
    #define GLOL_THM LT(_NUMPAD, KC_E)
    #define CLOL_THM LSFT_T(KC_ENTER)
    #define SLOL_THM LSFT_T(KC_T)

// Right thumb keys

    // Right Inner Thumb Keys
    #define LIR_THM LT(_SYMBOL, KC_SPACE)
    #define CLIR_THM LT(_SYMBOL, KC_E)

    // Right Outer Thumb Keys
    #define SLOR_THM LT(_VIM, KC_ENTER)
    #define LOR_THM HYPR_T(KC_ENTER)
    #define CLOR_THM RSFT_T(KC_ENTER)

// Typing Layer Keys
#define SFT_Z LSFT_T(KC_Z)
#define SFT_QUE RSFT_T(KC_SLSH)

// Mod-taps (QWERTY)

// Left Hand
#define LHM_A LCTL_T(KC_A)
#define LQM_S LALT_T(KC_S)
#define LHM_D LSFT_T(KC_D)
#define LHM_F LGUI_T(KC_F)
#define LCM_R LALT_T(KC_R)
#define LCM_S LSFT_T(KC_S)
#define LCM_T LGUI_T(KC_T)
#define MEH_PP MEH_T(KC_F14)
#define MEH_TAB MEH_T(KC_TAB)
#define MEH_ESC MEH_T(KC_ESC)
#define MEH_QUO MEH_T(KC_QUOT)
#define NUM_PP LT(_NUMPAD, KC_F14)
#define VIM_PP LT(_VIM, KC_F14)

// Right Hand
#define RHM_SCN RCTL_T(KC_SCLN)
#define RHM_L   RALT_T(KC_L)
#define RHM_K   RSFT_T(KC_K)
#define RHM_J   RGUI_T(KC_J)
#define RCM_N   RGUI_T(KC_N)
#define RCM_E   RSFT_T(KC_E)
#define RCM_I   RALT_T(KC_I)
#define RCM_O   RCTL_T(KC_O)

// One-shot mods

#define OSMLSFT OSM(MOD_LSFT)
#define OSMRSFT OSM(MOD_RSFT)
#define OSMLCTL OSM(MOD_LCTL)
#define OSMLALT OSM(MOD_LALT)
#define OSMRALT OSM(MOD_RALT)
#define OSMLGUI OSM(MOD_LGUI)
#define OSMRGUI OSM(MOD_RGUI)
#define OSMRCTL OSM(MOD_RCTL)
#define OSMHYPR OSM(MOD_HYPR)
#define OSMMEH  OSM(MOD_MEH)

// Layer-taps

#define NUM_Z LT(_NUMPAD, KC_Z)
#define VIM_QUE LT(_VIM, KC_SLSH)
#define MON_L LALT(KC_H)
#define MON_R LALT(KC_L)
#define MON_U LALT(KC_K)
#define MON_D LALT(KC_J)
#define SS_WIN LCMD(LSFT(KC_5))
#define SPC_L LCTL(LALT(KC_H))
#define SPC_R LCTL(LALT(KC_L))
#define MOV_LFT LCTL(LSFT(KC_TAB))
#define MOV_RGT LCTL(KC_TAB)
#define TAB_LFT LGUI(KC_H)
#define TAB_RGT LGUI(KC_L)
#define TAB_UP LGUI(KC_K)
#define TAB_DWN LGUI(KC_J)
#define TOBAS TO(_BASE)
#define TOHEX TO(_HEX)
#define TOFUN TO(_FUNCTION)
#define TGFUN TG(_FUNCTION)
#define TGHEX TG(_HEX)
#define TOADJ ADJ_LYR
#define CAD LCTL(LALT(KC_DELETE))
#define VIM_XCS LT(_VIM, KC_F23)
#define VIM_ESC LT(_VIM, KC_ESC)
#define VIM_BSL LT(_VIM, KC_BSLS)
#define MEH_Z MEH_T(KC_Z)
#define MEH_QUE MEH_T(KC_SLSH)
#define MEH_BSL MEH_T(KC_BSLS)
#define MEH_XCS MEH_T(KC_F23)
#define SFT_BSL RSFT_T(KC_BSLS)
#define SFT_XCS LSFT_T(KC_F23)
#define SFT_ESC RSFT_T(KC_ESC)
#define SFT_QUO LSFT_T(KC_QUOT)
#define NUM_ESC LT(_NUMPAD, KC_ESC)

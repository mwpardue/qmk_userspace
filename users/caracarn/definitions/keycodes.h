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
    UNDO, REDO,
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

    // Upper Left Thumb Keys
    #define UIL_THM LT(_FUNCTION, KC_F17)
    #define UOL_THM KC_F22

    // Lower Left Thumb Keys
    #define LUTHUM0 MON_L
    #define LUTHUM1 MON_R
    #define LUTHUM2 LT(_NUMPAD, KC_MINS)
    #define LIL_THM LT(_NAVIGATION, KC_TAB)
    #define CLOL_THM LT(_NUMPAD, KC_ENTER)

    // Alt Base Thumb Keys
    /*#define CLUTHUM2 LT(_NUMPAD, KC_MINS)*/
    #define CLUTHUM2 LCTL_T(KC_UNDS)
    #define GLIL_THM LT(_NAVIGATION, KC_BSPC)
    #define CLIL_THM LT(_NAVIGATION, KC_T)
    #define CUIL_THM KC_F20
    #define CUOL_THM MON_R
    #define GLOL_THM LT(_NUMPAD, KC_ENTER)
    #define SLOL_THM LSFT_T(KC_ENTER)
    #define LOL_THM LT(_NUMPAD, KC_TAB)

// Right thumb keys

    // Lower Right Thumb Keys
    #define RUTHUM0 KC_RBRC
    #define RUTHUM1 KC_LBRC
    #define RUTHUM2 LT(_VIM, KC_BSLS)
    #define LIR_THM LT(_SYMBOL, KC_SPACE)
    #define CLOR_THM HYPR_T(KC_ENTER)

    // Upper Right Thumb Keys
    #define UIR_THM LT(_FUNCTION, KC_F16)
    #define UOR_THM KC_F23

    // Alt Base Thumb Keys
    #define CLIR_THM LT(_SYMBOL, KC_ENTER)
    #define LOR_THM KC_ENTER
    #define CUIR_THM OSMHYPR
    #define CUOR_THM OSMMEH
    #define CRUTHUM2 RCTL_T(KC_DEL)
    #define SLOR_THM RSFT_T(KC_F16)

// Typing Layer Keys
#define CTL_Z LCTL_T(KC_Z)
#define CTL_X LCTL_T(KC_X)
#define GUI_Z LGUI_T(KC_Z)
#define SFT_Z LSFT_T(KC_Z)
#define CTL_QUE RCTL_T(KC_SLSH)
#define GUI_QUE RGUI_T(KC_SLSH)
#define SFT_QUE RSFT_T(KC_SLSH)
#define SFT_QUO RSFT_T(KC_QUOT)
#define SYM_QUE LT(_SYMBOL, KC_SLSH)
#define SFT_ESC LSFT_T(KC_ESC)
#define GUI_C LGUI_T(KC_C)
#define GUI_COM RGUI_T(KC_COMM)
#define ALT_X LALT_T(KC_X)
#define GUI_X LGUI_T(KC_X)
#define ALT_DOT RALT_T(KC_DOT)
#define GUI_DOT RGUI_T(KC_DOT)
#define B_NUM LT(_NUMPAD, KC_B)

// Right thumb keys

// Gaming keys
#define UIG_THM LM(_GAMENUM, MOD_LCTL)
#define LUGTHUM LM(_GAMENUM, MOD_LSFT)
#define LOG_THM LT(_GAMENUM, KC_TAB)
#define LIG_THM LSFT_T(KC_SPACE)

// Mod-taps (QWERTY)

// Left Hand
#define LHM_A LCTL_T(KC_A)
#define LQM_S LALT_T(KC_S)
#define LHM_D LSFT_T(KC_D)
#define LHM_F LGUI_T(KC_F)
#define LCM_R LALT_T(KC_R)
#define LCM_S LSFT_T(KC_S)
#define LCM_T LGUI_T(KC_T)
#define CTL_D LCTL_T(KC_D)
#define GUI_D LGUI_T(KC_D)
#define GUI_K LGUI_T(KC_K)
#define SFT_F LSFT_T(KC_F)
#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define SFT_A LSFT_T(KC_A)
#define CTL_D LCTL_T(KC_D)
#define CTL_K RCTL_T(KC_K)
#define GUI_A LGUI_T(KC_A)
#define GUI_SCN RGUI_T(KC_SCLN)
#define SFT_SCN RSFT_T(KC_SCLN)
#define CTL_TAB LCTL_T(KC_TAB)
#define SFT_TAB LSFT_T(KC_TAB)
#define SFT_BSP LSFT_T(KC_BSPC)
#define SFT_QUO RSFT_T(KC_QUOT)
#define LSFT_PP LSFT_T(KC_F13)
#define RSFT_PP RSFT_T(KC_F13)
#define MEH_PP MEH_T(KC_F14)
#define MEH_TAB MEH_T(KC_TAB)
#define MEH_QUO MEH_T(KC_QUOT)
#define NUM_PP LT(_NUMPAD, KC_F14)
#define VIM_PP LT(_VIM, KC_F14)
#define MEH_Z MEH_T(KC_Z)
#define MEH_QUE MEH_T(KC_SLSH)
#define CTL_QUO RCTL_T(KC_QUOT)
#define GUI_QUO RGUI_T(KC_QUOT)
#define GUI_TAB LGUI_T(KC_TAB)
#define GUI_ESC LGUI_T(SM_ESC)
#define NUM_TAB LT(_NUMPAD, KC_TAB)
#define CTL_MINS LCTL_T(KC_MINS)
#define SFT_DOT LSFT_T(KC_DOT)
#define LHM_X LALT_T(KC_X)
#define LHM_C LSFT_T(KC_C)
#define LHM_V LGUI_T(KC_V)
#define LSM_A LSFT_T(KC_A)
#define LSM_D LCTL_T(KC_D)

// Right Hand
#define RHM_SCN RCTL_T(KC_SCLN)
#define RHM_L   RALT_T(KC_L)
#define RHM_K   RSFT_T(KC_K)
#define RHM_J   RGUI_T(KC_J)
#define RHM_DOT RALT_T(KC_DOT)
#define RHM_COM RSFT_T(KC_COMM)
#define RCM_N   RGUI_T(KC_N)
#define RCM_E   RSFT_T(KC_E)
#define RCM_I   RALT_T(KC_I)
#define RCM_O   RCTL_T(KC_O)
#define RSM_SCN LSFT_T(KC_SCLN)
#define RSM_K LCTL_T(KC_K)
#define GUI_4 RGUI_T(KC_4)
#define SFT_5   RSFT_T(KC_5)
#define ALT_6   RALT_T(KC_6)
#define CTL_DOT   RCTL_T(KC_DOT)

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

#define LALT_PP LALT_T(KC_F18)
#define RALT_PP RALT_T(KC_F19)
#define LGUI_PP LGUI_T(KC_F18)
#define RGUI_PP RGUI_T(KC_F19)
#define MONUM MO(_NUMPAD)
#define MOVIM MO(_VIM)
#define NUM_Z LT(_NUMPAD, KC_Z)
#define VIM_QUE LT(_VIM, KC_SLSH)
#define NUM_J LT(_NUMPAD, KC_J)
#define NUM_BSP LT(_NUMPAD, KC_BSPC)
#define MON_L LALT(KC_H)
#define MON_R LALT(KC_L)
#define MON_U LALT(KC_K)
#define MON_D LALT(KC_J)
#define SS_WIN LCMD(LSFT(KC_5))
#define PW_AF LCTL(LALT(LSFT((KC_A))))
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
#define SFT_TAB LSFT_T(KC_TAB)
#define LCA_A LCTL(LALT(KC_A))
#define CAD LCTL(LALT(KC_DELETE))
#define GMG_CW LT(_GAMING, KC_F23)
#define MEH_RET MEH_T(KC_ENTER)
#define MEH_ESC MEH_T(KC_ESC)
#define MEH_XCS MEH_T(KC_F22)
#define VIM_X LT(_VIM, KC_X)
#define VIM_DOT LT(_VIM, KC_DOT)
#define MEH_LBR MEH_T(KC_LBRC)
#define MEH_RBR MEH_T(KC_RBRC)
#define MEH_BSL MEH_T(KC_BSLS)
#define WRD_BAK LALT(KC_LEFT)
#define WRD_FWD LALT(KC_RIGHT)

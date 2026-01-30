/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "caracarn.h"

const custom_shift_key_t custom_shift_keys[] = {
  {GLIL_THM, KC_DEL},
};
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
//
// const key_override_t colon_override = {
//     .trigger_mods               = MOD_BIT(KC_LSFT),                       //
//     .layers                     = ~0,                                          //
//     .suppressed_mods            = MOD_BIT(KC_LSFT),                       //
//     .options                    = ko_option_no_unregister_on_other_key_down,                 //
//     .trigger                    = RHM_SCN,                                                     //
//     .replacement                = KC_SCLN,                                                     //
//     .enabled                    = NULL};
//
// // // This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&delete_key_override
};

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
        // keycode = extract_base_tapping_keycode(keycode);
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word)
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
            case KC_MINS:
            case KC_UNDS:
            case KC_BSPC:
            case KC_UP:
            case KC_DOWN:
            case KC_RIGHT:
            case KC_LEFT:
            case KC_LPRN:
            case KC_RPRN:
            case KC_LBRC:
            case KC_RBRC:
            case KC_LCBR:
            case KC_RCBR:
            case KC_SCLN:
            case KC_COLN:
            case KC_SLSH:
            case KC_LSFT:
            case KC_RSFT:
            case LHM_D:
            case RHM_K:
            case SFT_F:
            case SFT_J:
            case SM_ESC:
            case SLOR_THM:
            case SLOL_THM:
            case CLOR_THM:
            case CLOL_THM:
            dprintln("terminate_case_modes");
                // If mod chording disable the mods
                if (record->event.pressed && (get_mods() & MOD_MASK_SHIFT)) {
                    dprintln("Chording shift, allowing case modes to continue");
                    return false;
                }

                if (record->event.pressed && (get_mods() != 0)) {
                    dprintln("Disabling case modes due to mod chording");
                    return true;
                }
                break;
            default:
                dprintln("terminate default action");
                if (record->event.pressed) {
                    return true;
                }
                break;
        }
        return false;
}

enum combos {
    CM_CAPS,
    CM_MLG2,
    CM_PREV,
    CM_PLAY,
    CM_NEXT,
    CM_HEX,
    CM_FUNC,
    CM_BOOT
};


const uint16_t PROGMEM capsword_combo[]     = {LHM_D,       RHM_K,                        COMBO_END};
const uint16_t PROGMEM mtlogin2_combo[]     = {LIL_THM,     LQM_S,     LHM_D,             COMBO_END};
const uint16_t PROGMEM mprev_combo[]        = {VIM_X,       KC_C,                         COMBO_END};
const uint16_t PROGMEM play_combo[]         = {VIM_X,       KC_C,      KC_V,              COMBO_END};
const uint16_t PROGMEM mnext_combo[]        = {KC_C,        KC_V,                         COMBO_END};
const uint16_t PROGMEM hex_combo[]          = {VIM_X,       VIM_DOT,                      COMBO_END};
const uint16_t PROGMEM function_combo[]     = {KC_GRV,      KC_1,                         COMBO_END};
const uint16_t PROGMEM boot_combo[]     = {KC_GRV,          KC_EQL,                       COMBO_END};

combo_t key_combos[] = {
  [CM_CAPS] = COMBO(capsword_combo,     CW_TOGG),
  [CM_MLG2] = COMBO(mtlogin2_combo,     SM_LOGN),
  [CM_PREV] = COMBO(mprev_combo,        KC_MPRV),
  [CM_PLAY] = COMBO(play_combo,         KC_MPLY),
  [CM_NEXT] = COMBO(mnext_combo,        KC_MNXT),
  [CM_HEX]  = COMBO(hex_combo,          TOHEX),
  [CM_FUNC] = COMBO(function_combo,     TOFUN),
  [CM_BOOT] = COMBO(boot_combo,         QK_BOOT)
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
        case KC_LSFT:
        case KC_RSFT:
        case KC_SLSH:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// uint8_t combo_ref_from_layer(uint8_t_layer) {
//     switch (get_highest_layer(layer_state)) {
//         case _NAVIGATION:
//             return _NAVIGATION;
//         default:
//             return _BASE;
//     }
//     return layer;
// }

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
  '*', '*', '*', '*', '*', '*',                              '*', '*', '*', '*', '*', '*',
  '*', 'L', 'L', 'L', 'L', 'L',                              'R', 'R', 'R', 'R', 'R', '*',
  '*', 'L', 'L', 'L', 'L', 'L',                              'R', 'R', 'R', 'R', 'R', 'R',
  '*', 'L', 'L', 'L', 'L', 'L',                              'R', 'R', 'R', 'R', 'R', '*',
                                '*', '*',          '*', '*'
    );

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
  KC_GRV,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  XCASE,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_BSPC, LHM_A,  LQM_S,   LHM_D,   LHM_F,   KC_G,                                                KC_H,    RHM_J,   RHM_K,   RHM_L,   RHM_SCN, KC_QUOT,
  MEH_RET, SFT_Z,  VIM_X,   KC_C,    KC_V,    KC_B,                                                KC_N,    KC_M,    KC_COMM, VIM_DOT, SFT_QUE, MEH_BSL,
                                                       LIL_THM,   LOL_THM,          LOR_THM, LIR_THM
                                                    // NAV/TAB LSHFT/SM_ESC       RSHFT/ENTER SYM/SPACE
),

[_GAMING] = LAYOUT(
  SM_ESC,  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  KC_GRV,  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  MEH_XCS, SFT_Z,   _______, _______, _______, _______,                                             _______, _______, _______, _______, SFT_QUE, _______,
                                                        LIL_THM, GLOL_THM,      _______,  _______
                                                    // NAV/TAB   NUM/ENTER   VIM/ENTER SYM/SPACE
),

[_GAMENUM] = LAYOUT(
  SM_ESC,  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  KC_GRV,  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  MEH_XCS, NUM_Z,   _______, _______, _______, _______,                                             _______, _______, _______, _______, KC_SLSH, _______,
                                                        LIL_THM, SLOL_THM,      CLOR_THM,  _______
                                                    // NAV/TAB   SFT/ENTER   SFT/ENTER SYM/SPACE
),

[_COLEMAK_DH] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  XCASE,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                                KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______,
  _______, LHM_A,   LCM_R,   LCM_S,   LCM_T,   KC_G,                                                KC_M,    RCM_N,   RCM_E,   RCM_I,   RCM_O,   _______,
  MEH_RET, SFT_Z,   VIM_X,   KC_C,    KC_D,    KC_V,                                                KC_K,    KC_H,    _______, _______, SFT_QUE, _______,
                                                        CLIL_THM, SLOL_THM,      KC_ENTER,  _______
                                                    // NAV/TAB    NUM/ESC       VIM/ENTER SYM/SPACE
),

[_NAVIGATION] = LAYOUT(
    _______, _______, _______, TD_SSFL, TD_SNIP, SS_WIN,                                            DM_REC1, DM_PLY1, DM_REC2, DM_PLY2, _______, KC_VOLU,
    _______, UNDO,    MON_L,   MON_U,   MON_R,   REDO,     		                                    WRD_BAK, SELWBAK, SELWORD, WRD_FWD, _______, KC_VOLD,
    KC_BSPC, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XCASE,   KC_MUTE,
    _______, TAB_DWN, TAB_UP,  TD_COPY, TD_PAST, _______,                                           KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
                                                          _______, _______,      _______, KC_SPC
),

[_NUMPAD] = LAYOUT(
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, KC_GRV,  KC_TILD, KC_LCBR, KC_RCBR, TIPS,                                                KC_PLUS, KC_7,    KC_8,    KC_9,    KC_QUOT, KC_BSLS,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                             KC_MINS, KC_4,    KC_5,    KC_6,    KC_DOT,  KC_COLN,
  _______, KC_LT,   KC_GT,   KC_LBRC, KC_RBRC, _______,                                             KC_EQL,  KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
                                                        _______, _______,       _______,  KC_0
),

[_SYMBOL] = LAYOUT(
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_GRV,  KC_GRV,  KC_TILD, KC_LCBR, KC_RCBR, TIPS,                                                _______, KC_AMPR, KC_ASTR, KC_LPRN, _______, _______,
  KC_DEL,  KC_AT,   KC_UNDS, KC_LPRN, KC_RPRN, KC_PIPE,                                             KC_MINS, KC_DLR,  KC_PERC, KC_CIRC, KC_COLN, KC_DQUO,
  _______, KC_LT,   KC_GT,   KC_LBRC, KC_RBRC, M_ARROW,                                             KC_EQL,  KC_EXLM, KC_AT,   KC_HASH, _______, _______,
                                                        KC_BSPC, _______,         _______, _______
),

[_VIM] = LAYOUT(
  _______, SEC20,   _______, _______, SEC18,   SEC5,                                                DM_REC1, DM_PLY1, DM_REC2, DM_PLY2, _______, _______,
  _______, SEC11,   SEC14,   _______, _______, SEC6,                                                SEC17,   SEC16,   SEC15,   SEC7,    SEC8,    _______,
  _______, SEC1,    SEC9,    SEC13,   _______, _______,                                             _______, SEC4,    _______, SEC10,   _______, _______,
  _______, _______, _______, _______, SEC19,   SEC3,                                                SEC12,   SEC2,    _______, _______, _______, _______,
                                                        _______, KC_ENTER,        _______, _______
),

[_HEX] = LAYOUT(
  TGHEX,   _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             KC_GRV,  KC_7,    KC_8,    KC_9,    KC_COLN, _______,
  _______, _______, _______, _______, _______, _______,                                             KC_MINS, KC_4,    KC_5,    KC_6,    KC_DOT,  _______,
  _______, _______, TGHEX,   _______, _______, _______,                                             KC_EQL,  KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
                                                        _______, _______,           _______, KC_0
),

[_FUNCTION] = LAYOUT( \
  TGFUN,   DF_LYR1, DF_LYR2, DF_LYR3, DF_LYR4, _______,                                             RGB_SLD, RGB_REC, _______, _______, _______, _______,
  _______, DF_LAYR, _______, EE_CLR,  _______, _______,                                             RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, _______,
  _______, _______, _______, DB_TOGG, _______, _______,                                             RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, _______,
  _______, MT_STTD, MT_DTTD, MT_MTTD, MT_GTTD, MT_SGTD,                                             MT_SGTI, MT_GTTI, MT_MTTI, MT_DTTI, MT_STTI, TT_CHEK,
                                                        KC_DEL,  _______,         _______, _______
),

[_APPSWITCH] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, KC_BSPC, KC_Z,    _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, MC_SWRI, _______, _______, _______,                                            KC_N,    KC_M,    _______, _______, _______, _______,
                                                        _______, _______,        _______, _______
),

[_ADJUST] = LAYOUT( \
  ADJ_EXT, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  TOBAS,   TOBAS,   _______, EE_CLR,  QK_RBT,  _______,                                             _______, _______,  _______,  _______, _______, _______,  \
  TB_MENU, _______, _______, _______, _______, _______,                                             MENU_AD, MENU_MD,  MENU_MU,  MENU_AU, _______, _______,\
  _______, _______, _______, _______, _______, _______,                                             _______, _______,  _______,  _______, _______, _______,\
                                                        _______, _______,         _______, _______
)
};


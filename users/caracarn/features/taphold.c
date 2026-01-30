#include QMK_KEYBOARD_H

#include "taphold.h"
#include "features/custom_shortcuts.h"
#include "features/tapdance.h"
#include "caracarn_runtime.h"
// #include "modules/getreuer/tap_flow/tap_flow.h"

uint16_t get_custom_tapping_term(uint16_t custom_tapping_term) {
    return custom_tapping_term;
}

void increase_modtap_tapping_term(void) {
    user_config.tapping_term.modtap = user_config.tapping_term.modtap + 5;
}

void increase_shift_tapping_term(void) {
    user_config.tapping_term.shift = user_config.tapping_term.shift + 5;
}

void increase_gqt_tapping_term(void) {
    user_config.tapping_term.gqt = user_config.tapping_term.gqt + 5;
}

void increase_shift_gqt_tapping_term(void) {
    user_config.tapping_term.shift_gqt = user_config.tapping_term.shift_gqt + 5;
}

void decrease_modtap_tapping_term(void) {
    user_config.tapping_term.modtap = user_config.tapping_term.modtap - 5;
}

void decrease_shift_tapping_term(void) {
    user_config.tapping_term.shift = user_config.tapping_term.shift - 5;
}

void decrease_gqt_tapping_term(void) {
    user_config.tapping_term.gqt = user_config.tapping_term.gqt - 5;
}

void decrease_shift_gqt_tapping_term(void) {
    user_config.tapping_term.shift_gqt = user_config.tapping_term.shift_gqt - 5;
}

uint16_t get_tapping_term_result(uint16_t keycode) {
    switch (keycode) {
        // case SPC_HYP:
        case LUTHUM1:
        case LUTHUM2:
        case LOL_THM:
        case LOR_THM:
        case LIL_THM:
        case CLIL_THM:
        case GLIL_THM:
        case RUTHUM2:
        case RUTHUM1:
            return g_tapping_term + 40;
        case UOR_THM:
        case UOL_THM:
        case TD_PAST:
        case TD_COPY:
        case LIR_THM:
        case CLUTHUM2:
        case CLOL_THM:
        case SLOR_THM:
        case SLOL_THM:
        case CRUTHUM2:
        case CLIR_THM:
        case CLOR_THM:
        case NUM_Z:
        case NUM_J:
        // case NUM_TAB:
        case GUI_4:
        case SFT_5:
        case ALT_6:
        case CTL_DOT:
        case VIM_QUE:
        case SYM_QUE:
        case VIM_DOT:
        case VIM_X:
        case MEH_Z:
        case MEH_QUE:
          return g_tapping_term + 100;
        case LHM_A:
        case LQM_S:
        case LHM_F:
        case LCM_R:
        case LCM_T:
        case RCM_N:
        case RCM_I:
        case RCM_O:
        case RHM_J:
        case RHM_L:
        case RHM_SCN:
        case CTL_Z:
        case ALT_X:
        case GUI_C:
        case CTL_QUE:
        case ALT_DOT:
        case GUI_COM:
        case GUI_X:
        case GUI_DOT:
        case CTL_X:
        case GUI_D:
        case GUI_K:
        case CTL_D:
        case CTL_K:
        case GUI_A:
        case GUI_SCN:
          return get_custom_tapping_term(user_config.tapping_term.modtap);
        case SFT_A:
        case SFT_SCN:
        case SFT_F:
        case SFT_J:
        case RHM_K:
        case LHM_D:
        case LHM_C:
        case RHM_COM:
        case LCM_S:
        case RCM_E:
        case SFT_Z:
        case SFT_QUE:
        case SFT_QUO:
        case SFT_ESC:
            return get_custom_tapping_term(user_config.tapping_term.shift);
        default:
            return g_tapping_term;
    }
}

uint16_t get_quick_tap_term_result(uint16_t keycode) {
    switch (keycode) {
        case LHM_A:
        case LQM_S:
        case LHM_F:
        case RHM_SCN:
        // case LIL_THM:
        case LOL_THM:
        case LIR_THM:
        case LOR_THM:
        case GUI_4:
        case SFT_5:
        case ALT_6:
        case CTL_DOT:
            return 0;
    }
    switch (keycode) {
        case QK_MOD_TAP...QK_MOD_TAP_MAX:
        case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
        case QK_MOMENTARY...QK_MOMENTARY_MAX:
        case OSMLSFT:
        case OSMRSFT:
        case OSMLCTL:
        case OSMRCTL:
        case OSMLALT:
        case OSMRALT:
        case OSMLGUI:
        case OSMRGUI:
            return 175;
        default:
            return 0;
    }
}

bool get_hold_on_other_key_press_result(uint16_t keycode) {
    switch (keycode) {
        case LUTHUM1:
        case LUTHUM2:
        case LOL_THM:
        case LOR_THM:
        case RUTHUM2:
        case RUTHUM1:
        case CLUTHUM2:
        case CRUTHUM2:
        case CLOR_THM:
        case CLOL_THM:
        case SLOR_THM:
        case SLOL_THM:
        case SFT_Z:
        case SFT_QUE:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold_result(uint16_t keycode) {
    switch (keycode) {
        case LHM_A:
        case LHM_F:
        case RHM_J:
        case RHM_L:
        case RHM_SCN:
        case LQM_S:
        case SFT_A:
        case SFT_SCN:
        case GUI_D:
        case GUI_K:
        case CTL_D:
        case CTL_K:
        case GUI_A:
        case GUI_SCN:
        case SFT_F:
        case SFT_J:
        case RUTHUM2:
        case LUTHUM2:
        case CTL_Z:
        case ALT_X:
        case GUI_C:
        case CTL_QUE:
        case ALT_DOT:
        case GUI_COM:
        case NUM_Z:
        case NUM_J:
        case GUI_X:
        case GUI_DOT:
        case LHM_C:
        case RHM_COM:
        case CTL_X:
        case GUI_4:
        case SFT_5:
        case ALT_6:
        case CTL_DOT:
        case LHM_D:
        case RHM_K:
        case MEH_Z:
        case MEH_QUE:
        case SFT_QUO:
        case SFT_ESC:
        case VIM_X:
        case VIM_DOT:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}


uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {
    dprintln("[TAP_FLOW_CUSTOM] get_flow_tap_term.");
    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        dprintln("[TAP_FLOW_CUSTOM] get_flow_tap_term->is_flow_tap_key.");
        switch(keycode) {
            case LHM_A:
            case LQM_S:
            case LHM_F:
            case RHM_J:
            case RHM_L:
            case RHM_SCN:
            case CTL_Z:
            case ALT_X:
            case CTL_QUE:
            case ALT_DOT:
            case LCM_R:
            case LCM_T:
            case RCM_N:
            case RCM_I:
            case RCM_O:
            case GUI_4:
            case SFT_5:
            case ALT_6:
            case CTL_DOT:
            case GUI_D:
            case GUI_K:
            case CTL_D:
            case CTL_K:
            case GUI_A:
            case GUI_SCN:
                dprintln("get_tap_flow triggered, gqt case");
                return get_custom_tapping_term(user_config.tapping_term.gqt);
            case LCM_S:
            case RCM_E:
            case LHM_C:
            case RHM_COM:
            case SFT_Z:
            case SFT_QUE:
                dprintln("get_tap_flow triggered, shift gqt case");
                return get_custom_tapping_term(user_config.tapping_term.shift_gqt);
            case NUM_Z:
            case LHM_D:
            case RHM_K:
            case SFT_F:
            case SFT_J:
            case SFT_A:
            case SFT_SCN:
            case SFT_QUO:
            case SFT_ESC:
            case NUM_J:
            case CLIL_THM:
            case GLIL_THM:
                return 1;
            // case SFT_Z:
            // case SFT_QUE:
            default:
                dprintln("get_tap_flow triggered, default case");
                return 0;
        }
    }
    return 0;
}

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    // Exceptionally allow some one-handed chords for hotkeys.
    switch (tap_hold_keycode) {
        case MEH_Z:
            if (other_keycode == LHM_F) {
                return true;
            }
            break;
        case VIM_X:
            if ((other_keycode == KC_B) || (other_keycode == KC_V)) {
                return true;
            }
            break;
    }
    // Otherwise defer to the opposite hands rule.
    return get_chordal_hold_default(tap_hold_record, other_record);
}

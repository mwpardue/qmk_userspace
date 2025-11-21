#include QMK_KEYBOARD_H

#include "dynamic_macro.h"
#include "caracarn_runtime.h"

dyn_macro_t dyn_macro = {.recording = 0};

user_runtime_state_t user_runtime_state;

void dyn_macro_start(uint16_t keycode) {
    keyrecord_t kr;
    kr.event.pressed    = false;
    dyn_macro.recording = keycode;
    process_dynamic_macro(keycode, &kr);
    tap_code16(KC_NO);
    user_runtime_state.kb.dyn_recording = true;
}

void dyn_macro_stop(void) {
    keyrecord_t kr;
    dyn_macro.recording = 0;
    kr.event.pressed    = true;
    process_dynamic_macro(QK_DYNAMIC_MACRO_RECORD_STOP, &kr);
    user_runtime_state.kb.dyn_recording = false;
}

void dyn_macro_play(uint16_t keycode) {
    keyrecord_t kr;
    dyn_macro_stop();
    kr.event.pressed = false;
    process_dynamic_macro(keycode, &kr);
}

void dyn_macro_toggle(uint16_t keycode) {
    if (dyn_macro.recording != 0) {
        dyn_macro_stop();
    } else {
        dyn_macro_start(keycode);
    }
}

void dyn_macro_reset(void) {
    if (dyn_macro.recording != 0) {
        dyn_macro_stop();
        dyn_macro_start(dyn_macro.recording);
        dyn_macro_stop();
    }
}

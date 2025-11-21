#include QMK_KEYBOARD_H

#include "window_swapper.h"
#include "caracarn_runtime.h"

swapper_t swapper = {.state = NONE};

bool is_swapper_keycode(uint16_t keycode) {
    switch (keycode) {
        case MC_SWLE:
        case MC_SWRI:
        case MC_MODM:
        case MC_MODP:
        case SF_MODP:
        case KC_LEFT:
        case KC_RIGHT:
        case KC_DOWN:
        case KC_UP:
        case KC_H:
        case KC_J:
        case KC_K:
        case KC_L:
        case RHM_J:
        case RHM_K:
        case RHM_L:
        case KC_X:
        case KC_Z:
            return true;
        default:
            return false;
    }
}

process_record_result_t process_window_swapper(uint16_t keycode, keyrecord_t *record) {
    if (record != NULL && record->event.pressed) {
        dprintf("Swapper record is not null\n");
        return PROCESS_RECORD_CONTINUE;
    }

    // Finish swapper
    if (!is_swapper_keycode(keycode)) {
        if (swapper.state != NONE) {
            dprintf("swapper.state before=%d\n",swapper.state);
            clear_mods();
            clear_locked_and_oneshot_mods();
            swapper.state = NONE;
            dprintf("swapper.state after=%d\n",swapper.state);
            send_keyboard_report();
        }
        return PROCESS_RECORD_CONTINUE;
    }

    bool isMacOS              = user_config.system.os == MACOS;
    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotShift       = isOneShotLockedShift || get_oneshot_mods() & MOD_MASK_SHIFT;
    bool isShifted            = isOneShotShift || get_mods() & MOD_MASK_SHIFT;

    // Determine swapper mode
    if (swapper.state == NONE) {
        switch(keycode) {
            case MC_SWLE:
            case MC_SWRI:
                swapper.state = isShifted ? ZOOMING_START : SWAPPING_START;
                dprintf("Setting swapper state to SWAPPING_START\n");
                break;
            case MC_MODP:
            case MC_MODM:
                swapper.state = isShifted ? BROWSING_START : TABBING_START;
                break;
        }
        // clear_mods();
    }

    // Start swapper
    switch (swapper.state) {
        case SWAPPING_START:
            switch (keycode) {
                case MC_SWLE:
                case MC_SWRI:
                    if (isMacOS) {
                        register_mods(MOD_LGUI);
                    } else {
                        register_mods(MOD_LALT);
                    }
                    dprintf("Registering mods for MC_SWRI\n");
                    swapper.state = SWAPPING_CONTINUE;
                    break;
            }
            break;
        case TABBING_START:
            switch (keycode) {
                case MC_MODM:
                    register_mods(MOD_LSFT);
                    register_mods(MOD_LCTL);
                    swapper.state = TABBING_CONTINUE;
                    break;
                case MC_MODP:
                    unregister_mods(MOD_LSFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    register_mods(MOD_LCTL);
                    swapper.state = TABBING_CONTINUE;
                    break;
            }
            break;
        case ZOOMING_START:
            switch (keycode) {
                case MC_SWLE:
                case MC_SWRI:
                    unregister_mods(MOD_LSFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    if (isMacOS) {
                        register_mods(MOD_LGUI);
                    } else {
                        register_mods(MOD_LCTL);
                    }
                    swapper.state = ZOOMING_CONTINUE;
                    break;
            }
            break;
        case BROWSING_START:
            switch (keycode) {
                case MC_MODM:
                case MC_MODP:
                    unregister_mods(MOD_LSFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    if (isMacOS) {
                        register_mods(MOD_LGUI);
                    } else {
                        register_mods(MOD_LALT);
                    }
                    swapper.state = BROWSING_CONTINUE;
                    break;
            }
            break;
        default:
            break;
    }

    // Check if action was reversed since started
    switch (swapper.state) {
        case SWAPPING_CONTINUE:
        case TABBING_CONTINUE:
            switch (keycode) {
                case MC_MODM:
                    register_mods(MOD_LSFT);
                    break;
                case MC_SWLE:
                case MC_SWRI:
                case MC_MODP:
                case KC_LEFT:
                case KC_RIGHT:
                case KC_DOWN:
                case KC_UP:
                case KC_X:
                case KC_Z:
                case KC_H:
                case KC_J:
                case KC_K:
                case KC_L:
                case RHM_J:
                case RHM_K:
                case RHM_L:
                    unregister_mods(MOD_LSFT);
                    break;
            }
        default:
            break;
    }

    // Process swap action
    switch (swapper.state) {
        case SWAPPING_CONTINUE:
        case TABBING_CONTINUE:
          switch (keycode) {
            case KC_RIGHT:
            case KC_LEFT:
            case KC_DOWN:
            case KC_UP:
            case KC_X:
            case KC_Z:
            case KC_H:
            case KC_J:
            case KC_K:
            case KC_L:
            case RHM_J:
            case RHM_K:
            case RHM_L:
              return false;
              break;
            case MC_SWLE:
            case MC_SWRI:
              tap_code(KC_TAB);
              break;
          }
          break;
        case ZOOMING_CONTINUE:
            switch (keycode) {
                case MC_SWLE:
                    tap_code(KC_MINS);
                    break;
                case MC_SWRI:
                    tap_code(KC_EQL);
                    break;
            }
            break;
        case BROWSING_CONTINUE:
            switch (keycode) {
                case MC_MODM:
                    if (isMacOS) {
                        tap_code(KC_LBRC);
                    } else {
                        tap_code(KC_LEFT);
                    }
                    break;
                case MC_MODP:
                    if (isMacOS) {
                        tap_code(KC_RBRC);
                    } else {
                        tap_code(KC_RIGHT);
                    }
                    break;
            }
            break;
        default:
          switch (keycode) {
            case KC_LEFT:
            case KC_RIGHT:
            case KC_DOWN:
            case KC_UP:
            case KC_H:
            case KC_J:
            case KC_K:
            case KC_L:
            case RHM_J:
            case RHM_K:
            case RHM_L:
            case KC_X:
            case KC_Z:
              return false;
          }
            break;
    }

    return PROCESS_RECORD_RETURN_FALSE;
}

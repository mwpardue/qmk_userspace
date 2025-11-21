// Copyright 2021-2025 Matthew Pardue
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file smart_select.c
 * @brief Smart Select community module implementation
 */

#include "quantum.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

bool smart_selecting = false;

bool process_record_smart_select(uint16_t keycode, keyrecord_t* record) {
  if (!process_record_smart_select_kb(keycode, record)) {
    return false;
  }

    switch (keycode) {
        case SMART_SELECT:
            if (record->event.pressed) {
                if (smart_selecting) {
                    dprintln("[Smart Select] SS Case IF");
                    smart_selecting = false;
                    tap_code16(LGUI(KC_LEFT));
                    tap_code16(LGUI(LSFT(KC_RIGHT)));
                    return false;
                } else {
                    dprintln("[Smart Select] SS Case ELSE");
                    tap_code16(LALT(KC_LEFT));
                    tap_code16(LSFT(LALT(KC_RIGHT)));
                    smart_selecting = true;
                }
                return false;
            }
            break;
        default:
            if (smart_selecting) {
                dprintln("[Smart Select] Default case");
                smart_selecting = false;
            }
            return true;
            break;
    }

  return true;
}

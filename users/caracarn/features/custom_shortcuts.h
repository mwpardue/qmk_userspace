#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "process_record_result.h"
#include "smart_thumb_keys.h"

#ifndef DEFAULT_MOD_ENABLE
        bool should_send_ctrl(bool isWindowsOrLinux, bool isOneShotShift);
#endif

void smart_escape(void);
process_record_result_t process_custom_shortcuts(uint16_t keycode, keyrecord_t *record);

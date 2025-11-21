#include "caracarn.h"
#include "caracarn_runtime.h"
#include "features/transport_sync.h"
#include "transactions.h"
#ifdef OLED_MENU_ENABLE
    #include "features/rgb_matrix_keys.h"
#endif
#ifdef SMART_CASE_ENABLE
    #include "features/smart_case.h"
#endif
#ifdef CASEMODE_ENABLE
    #include "features/casemodes.h"
#endif
#ifdef OS_TOGGLE_ENABLE
    #include "features/os_toggle.h"
#endif

#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

#include <string.h>

uint32_t transport_user_runtime_state = 0;

extern layer_state_t locked_layers;

user_runtime_state_t user_runtime_state;

#ifdef SMART_CASE_ENABLE
extern smart_case_t smart_case;
#endif

#ifdef CASEMODE_ENABLE
    extern enum xcase_state xcase_state;
    extern bool caps_word_on;
#endif

#ifdef DYNAMIC_MACRO_ENABLE
    extern bool is_dynamic_recording;
#endif

#ifdef CUSTOM_LEADER_ENABLE
    menu_t menu;
#endif

void user_runtime_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_user_runtime_state)) {
        memcpy(&transport_user_runtime_state, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void keyboard_post_init_transport_sync(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_USER_RUNTIME_STATE_SYNC, user_runtime_state_sync);
}

void user_transport_update(void) {
    if (is_keyboard_master()) {
        user_runtime_state.kb.xcase_state = xcase_state;
        user_runtime_state.kb.llocked = locked_layers;
        user_runtime_state.kb.caps_word_on = caps_word_on;
        user_runtime_state.kb.debug_enabled = debug_enable;
        transport_user_runtime_state = user_runtime_state.raw;
    } else {
        user_runtime_state.raw = transport_user_runtime_state;
        xcase_state = user_runtime_state.kb.xcase_state;
        locked_layers = user_runtime_state.kb.llocked;
        caps_word_on = user_runtime_state.kb.caps_word_on;
        debug_enable = user_runtime_state.kb.debug_enabled;
    }
}

void user_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static uint32_t last_sync[1], last_user_state = 0;
        bool            needs_sync = false;

        // Check if the state values are different
        if (memcmp(&transport_user_runtime_state, &last_user_state, sizeof(transport_user_runtime_state))) {
            needs_sync = true;
            memcpy(&last_user_state, &transport_user_runtime_state, sizeof(transport_user_runtime_state));
        }
        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[0]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_RUNTIME_STATE_SYNC, sizeof(user_runtime_state), &user_runtime_state)) {
                last_sync[0] = timer_read32();
            }
            needs_sync = false;
        }
    }
}

void housekeeping_task_transport_sync(void) {
    // Update kb_state so we can send to slave
    user_transport_update();

    // Data sync from master to slave
    user_transport_sync();
}

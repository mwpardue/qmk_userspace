#pragma once
// #include "features/os_toggle.h"

extern uint32_t transport_user_state;

extern uint16_t sft_tapping_term;

extern uint16_t modtap_tapping_term;

extern uint16_t achordion_tapping_term;

extern uint16_t gqt_tapping_term;

extern uint16_t sgqt_tapping_term;

bool check_lock(void) {
    if (is_layer_locked(get_highest_layer(layer_state))) {
        return true;
    } else {
        return false;
    }
}

#ifdef CASEMODE_ENABLE
    extern enum xcase_state xcase_state;
    extern bool caps_word_on;
#endif

bool check_state(void) {
    led_t led_usb_state = host_keyboard_led_state();
    if (led_usb_state.caps_lock || (xcase_state == XCASE_ON) || (xcase_state == XCASE_WAIT) || led_usb_state.num_lock || caps_word_on || is_leading()) {
        return true;
    } else {
        return false;
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void render_led_flags(void);
void render_matrix_mode(void);
void render_rgb_speed(void);
void render_rgb_hue(void);
void render_stt_specs(void);
void render_tt_specs(void);
void render_mt_specs(void);
void render_at_specs(void);

void render_newline(void) {
    oled_write_P(PSTR("\n"), false);
}

void render_blank_line(void) {
    oled_write_P(PSTR("                     "), false);
}


// Modifier Box Components
void render_modifier_box_top(uint8_t modifiers, uint8_t active_mods) {
    static const char PROGMEM inactive_modifier_box_top[] = {
        0x94,0x95,0x95,0x96, 0};
    static const char PROGMEM active_modifier_box_top[] = {
        0x93,0xd2,0xd2,0x9f, 0};
    if (modifiers & active_mods) {
        oled_write_P(active_modifier_box_top, false);
    } else {
        oled_write_P(inactive_modifier_box_top, false);
    }
}

void render_modifier_box_bottom(uint8_t modifiers, uint8_t active_mods) {
    static const char PROGMEM inactive_modifier_box_bottom[] = {
        0xd4,0xd5,0xd5,0xd6, 0};
    static const char PROGMEM active_modifier_box_bottom[] = {
        0xd3,0xd1,0xd1,0xdf, 0};
    if (modifiers & active_mods) {
        oled_write_P(active_modifier_box_bottom, false);
    } else {
        oled_write_P(inactive_modifier_box_bottom, false);
    }
}


void render_modifier_box_left(uint8_t modifiers, uint8_t active_mods) {
    static const char PROGMEM inactive_modifier_box_left[] = {
        0xb4, 0};
    static const char PROGMEM active_modifier_box_left[] = {
        0xb3, 0};
    if (modifiers & active_mods) {
        oled_write_P(active_modifier_box_left, false);
    } else {
        oled_write_P(inactive_modifier_box_left, false);
    }
}


void render_modifier_box_right(uint8_t modifiers, uint8_t active_mods) {
    static const char PROGMEM inactive_modifier_box_right[] = {
        0xb6, 0};
    static const char PROGMEM active_modifier_box_right[] = {
        0xbf, 0};
    if (modifiers & active_mods) {
        oled_write_P(active_modifier_box_right, false);
    } else {
        oled_write_P(inactive_modifier_box_right, false);
    }
}

void render_master_mod_cluster_align(void) {
    static const char PROGMEM master_cluster_align[] = {
        0xb0, 0};
    oled_write_P(master_cluster_align, false);
}

void render_slave_mod_cluster_align(void) {
    static const char PROGMEM slave_cluster_align[] = {
        0xb0,0xb0,0xb0,0xb0, 0};
    oled_write_P(slave_cluster_align, false);
}

// Master Modifier Cluster
void render_master_mod_cluster_1(void) {
    render_master_mod_cluster_align();
    render_modifier_box_top(get_mods()|get_oneshot_mods(), MOD_MASK_CTRL);
    render_modifier_box_top(get_mods()|get_oneshot_mods(), MOD_MASK_ALT);
    render_modifier_box_top(get_mods()|get_oneshot_mods(), MOD_MASK_SHIFT);
    render_modifier_box_top(get_mods()|get_oneshot_mods(), MOD_MASK_GUI);
    render_newline();
}

void render_master_mod_cluster_2(void) {
    // static const char PROGMEM mod_shift[] = {0x8b, 0x8c, 0};
    // static const char PROGMEM mod_alt[] = {0x87, 0x88, 0};
    // static const char PROGMEM mod_ctrl[] = {0x89, 0x8a, 0};
    // static const char PROGMEM mod_gui[] = {0x85, 0x86, 0};
    // static const char PROGMEM mod_win[] = {0x8d, 0x8e, 0};
    // static const char PROGMEM mod_lin[] = {0x8f, 0x90, 0};
    static const char PROGMEM mod_shift[] = {0xA9, 0xAA, 0};
    static const char PROGMEM mod_alt[] = {0xA7, 0xA8, 0};
    static const char PROGMEM mod_ctrl[] = {0xA5, 0xA6, 0};
    static const char PROGMEM mod_gui[] = {0xAD, 0xAE, 0};
    static const char PROGMEM mod_win[] = {0xAB, 0xAC, 0};
    static const char PROGMEM mod_lin[] = {0x8f, 0x90, 0};

    render_master_mod_cluster_align();

    render_modifier_box_left(get_mods()|get_oneshot_mods(), MOD_MASK_CTRL);
    oled_write_P(mod_ctrl, ((get_mods()|get_oneshot_mods()) & MOD_MASK_CTRL));
    render_modifier_box_right(get_mods()|get_oneshot_mods(), MOD_MASK_CTRL);

    render_modifier_box_left(get_mods()|get_oneshot_mods(), MOD_MASK_ALT);
    oled_write_P(mod_alt, ((get_mods()|get_oneshot_mods()) & MOD_MASK_ALT));
    render_modifier_box_right(get_mods()|get_oneshot_mods(), MOD_MASK_ALT);

    render_modifier_box_left(get_mods()|get_oneshot_mods(), MOD_MASK_SHIFT);
    oled_write_P(mod_shift, ((get_mods()|get_oneshot_mods()) & MOD_MASK_SHIFT));
    render_modifier_box_right(get_mods()|get_oneshot_mods(), MOD_MASK_SHIFT);

    render_modifier_box_left(get_mods()|get_oneshot_mods(), MOD_MASK_GUI);

    if (user_config.os == WINDOWS) {
        oled_write_P(mod_win, ((get_mods()|get_oneshot_mods()) & MOD_MASK_GUI));
    } else if (user_config.os == LINUX) {
        oled_write_P(mod_lin, ((get_mods()|get_oneshot_mods()) & MOD_MASK_GUI));
    } else {
        oled_write_P(mod_gui, ((get_mods()|get_oneshot_mods()) & MOD_MASK_GUI));
    }

    render_modifier_box_right(get_mods()|get_oneshot_mods(), MOD_MASK_GUI);

    render_newline();
}

void render_master_mod_cluster_3(void) {
    render_master_mod_cluster_align();
    render_modifier_box_bottom(get_mods()|get_oneshot_mods(), MOD_MASK_CTRL);
    render_modifier_box_bottom(get_mods()|get_oneshot_mods(), MOD_MASK_ALT);
    render_modifier_box_bottom(get_mods()|get_oneshot_mods(), MOD_MASK_SHIFT);
    render_modifier_box_bottom(get_mods()|get_oneshot_mods(), MOD_MASK_GUI);
    render_newline();
}

// Slave Modifier Cluster
void render_slave_mod_cluster_1(void) {
    render_slave_mod_cluster_align();
    render_modifier_box_top(get_mods()|get_oneshot_mods(), MOD_MASK_GUI);
    render_modifier_box_top(get_mods()|get_oneshot_mods(), MOD_MASK_SHIFT);
    render_modifier_box_top(get_mods()|get_oneshot_mods(), MOD_MASK_ALT);
    render_modifier_box_top(get_mods()|get_oneshot_mods(), MOD_MASK_CTRL);
    render_newline();
}

void render_slave_mod_cluster_2(void) {
    // static const char PROGMEM mod_shift[] = {0x8b, 0x8c, 0};
    // static const char PROGMEM mod_alt[] = {0x87, 0x88, 0};
    // static const char PROGMEM mod_ctrl[] = {0x89, 0x8a, 0};
    // static const char PROGMEM mod_gui[] = {0x85, 0x86, 0};
    // static const char PROGMEM mod_win[] = {0x8d, 0x8e, 0};
    // static const char PROGMEM mod_lin[] = {0x8f, 0x90, 0};
    static const char PROGMEM mod_shift[] = {0xA9, 0xAA, 0};
    static const char PROGMEM mod_alt[] = {0xA7, 0xA8, 0};
    static const char PROGMEM mod_ctrl[] = {0xA5, 0xA6, 0};
    static const char PROGMEM mod_gui[] = {0xAD, 0xAE, 0};
    static const char PROGMEM mod_win[] = {0xAB, 0xAC, 0};
    static const char PROGMEM mod_lin[] = {0x8f, 0x90, 0};

    render_slave_mod_cluster_align();

    render_modifier_box_left(get_mods()|get_oneshot_mods(), MOD_MASK_GUI);

    if (user_config.os == WINDOWS) {
        oled_write_P(mod_win, ((get_mods()|get_oneshot_mods()) & MOD_MASK_GUI));
    } else if (user_config.os == LINUX) {
        oled_write_P(mod_lin, ((get_mods()|get_oneshot_mods()) & MOD_MASK_GUI));
    } else {
        oled_write_P(mod_gui, ((get_mods()|get_oneshot_mods()) & MOD_MASK_GUI));
    }

    render_modifier_box_right(get_mods()|get_oneshot_mods(), MOD_MASK_GUI);

    render_modifier_box_left(get_mods()|get_oneshot_mods(), MOD_MASK_SHIFT);
    oled_write_P(mod_shift, ((get_mods()|get_oneshot_mods()) & MOD_MASK_SHIFT));
    render_modifier_box_right(get_mods()|get_oneshot_mods(), MOD_MASK_SHIFT);

    render_modifier_box_left(get_mods()|get_oneshot_mods(), MOD_MASK_ALT);
    oled_write_P(mod_alt, ((get_mods()|get_oneshot_mods()) & MOD_MASK_ALT));
    render_modifier_box_right(get_mods()|get_oneshot_mods(), MOD_MASK_ALT);

    render_modifier_box_left(get_mods()|get_oneshot_mods(), MOD_MASK_CTRL);
    oled_write_P(mod_ctrl, ((get_mods()|get_oneshot_mods()) & MOD_MASK_CTRL));
    render_modifier_box_right(get_mods()|get_oneshot_mods(), MOD_MASK_CTRL);

    render_newline();
}

void render_slave_mod_cluster_3(void) {
    render_slave_mod_cluster_align();
    render_modifier_box_bottom(get_mods()|get_oneshot_mods(), MOD_MASK_GUI);
    render_modifier_box_bottom(get_mods()|get_oneshot_mods(), MOD_MASK_SHIFT);
    render_modifier_box_bottom(get_mods()|get_oneshot_mods(), MOD_MASK_ALT);
    render_modifier_box_bottom(get_mods()|get_oneshot_mods(), MOD_MASK_CTRL);
    render_newline();
}


void render_logo1(void) {
    static const char PROGMEM mac_logo1[] = {
        0x81,0x82,0x83,0x84,0};
    static const char PROGMEM win_logo1[] = {
        0x97,0x98,0x99,0x9a,0};
    static const char PROGMEM linux_logo1[] = {
        0x9b,0x9c,0x9d,0x9e,0};
    switch (user_config.os) {
        case WINDOWS:
            oled_write_P(win_logo1, false);
            break;
        case LINUX:
            oled_write_P(linux_logo1, false);
            break;
        default:
            oled_write_P(mac_logo1, false);
            break;
    }
}

void render_logo2(void) {
    static const char PROGMEM mac_logo2[] = {
        0xa1,0xa2,0xa3,0xa4,0};
    static const char PROGMEM win_logo2[] = {
        0xb7,0xb8,0xb9,0xba,0};
    static const char PROGMEM linux_logo2[] = {
        0xbb,0xbc,0xbd,0xbe,0};
    switch (user_config.os) {
        case WINDOWS:
            oled_write_P(win_logo2, false);
            break;
        case LINUX:
            oled_write_P(linux_logo2, false);
            break;
        default:
            oled_write_P(mac_logo2, false);
            break;
    }
}

void render_master_logo3(void) {
    static const char PROGMEM mac_logo3[] = {
        0xc1,0xc2,0xc3,0xc4,0};
    static const char PROGMEM win_logo3[] = {
        0xd7,0xd8,0xd9,0xda,0};
    static const char PROGMEM linux_logo3[] = {
        0xdb,0xdc,0xdd,0xde,0};
    switch (user_config.os) {
        case WINDOWS:
            oled_write_P(win_logo3, false);
            break;
        case LINUX:
            oled_write_P(linux_logo3, false);
            break;
        default:
            oled_write_P(mac_logo3, false);
            break;
    }
}

void render_slave_logo3(void) {
    static const char PROGMEM mac_logo3[] = {
        0xc1,0xc2,0xc3,0xc4,0};
    static const char PROGMEM win_logo3[] = {
        0xd7,0xd8,0xd9,0xda,0};
    static const char PROGMEM linux_logo3[] = {
        0xdb,0xdc,0xdd,0xde,0};
    switch (user_config.os) {
        case WINDOWS:
            oled_write_P(win_logo3, false);
            break;
        case LINUX:
            oled_write_P(linux_logo3, false);
            break;
        default:
            oled_write_P(mac_logo3, false);
            break;
    }
}

void render_master_logo(void) {
    oled_write_P(PSTR("  Kyria          "), false);
    render_logo1();
    oled_write_P(PSTR("  rev3.1         "), false);
    render_logo2();
}

void render_slave_logo(void) {
    render_logo1();
    oled_write_P(PSTR("          Kyria  "), false);
    render_logo2();
    oled_write_P(PSTR("         rev3.1  "), false);
}

// KB State Box Components
void render_kb_box_top(void) {
    static const char PROGMEM inactive_kb_box_top[] = {
        0x94,0x95,0x95,0x96, 0};
    static const char PROGMEM active_kb_box_top[] = {
        0x93,0xd2,0xd2,0x9f, 0};
    if (check_state()) {
        oled_write_P(active_kb_box_top, false);
    } else {
        oled_write_P(inactive_kb_box_top, false);
    }
}

void render_kb_box_bottom(void) {
    static const char PROGMEM inactive_kb_box_bottom[] = {
        0xd4,0xd5,0xd5,0xd6, 0};
    static const char PROGMEM active_kb_box_bottom[] = {
        0xd3,0xd1,0xd1,0xdf, 0};
    if (check_state()) {
        oled_write_P(active_kb_box_bottom, false);
    } else {
        oled_write_P(inactive_kb_box_bottom, false);
    }
}

void render_kb_box_left(void) {
    static const char PROGMEM inactive_kb_box_left[] = {
        0xb4, 0};
    static const char PROGMEM active_kb_box_left[] = {
        0xb3, 0};
    if (check_state()) {
        oled_write_P(active_kb_box_left, false);
    } else {
        oled_write_P(inactive_kb_box_left, false);
    }
}

void render_kb_box_right(void) {
    static const char PROGMEM inactive_kb_box_right[] = {
        0xb6, 0};
    static const char PROGMEM active_kb_box_right[] = {
        0xbf, 0};
    if (check_state()) {
        oled_write_P(active_kb_box_right, false);
    } else {
        oled_write_P(inactive_kb_box_right, false);
    }
}

void render_kb_state_1(void) {
    render_kb_box_top();
}

void render_kb_state_2(void) {
    render_kb_box_left();
    led_t led_usb_state = host_keyboard_led_state();

    if ((led_usb_state.caps_lock) && (xcase_state == XCASE_ON)) {
        oled_write_P(PSTR("XC"), true);
    } else if (xcase_state == XCASE_ON) {
        oled_write_P(PSTR("xc"), true);
    } else if ((led_usb_state.caps_lock) && (xcase_state == XCASE_WAIT)) {
        oled_write_P(PSTR("XW"), true);
    } else if (xcase_state == XCASE_WAIT) {
        oled_write_P(PSTR("xw"), true);
    } else if (caps_word_on) {
        oled_write_P(PSTR("CW"), true);
    } else if (led_usb_state.num_lock) {
        oled_write_P(PSTR("NL"), true);
    } else if (led_usb_state.caps_lock) {
        oled_write_P(PSTR("CL"), true);
    } else if (is_leading()) {
        oled_write_P(PSTR("LD"), true);
    } else {
        oled_write_P(PSTR("  "), false);
    }
    render_kb_box_right();
}

void render_kb_state_3(void) {
    render_kb_box_bottom();
}

void render_master_layer_state(void) {
        // Host Keyboard Layer Status
    static const char PROGMEM layer_box_top[] = {
        0x80,0x94,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x96, 0};
    static const char PROGMEM layer_box_bottom[] = {
        0x80,0xd4,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd6, 0};
    static const char PROGMEM layer_box_left[] = {
        0x80,0xb4, 0};
    static const char PROGMEM layer_box_right[] = {
        0xb6, 0};
    static const char PROGMEM locked_layer_box_top[] = {
        0x80,0x93,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0x9f, 0};
    static const char PROGMEM locked_layer_box_left[] = {
        0x80,0xb3, 0};
    static const char PROGMEM locked_layer_box_right[] = {
        0xbf, 0};
    static const char PROGMEM locked_layer_box_bottom[] = {
        0x80,0xd3,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xdf, 0};
    if (is_layer_locked(get_highest_layer(layer_state))) {
        oled_write_P(locked_layer_box_top, false);
        render_kb_state_1();
        render_master_logo3();
        oled_write_P(locked_layer_box_left, false);
    } else {
        oled_write_P(layer_box_top, false);
        render_kb_state_1();
        render_master_logo3();
        oled_write_P(layer_box_left, false);
    }
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _BASE:
            oled_write_P(PSTR("COLEMAK-DH"), check_lock());
            break;
        case _COLEMAK_DH:
            oled_write_P(PSTR(" ALT BASE "), check_lock());
            break;
        case _NAVIGATION:
            oled_write_P(PSTR("NAVIGATION"), check_lock());
            break;
        case _SYMBOL:
            oled_write_P(PSTR("  SYMBOL  "), check_lock());
            break;
        case _FUNCTION:
            oled_write_P(PSTR(" FUNCTION "), check_lock());
            break;
        case _ADJUST:
            oled_write_P(PSTR("  ADJUST  "), check_lock());
            break;
        case _NUMPAD:
            oled_write_P(PSTR("  NUMPAD  "), check_lock());
            break;
        case _VIM:
            oled_write_P(PSTR("   VIM    "), check_lock());
            break;
        case _HEX:
            oled_write_P(PSTR("   HEX    "), check_lock());
            break;
        case _APPSWITCH:
            oled_write_P(PSTR(" APPSWITCH"), check_lock());
            break;
        case _GAMING:
            oled_write_P(PSTR("  GAMING  "), check_lock());
            break;
        case _GAMENUM:
            oled_write_P(PSTR(" GAMENUM  "), check_lock());
            break;
        default:
            oled_write_P(PSTR("UNDEFINED "), check_lock());
    }
    if (is_layer_locked(get_highest_layer(layer_state))) {
        oled_write_P(locked_layer_box_right, false);
        render_kb_state_2();
        render_newline();
        oled_write_P(locked_layer_box_bottom, false);
        render_kb_state_3();
        render_newline();
    } else {
        oled_write_P(layer_box_right, false);
        render_kb_state_2();
        render_newline();
        oled_write_P(layer_box_bottom, false);
        render_kb_state_3();
        render_newline();
    }
}

void render_slave_layer_state(void) {
        // Host Keyboard Layer Status
    static const char PROGMEM layer_box_top[] = {
        0x94,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x96, 0};
    static const char PROGMEM layer_box_bottom[] = {
        0xd4,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd6, 0};
    static const char PROGMEM layer_box_left[] = {
        0xb4, 0};
    static const char PROGMEM layer_box_right[] = {
        0xb6, 0};
    static const char PROGMEM locked_layer_box_top[] = {
        0x93,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0x9f, 0};
    static const char PROGMEM locked_layer_box_left[] = {
        0xb3, 0};
    static const char PROGMEM locked_layer_box_right[] = {
        0xbf, 0};
    static const char PROGMEM locked_layer_box_bottom[] = {
        0xd3,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xdf, 0};
    render_slave_logo3();
    render_kb_state_1();
    if (is_layer_locked(get_highest_layer(layer_state))) {
        oled_write_P(locked_layer_box_top, false);
        render_newline();
        oled_write_P(PSTR("    "), false);
        render_kb_state_2();
        oled_write_P(locked_layer_box_left, false);
    } else {
        oled_write_P(layer_box_top, false);
        render_newline();
        oled_write_P(PSTR("    "), false);
        render_kb_state_2();
        oled_write_P(layer_box_left, false);
    }
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _BASE:
            oled_write_P(PSTR("COLEMAK-DH"), check_lock());
            break;
        case _COLEMAK_DH:
            oled_write_P(PSTR(" ALT BASE "), check_lock());
            break;
        case _NAVIGATION:
            oled_write_P(PSTR("NAVIGATION"), check_lock());
            break;
        case _SYMBOL:
            oled_write_P(PSTR("  SYMBOL  "), check_lock());
            break;
        case _FUNCTION:
            oled_write_P(PSTR(" FUNCTION "), check_lock());
            break;
        case _ADJUST:
            oled_write_P(PSTR("  ADJUST  "), check_lock());
            break;
        case _NUMPAD:
            oled_write_P(PSTR("  NUMPAD  "), check_lock());
            break;
        case _VIM:
            oled_write_P(PSTR("   VIM    "), check_lock());
            break;
        case _HEX:
            oled_write_P(PSTR("   HEX    "), check_lock());
            break;
        case _APPSWITCH:
            oled_write_P(PSTR(" APPSWITCH"), check_lock());
            break;
        case _GAMING:
            oled_write_P(PSTR("  GAMING  "), check_lock());
            break;
        case _GAMENUM:
            oled_write_P(PSTR(" GAMENUM  "), check_lock());
            break;
        default:
            oled_write_P(PSTR("UNDEFINED "), check_lock());
    }
    if (is_layer_locked(get_highest_layer(layer_state))) {
        oled_write_P(locked_layer_box_right, false);
        render_newline();
        oled_write_P(PSTR("    "), false);
        render_kb_state_3();
        oled_write_P(locked_layer_box_bottom, false);
        render_newline();
    } else {
        oled_write_P(layer_box_right, false);
        render_newline();
        oled_write_P(PSTR("    "), false);
        render_kb_state_3();
        oled_write_P(layer_box_bottom, false);
        render_newline();
    }
}

void render_leading(void) {
    oled_write_P(PSTR("     LEADER KEYS     "), false);
    oled_write_P(PSTR("[DD]    Dynamic Macro"), false);
    oled_write_P(PSTR("[SA]     Arrange Apps"), false);
    oled_write_P(PSTR("[SS]   Scrnsht Snagit"), false);
    oled_write_P(PSTR("[SC]   Scrnsht Clipbd"), false);
    oled_write_P(PSTR("[RR]   Firmware Flash"), false);
    oled_write_P(PSTR("[EC]        @caracarn"), false);
    oled_write_P(PSTR("[ET]          @trueip"), false);
}

void render_passing(void) {
    oled_write_P(PSTR("      PASS-KEYS      "), false);
    oled_write_P(PSTR("[A]  Ad!  |  [B] LbD "), false);
    oled_write_P(PSTR("[D]  D!2  |  [I] T!P "), false);
    oled_write_P(PSTR("[J]  JbD  |  [L] L2c "), false);
    oled_write_P(PSTR("[N]  Nv_  |  [O] Pdn "), false);
    oled_write_P(PSTR("[P]  P@s  |  [Q] StQ "), false);
    oled_write_P(PSTR("[R]  IWR  |  [S] S1b "), false);
    oled_write_P(PSTR("[T]  Tit  |  [Y] Lab "), false);
}

void render_menu(void) {
    menu_items();
}

bool oled_task_user(void) {
    if (get_highest_layer(layer_state | default_layer_state) == _ADJUST) {
            render_menu();
    } else if (is_leading()) {
            render_leading();
    } else if (is_passing()) {
            render_passing();
    } else {
        if (is_keyboard_left()) {
            render_master_logo();
            render_master_layer_state();
            render_master_mod_cluster_1();
            render_master_mod_cluster_2();
            render_master_mod_cluster_3();
        } else {
            render_slave_logo();
            render_slave_layer_state();
            render_slave_mod_cluster_1();
            render_slave_mod_cluster_2();
            render_slave_mod_cluster_3();
            // render_logo_slave();
            // render_layer_state();
            // render_led_state_slave();
        }
    }
    return false;
}


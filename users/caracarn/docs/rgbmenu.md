
![alt text](rgb_menu.gif "RGB Menu")

# RGB Menu

I've always thought we could make better use of the OLED screens on our keyboards, especially given the increased
memory capacity of modern controllers. My first attempt at this was to create a visual representation of the various RGB properties
and to create a menu for adjusting those values. I have chosen to include the RGB mode, active LED flags, speed,
hue, saturation, and value via this menu system. 

I use a Kyria keyboard (<https://splitkb.com/products/kyria-rev3-pcb-kit>) and have one EC12 encoder per keyboard half. These encoders
are low profile at the cost of not having a push button function, so I use one encoder to select the menu item and the other to control 
adjustments. It would be trivial to use the push button function of a capable encoder to change menu selection, meaning all menu controls 
would be accessible by one encoder.

Below is the code I used to implement this menu. I'll link the files but my keymap is a Frankenstein's monster. I started
with very little knowledge of QMK or C and built on other users' work. Eventually I was able to write my own code, but I've never gone
back and cleaned up the mess I've made. I apologize in advance for the confusion. One of these days I'm gonna clean this place up....

## Define Menu Selection Variable

You will need a variable to keep track of the menu selection. I created an enum variable with a placeholder at the top to allow the menu
selection to wrap around more easily.

File: [rgb_matrix_keys.h](../features/rgb_matrix_keys.h)

```
typedef enum {
    RGBM_FLG,
    RGBM_MOD,
    RGBM_SPD,
    RGBM_HUE,
    RGBM_SAT,
    RGBM_VAL,
    RGBM_MAX
} rgb_menu_selector_t;

extern rgb_menu_selector_t rgb_menu_selector;
```

## Create Keys

One set of keys, RENC_MDP (RGB Encoder Mode Plus) and RENC_MDM (RGB Encoder Mode Minus) are used to change menu selection.

File: [rgb_matrix_keys.c](../features/rgb_matrix_keys.c)

```
case RENC_MDP:
    if (record->event.pressed) {
        if (user_config.rgb_menu_selector == RGBM_MAX - 1) {
            user_config.rgb_menu_selector = 0;
        } else {
            user_config.rgb_menu_selector = user_config.rgb_menu_selector + 1;
        };
        return PROCESS_RECORD_RETURN_FALSE;
    }
    break;

case RENC_MDM:
    if (record->event.pressed) {
        if (user_config.rgb_menu_selector == 0) {
            user_config.rgb_menu_selector = RGBM_MAX - 1;
        } else {
            user_config.rgb_menu_selector = user_config.rgb_menu_selector - 1;
        }
        return PROCESS_RECORD_RETURN_FALSE;
    }
    break;
```

The other set of keys, RENC_ADP and RENC_ADM (RGB Encoder Adjust Plus/Minus) handle adjustment of the selected value.

```
case RENC_ADP:
    if (record->event.pressed) {
        switch (user_config.rgb_menu_selector) {
            case RGBM_HUE:
                rgb_matrix_increase_hue();
                break;
            case RGBM_SAT:
                rgb_matrix_increase_sat();
                break;
            case RGBM_VAL:
                rgb_matrix_increase_val();
                break;
            case RGBM_SPD:
                rgb_matrix_increase_speed();
                break;
            case RGBM_MOD:
                rgb_matrix_step();
                break;
            case RGBM_FLG:
                  switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        dprintf("rgb_matrix_get_flags (KMI)= %d\n", rgb_matrix_get_flags());
                      }
                      break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        dprintf("rgb_matrix_get_flags (UG)= %d\n", rgb_matrix_get_flags());
                      }
                      break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                        dprintf("rgb_matrix_get_flags (OFF)= %d\n", rgb_matrix_get_flags());
                      }
                      break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                        dprintf("rgb_matrix_get_flags (ALL)= %d\n", rgb_matrix_get_flags());
                      }
                      break;
                  }
                break;
            default:
                break;
        }
        return PROCESS_RECORD_RETURN_FALSE;
    }
    break;

case RENC_ADM:
    if (record->event.pressed) {
        switch (user_config.rgb_menu_selector) {
            case RGBM_HUE:
                rgb_matrix_decrease_hue();
                break;
            case RGBM_SAT:
                rgb_matrix_decrease_sat();
                break;
            case RGBM_VAL:
                rgb_matrix_decrease_val();
                break;
            case RGBM_SPD:
                rgb_matrix_decrease_speed();
                break;
            case RGBM_MOD:
                rgb_matrix_step_reverse();
                break;
            case RGBM_FLG:
                  switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                        dprintf("rgb_matrix_get_flags (OFF)= %d\n", rgb_matrix_get_flags());
                      }
                      break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        dprintf("rgb_matrix_get_flags (ALL)= %d\n", rgb_matrix_get_flags());
                      }
                      break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        dprintf("rgb_matrix_get_flags (KMI)= %d\n", rgb_matrix_get_flags());
                      }
                      break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_enable_noeeprom();
                        dprintf("rgb_matrix_get_flags (UG)= %d\n", rgb_matrix_get_flags());
                      }
                      break;
                  }
                break;
            default:
                break;
        }
        return PROCESS_RECORD_RETURN_FALSE;
    }
    break;
```

I then just assigned the keys to the encoders.


```
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {

  [_ADJUST] =     { ENCODER_CCW_CW(RENC_MDM, RENC_MDP),                ENCODER_CCW_CW(RENC_ADM, RENC_ADP) },
};
```

## OLED Menu

File: [oled.c](../../../keyboards/splitkb/kyria/keymaps/coramoor/oled.c)

This is one of those things I borrowed, at least the process, so there may be a better way to display the various RGB properties.
I create a place to hold the strings for the RGB mode, speed, hue, saturation, and value numbers.
Then, inside each of the render functions, I populate the strings with their values and use the user_config.rgb_menu_selector 
variable to place the menu selection marker (>). 

```
char rgb_matrix_mode_str[8];
char rgb_matrix_speed_str[8];
char rgb_matrix_val_str[8];
char rgb_matrix_hue_str[8];
char rgb_matrix_sat_str[8];

void render_matrix_mode(void) {
    sprintf(rgb_matrix_mode_str, "%03d", rgb_matrix_get_mode());
    if (user_config.rgb_menu_selector == RGBM_MOD) {
        oled_write_P(PSTR("      >MOD: "), false);
    } else {
        oled_write_P(PSTR("       MOD: "), false);
    }
    oled_write_P(rgb_matrix_mode_str, false);
}

void render_rgb_speed(void) {
    sprintf(rgb_matrix_speed_str, "%03d", rgb_matrix_get_speed());
    if (user_config.rgb_menu_selector == RGBM_SPD) {
        oled_write_P(PSTR("      >SPD: "), false);
    } else {
        oled_write_P(PSTR("       SPD: "), false);
    }
    oled_write_P(rgb_matrix_speed_str, false);
}

void render_rgb_hue(void) {
    sprintf(rgb_matrix_hue_str, "%03d", rgb_matrix_get_hue());
    if (user_config.rgb_menu_selector == RGBM_HUE) {
        oled_write_P(PSTR("            >HUE: "), false);
    } else {
        oled_write_P(PSTR("             HUE: "), false);
    }
    oled_write_P(rgb_matrix_hue_str, false);
}

void render_rgb_sat(void) {
    sprintf(rgb_matrix_sat_str, "%03d", rgb_matrix_get_sat());
    if (user_config.rgb_menu_selector == RGBM_SAT) {
        oled_write_P(PSTR("            >SAT: "), false);
    } else {
        oled_write_P(PSTR("             SAT: "), false);
    }
    oled_write_P(rgb_matrix_sat_str, false);
}

void render_rgb_value(void) {
    sprintf(rgb_matrix_val_str, "%03d", rgb_matrix_get_val());
    if (user_config.rgb_menu_selector == RGBM_VAL) {
        oled_write_P(PSTR("            >VAL: "), false);
    } else {
        oled_write_P(PSTR("             VAL: "), false);
    }
    oled_write_P(rgb_matrix_val_str, false);
}

void render_led_flags(void) {
    if (user_config.rgb_menu_selector == RGBM_FLG) {
    oled_write_P(PSTR("      >FLG:"), false);
    } else {
    oled_write_P(PSTR("       FLG:"), false);
    }
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            oled_write_P(PSTR(" ALL"), false);
        }
        break;
        case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
            oled_write_P(PSTR(" KMI"), false);
        }
        break;
        case LED_FLAG_UNDERGLOW: {
            oled_write_P(PSTR(" UG "), false);
        }
        break;
        default: {
            oled_write_P(PSTR(" OFF"), false);
        }
        break;
    }
}

```

Finally, just call the render functions in your `oled_task_user()` function.

## Starting State 

I only display the menu on my _ADJUST layer, but I didn't want the menu selection to always start at the last selected value the last
time I was in the _ADJUST layer, so I created a custom layer change key that sets the rgb_menu_selector variable
to the first menu item when entering the _ADJUST layer so that the menu selection always starts at the top when I enter the _ADJUST layer.

File: [custom_shortcuts.c](../features/custom_shortcuts.c)

```
case ADJ_LYR:
    if (record->event.pressed) {
        user_config.rgb_menu_selector = 0;
        layer_on(_ADJUST);
        return PROCESS_RECORD_RETURN_FALSE;
    }
```

## Transport Sync

Since I have to use both encoders I wanted the menu to show up on both sides, so I had to set up a custom split transport sync 
for the menu selection state variable. For more details on custom transport sync, see the QMK Docs, <https://docs.qmk.fm/#/feature_split_keyboard?id=custom-data-sync>.
If there are any items you want to add to this menu that aren't synced by QMK by default then you'll have to set up a custom
sync for those variables as well. Otherwise you'll only see their status on the master side.

## Closing Words

I'm absolutely still a novice at programming, so it's very possible you'll see a better way to implement this menu or ways it can be 
improved. I'm all ears. Please let me know what you find, either through GitHub or by email at github@caracarn.anonaddy.com. Feel free 
to reach out with questions as well! Thanks for reading!!

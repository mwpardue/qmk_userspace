#include "caracarn_runtime.h"
#include "caracarn.h"

#ifndef PAINTER_HUE_STEP
#    define PAINTER_HUE_STEP 5
#endif // PAINTER_HUE_STEP

#ifndef PAINTER_SAT_STEP
#    define PAINTER_SAT_STEP 5
#endif // PAINTER_SAT_STEP

#ifndef PAINTER_VAL_STEP
#    define PAINTER_VAL_STEP 5
#endif // PAINTER_VAL_STEP

#ifndef PAINTER_SPD_STEP
#    define PAINTER_SPD_STEP 16
#endif // PAINTER_SPD_STEP
#include <lib/lib8tion/lib8tion.h>

dual_hsv_t painter_get_dual_hsv(void) {
    return user_config.painter.hsv;
}

void painter_sethsv_eeprom_helper(uint8_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom, bool primary) {
    hsv_t* hsv =
        primary ? &user_config.painter.hsv.primary : &user_config.painter.hsv.secondary;
    hsv->h = hue;
    hsv->s = sat;
    hsv->v = val;
    if (write_to_eeprom) {
        eeconfig_update_user_datablock_handler(&user_config, 0, EECONFIG_USER_DATA_SIZE);
    }
    dprintf("painter set %s hsv [%s]: %u,%u,%u\n", primary ? "primary" : "secondary",
            write_to_eeprom ? "EEPROM" : "NOEEPROM", hsv->h, hsv->s, hsv->v);
}

void painter_sethsv_noeeprom(uint8_t hue, uint8_t sat, uint8_t val, bool primary) {
    painter_sethsv_eeprom_helper(hue, sat, val, false, primary);
}

void painter_sethsv(uint8_t hue, uint8_t sat, uint8_t val, bool primary) {
    painter_sethsv_eeprom_helper(hue, sat, val, true, primary);
}

hsv_t painter_get_hsv(bool primary) {
    return primary ? user_config.painter.hsv.primary : user_config.painter.hsv.secondary;
}

uint8_t painter_get_hue(bool primary) {
    return primary ? user_config.painter.hsv.primary.h : user_config.painter.hsv.secondary.h;
}

uint8_t painter_get_sat(bool primary) {
    return primary ? user_config.painter.hsv.primary.s : user_config.painter.hsv.secondary.s;
}

uint8_t painter_get_val(bool primary) {
    return primary ? user_config.painter.hsv.primary.v : user_config.painter.hsv.secondary.v;
}

void painter_increase_hue_helper(bool write_to_eeprom, bool primary) {
    hsv_t* hsv =
        primary ? &user_config.painter.hsv.primary : &user_config.painter.hsv.secondary;
    painter_sethsv_eeprom_helper(qadd8(hsv->h, PAINTER_HUE_STEP), hsv->s, hsv->v, write_to_eeprom, primary);
}

void painter_increase_hue_noeeprom(bool primary) {
    painter_increase_hue_helper(false, primary);
}

void painter_increase_hue(bool primary) {
    painter_increase_hue_helper(true, primary);
}

void painter_decrease_hue_helper(bool write_to_eeprom, bool primary) {
    hsv_t* hsv =
        primary ? &user_config.painter.hsv.primary : &user_config.painter.hsv.secondary;
    painter_sethsv_eeprom_helper(qsub8(hsv->h, PAINTER_HUE_STEP), hsv->s, hsv->v, write_to_eeprom, primary);
}

void painter_decrease_hue_noeeprom(bool primary) {
    painter_decrease_hue_helper(false, primary);
}

void painter_decrease_hue(bool primary) {
    painter_decrease_hue_helper(true, primary);
}

void painter_increase_sat_helper(bool write_to_eeprom, bool primary) {
    hsv_t* hsv =
        primary ? &user_config.painter.hsv.primary : &user_config.painter.hsv.secondary;
    painter_sethsv_eeprom_helper(hsv->h, qadd8(hsv->s, PAINTER_SAT_STEP), hsv->v, write_to_eeprom, primary);
}

void painter_increase_sat_noeeprom(bool primary) {
    painter_increase_sat_helper(false, primary);
}

void painter_increase_sat(bool primary) {
    painter_increase_sat_helper(true, primary);
}

void painter_decrease_sat_helper(bool write_to_eeprom, bool primary) {
    hsv_t* hsv =
        primary ? &user_config.painter.hsv.primary : &user_config.painter.hsv.secondary;
    painter_sethsv_eeprom_helper(hsv->h, qsub8(hsv->s, PAINTER_SAT_STEP), hsv->v, write_to_eeprom, primary);
}

void painter_decrease_sat_noeeprom(bool primary) {
    painter_decrease_sat_helper(false, primary);
}

void painter_decrease_sat(bool primary) {
    painter_decrease_sat_helper(true, primary);
}

void painter_increase_val_helper(bool write_to_eeprom, bool primary) {
    hsv_t* hsv =
        primary ? &user_config.painter.hsv.primary : &user_config.painter.hsv.secondary;
    painter_sethsv_eeprom_helper(hsv->h, hsv->s, qadd8(hsv->v, PAINTER_VAL_STEP), write_to_eeprom, primary);
}

void painter_increase_val_noeeprom(bool primary) {
    painter_increase_val_helper(false, primary);
}

void painter_increase_val(bool primary) {
    painter_increase_val_helper(true, primary);
}

void painter_decrease_val_helper(bool write_to_eeprom, bool primary) {
    hsv_t* hsv =
        primary ? &user_config.painter.hsv.primary : &user_config.painter.hsv.secondary;
    painter_sethsv_eeprom_helper(hsv->h, hsv->s, qsub8(hsv->v, PAINTER_VAL_STEP), write_to_eeprom, primary);
}

void painter_decrease_val_noeeprom(bool primary) {
    painter_decrease_val_helper(false, primary);
}

void painter_decrease_val(bool primary) {
    painter_decrease_val_helper(true, primary);
}

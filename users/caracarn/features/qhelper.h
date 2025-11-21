#pragma once

dual_hsv_t painter_get_dual_hsv(void);

void painter_sethsv_eeprom_helper(uint8_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom, bool primary);
void painter_sethsv_noeeprom(uint8_t hue, uint8_t sat, uint8_t val, bool primary);
void painter_sethsv(uint8_t hue, uint8_t sat, uint8_t val, bool primary);

hsv_t painter_get_hsv(bool primary);
uint8_t painter_get_hue(bool primary);
uint8_t painter_get_sat(bool primary);
uint8_t painter_get_val(bool primary);

void painter_increase_hue_helper(bool write_to_eeprom, bool primary);
void painter_increase_hue_noeeprom(bool primary);
void painter_increase_hue(bool primary);

void painter_decrease_hue_helper(bool write_to_eeprom, bool primary);
void painter_decrease_hue_noeeprom(bool primary);
void painter_decrease_hue(bool primary);

void painter_increase_sat_helper(bool write_to_eeprom, bool primary);
void painter_increase_sat_noeeprom(bool primary);
void painter_increase_sat(bool primary);

void painter_decrease_sat_helper(bool write_to_eeprom, bool primary);
void painter_decrease_sat_noeeprom(bool primary);
void painter_decrease_sat(bool primary);

void painter_increase_val_helper(bool write_to_eeprom, bool primary);
void painter_increase_val_noeeprom(bool primary);
void painter_increase_val(bool primary);

void painter_decrease_val_helper(bool write_to_eeprom, bool primary);
void painter_decrease_val_noeeprom(bool primary);
void painter_decrease_val(bool primary);

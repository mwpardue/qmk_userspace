// You shouldn't need to edit any of this.

#pragma once

#include "keyboards/cosmos/cosmotyl/vik/config.vik.pre.h"

#define VIK_SPI_DRIVER   SPID1
#define VIK_SPI_SCK_PIN  GP14
#define VIK_SPI_MOSI_PIN GP15
#define VIK_SPI_MISO_PIN NO_PIN
#define VIK_SPI_CS       GP13
// #define VIK_I2C_DRIVER   I2CD1
// #define VIK_I2C_SDA_PIN  GP18
// #define VIK_I2C_SCL_PIN  GP19
#define VIK_GPIO_1       GP26
#define VIK_GPIO_2       GP27
#define VIK_WS2812_DI_PIN GP2

#undef DISPLAY_DC_PIN
#define DISPLAY_DC_PIN GP19

#undef     BACKLIGHT_PIN
#define BACKLIGHT_PIN GP18

#undef DISPLAY_RST_PIN
#define DISPLAY_RST_PIN GP12


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define SPLIT_USB_DETECT
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define ENCODER_RESOLUTION 4

#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#include "keyboards/cosmos/cosmotyl/vik/config.vik.post.h"

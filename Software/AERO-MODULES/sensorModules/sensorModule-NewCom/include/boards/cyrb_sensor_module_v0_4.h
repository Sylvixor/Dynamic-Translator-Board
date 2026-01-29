/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef _BOARDS_CYRB_DEV_RP2040_V1_H
#define _BOARDS_CYRB_DEV_RP2040_V1_H

// For board detection
#define CYRB_RP2040_DEV_1

// On some samples, the xosc can take longer to stabilize than is usual
#ifndef PICO_XOSC_STARTUP_DELAY_MULTIPLIER
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64
#endif

//-------- Sensor Mosfet ---------//
#ifndef MOSFET_PIN
#define MOSFET_PIN 18
#endif

//------------- UART -------------//
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
#endif

#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 0
#endif

#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 1
#endif

//------------- I2C -------------//
#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 0
#endif

#ifndef I2C_SLAVE_SDA_PIN
#define I2C_SLAVE_SDA_PIN 4
#endif

#ifndef I2C_SLAVE_SCL_PIN
#define I2C_SLAVE_SCL_PIN 5
#endif

#ifndef I2C_MASTER_SDA_PIN
#define I2C_MASTER_SDA_PIN 26
#endif

#ifndef I2C_MASTER_SCL_PIN
#define I2C_MASTER_SCL_PIN 27
#endif

//------------- SPI -------------//
#ifndef PICO_DEFAULT_SPI
#define PICO_DEFAULT_SPI 0
#endif

#ifndef PICO_DEFAULT_SPI_TX_PIN
#define PICO_DEFAULT_SPI_TX_PIN 7
#endif

#ifndef PICO_DEFAULT_SPI_RX_PIN
#define PICO_DEFAULT_SPI_RX_PIN 8
#endif

#ifndef PICO_DEFAULT_SPI_SCK_PIN
#define PICO_DEFAULT_SPI_SCK_PIN 6
#endif

#ifndef PICO_DEFAULT_SPI_CSN_PIN
#define PICO_DEFAULT_SPI_CSN_PIN 5
#endif

//-------------BUTTON------------//

#ifndef CYRB_DEV_BUTTON_1_PIN 
#define CYRB_DEV_BUTTON_1_PIN 28
#endif

//------------- LED -------------//
// No normal LED
// #define PICO_DEFAULT_LED_PIN 13

#ifndef CYRB_NEOPIXEL_STATUS_PIN
#define CYRB_NEOPIXEL_STATUS_PIN 12
#endif

// #ifndef PICO_DEFAULT_WS2812_POWER_PIN
// #define PICO_DEFAULT_WS2812_POWER_PIN 11
// #endif

//------------- FLASH -------------//

#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (8 * 1024 * 1024)
#endif

// All boards have B1 RP2040
#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 0
#endif

#endif

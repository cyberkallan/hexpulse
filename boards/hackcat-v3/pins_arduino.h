// =============================================================================
// HexPulse — HackCat V3 Pin Definitions
// Portable Intelligence Platform | HexMind AI Ecosystem
//
// NOTE: These pin assignments are estimated based on common ESP32-WROOM
// configurations for the HackCat V3 hardware. Adjust if your board differs.
// =============================================================================
#ifndef HEXPULSE_PINS_H
#define HEXPULSE_PINS_H

#include <Arduino.h>

// =============================================================================
// OLED Display — I2C (SSD1306 / SH1106, 128x64)
// =============================================================================
#ifndef OLED_SDA
#define OLED_SDA        21
#endif
#ifndef OLED_SCL
#define OLED_SCL        22
#endif
#ifndef OLED_WIDTH
#define OLED_WIDTH      128
#endif
#ifndef OLED_HEIGHT
#define OLED_HEIGHT     64
#endif
#ifndef OLED_ADDR
#define OLED_ADDR       0x3C
#endif

// =============================================================================
// Navigation Buttons — 4-button GPIO (Active LOW, internal pullup)
// =============================================================================
#ifndef BTN_UP
#define BTN_UP          32
#endif
#ifndef BTN_DOWN
#define BTN_DOWN        33
#endif
#ifndef BTN_LEFT
#define BTN_LEFT        25      // ESC / Back
#endif
#ifndef BTN_RIGHT
#define BTN_RIGHT       26      // SELECT / Enter
#endif

#ifndef BTN_ACTIVE_LOW
#define BTN_ACTIVE_LOW  1
#endif

#define BTN_PRESSED     (BTN_ACTIVE_LOW ? LOW : HIGH)
#define BTN_RELEASED    (BTN_ACTIVE_LOW ? HIGH : LOW)

// Button aliases for semantic usage
#define BTN_ESC         BTN_LEFT
#define BTN_SELECT      BTN_RIGHT
#define BTN_BACK        BTN_LEFT
#define BTN_ENTER       BTN_RIGHT

// =============================================================================
// NRF24L01 — SPI (VSPI Bus)
// =============================================================================
#ifndef NRF24_CE
#define NRF24_CE        4
#endif
#ifndef NRF24_CS
#define NRF24_CS        5
#endif
#ifndef NRF24_SCK
#define NRF24_SCK       18
#endif
#ifndef NRF24_MISO
#define NRF24_MISO      19
#endif
#ifndef NRF24_MOSI
#define NRF24_MOSI      23
#endif

// =============================================================================
// RF 433/435 MHz Module
// =============================================================================
#ifndef RF433_TX
#define RF433_TX        13
#endif
#ifndef RF433_RX
#define RF433_RX        14
#endif

// =============================================================================
// IR Transmitter / Receiver
// =============================================================================
#ifndef IR_TX_PIN
#define IR_TX_PIN       12
#endif
#ifndef IR_RX_PIN
#define IR_RX_PIN       15
#endif

// =============================================================================
// MicroSD Card — SPI (HSPI Bus)
// =============================================================================
#ifndef SD_CS
#define SD_CS           27
#endif
#ifndef SD_SCK
#define SD_SCK          14
#endif
#ifndef SD_MISO
#define SD_MISO         2
#endif
#ifndef SD_MOSI
#define SD_MOSI         15
#endif

// =============================================================================
// Battery Monitoring — ADC
// =============================================================================
#ifndef BAT_ADC_PIN
#define BAT_ADC_PIN     34      // ADC1_CH6 (input only)
#endif
#ifndef BAT_ADC_DIVIDER
#define BAT_ADC_DIVIDER 2.0     // Voltage divider ratio
#endif
#define BAT_FULL_MV     4200    // Full charge voltage (mV)
#define BAT_EMPTY_MV    3300    // Empty voltage (mV)

// =============================================================================
// Status LED
// =============================================================================
#ifndef STATUS_LED_PIN
#define STATUS_LED_PIN  2
#endif
#ifndef LED_ON
#define LED_ON          HIGH
#endif
#ifndef LED_OFF
#define LED_OFF         LOW
#endif

// =============================================================================
// Serial / USB
// =============================================================================
#define SERIAL_BAUD     115200

// =============================================================================
// Flash Configuration
// =============================================================================
#ifndef FLASH_SIZE_MB
#define FLASH_SIZE_MB   16
#endif

#endif // HEXPULSE_PINS_H

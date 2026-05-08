// =============================================================================
// HexPulse — HackCat V3 Pin Definitions
// ESP32-WROOM | 1.3" OLED | NRF24 | RF435 | IR TX/RX | SD Card
// Part of the HexMind AI Ecosystem by Arjun TM (@cyberkallan)
// =============================================================================
#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

// Board identifiers
#define HAS_4_BUTTONS
#define HACKCAT_V3

// Serial
static const uint8_t TX = 1;
static const uint8_t RX = 3;

// I2C (OLED display at 0x3C)
static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

// SPI (VSPI — shared NRF24/SD)
static const uint8_t SS   = 5;
static const uint8_t MOSI = 23;
static const uint8_t MISO = 19;
static const uint8_t SCK  = 18;

// GPIO aliases
static const uint8_t G2  = 2;
static const uint8_t G4  = 4;
static const uint8_t G5  = 5;
static const uint8_t G12 = 12;
static const uint8_t G13 = 13;
static const uint8_t G14 = 14;
static const uint8_t G15 = 15;
static const uint8_t G25 = 25;
static const uint8_t G26 = 26;
static const uint8_t G27 = 27;
static const uint8_t G32 = 32;
static const uint8_t G33 = 33;
static const uint8_t G34 = 34;

// DAC
static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

// ADC (Battery)
static const uint8_t ADC1 = 34;

// Deep sleep wakeup
#define DEEPSLEEP_WAKEUP_PIN 26  // SEL button
#define DEEPSLEEP_PIN_ACT LOW

#endif /* Pins_Arduino_h */

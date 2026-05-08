// =============================================================================
// HexPulse — HackCat V3 Interface Implementation
// 4-button navigation, battery monitoring, power management
// Part of the HexMind AI Ecosystem by Arjun TM (@cyberkallan)
// =============================================================================
#include "core/powerSave.h"
#include <interface.h>

// Button pin aliases for readability
#ifndef ESC_BTN
#define ESC_BTN 25
#endif

/***************************************************************************************
** Function name: _setup_gpio()
** Description:   Initial GPIO setup for HackCat V3
***************************************************************************************/
void _setup_gpio() {
    // Navigation buttons — internal pullup, active LOW
    pinMode(UP_BTN, INPUT_PULLUP);
    pinMode(DW_BTN, INPUT_PULLUP);
    pinMode(SEL_BTN, INPUT_PULLUP);
    pinMode(ESC_BTN, INPUT_PULLUP);

    // Status LED
#ifdef STATUS_LED
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, LOW);
#endif

    // Battery ADC
#ifdef ANALOG_BAT_PIN
    pinMode(ANALOG_BAT_PIN, INPUT);
#endif
}

/*********************************************************************
** Function: setBrightness
** OLED brightness control via contrast setting
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    // OLED doesn't have traditional backlight
    // Could use U8g2 setContrast() if integrated
    (void)brightval;
}

/*********************************************************************
** Function: InputHandler
** 4-button input: UP, DOWN, SELECT, ESC/BACK
** Handles debouncing and press detection for responsive navigation
**********************************************************************/
void InputHandler(void) {
    static unsigned long tm = 0;
    if (millis() - tm < 150 && !LongPress) return; // Debounce 150ms

    bool upPressed  = (digitalRead(UP_BTN) == LOW);
    bool dwPressed  = (digitalRead(DW_BTN) == LOW);
    bool selPressed = (digitalRead(SEL_BTN) == LOW);
    bool escPressed = (digitalRead(ESC_BTN) == LOW);

    bool anyPressed = upPressed || dwPressed || selPressed || escPressed;
    if (anyPressed) tm = millis();
    if (anyPressed && wakeUpScreen()) return;

    AnyKeyPress = anyPressed;

    // Map 4 buttons to navigation
    PrevPress = upPressed;      // UP = Previous item
    NextPress = dwPressed;      // DOWN = Next item
    SelPress  = selPressed;     // RIGHT = Select/Enter
    EscPress  = escPressed;     // LEFT = Escape/Back

    // Also set Up/Down for scrollable areas
    UpPress   = upPressed;
    DownPress = dwPressed;
}

/*********************************************************************
** Function: powerOff
** Enter deep sleep — wake on button press
**********************************************************************/
void powerOff() {
#ifdef STATUS_LED
    digitalWrite(STATUS_LED, LOW);
#endif
    esp_sleep_enable_ext0_wakeup((gpio_num_t)SEL_BTN, LOW);
    esp_deep_sleep_start();
}

/*********************************************************************
** Function: checkReboot
** Long-press detection for power off
**********************************************************************/
void checkReboot() {
    int countDown = 0;
    // Long press ESC button to power off
    if (digitalRead(ESC_BTN) == LOW) {
        uint32_t time_count = millis();
        while (digitalRead(ESC_BTN) == LOW) {
            if (millis() - time_count > 500) {
                if (countDown == 0) {
                    int textWidth = tft.textWidth("PWR OFF IN 3/3", 1);
                    tft.fillRect(60, 7, textWidth, 18, bruceConfig.bgColor);
                }
                tft.setCursor(60, 12);
                tft.setTextSize(1);
                tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
                countDown = (millis() - time_count) / 1000 + 1;
                tft.printf(" PWR OFF IN %d/3\n", countDown);
                vTaskDelay(10 / portTICK_RATE_MS);
            }
            if (countDown >= 3) {
                powerOff();
            }
        }
        // Clear text after releasing
        if (millis() - time_count > 500) {
            tft.fillRect(60, 12, 16 * LW, tft.fontHeight(1), bruceConfig.bgColor);
            drawStatusBar();
        }
        EscPress = true;
    }
}

/*********************************************************************
** Function: isCharging
** Check USB charging status (estimate from ADC voltage trend)
**********************************************************************/
bool isCharging() {
    // HackCat V3 doesn't have a dedicated charge detection pin
    // Return false — could be enhanced with voltage slope detection
    return false;
}

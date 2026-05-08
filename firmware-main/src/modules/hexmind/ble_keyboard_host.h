// =============================================================================
// HexPulse — BLE Keyboard Host Module
// Receive keystrokes from Bluetooth keyboards or Android phones
// Part of the HexMind AI Ecosystem by Arjun TM (@cyberkallan)
// =============================================================================
#ifndef __BLE_KEYBOARD_HOST_H__
#define __BLE_KEYBOARD_HOST_H__

#include <Arduino.h>
#include <NimBLEDevice.h>

// BLE HID Service/Characteristic UUIDs
#define HID_SERVICE_UUID        "1812"
#define HID_REPORT_CHAR_UUID    "2A4D"
#define BATTERY_SERVICE_UUID    "180F"

// Keyboard state
enum BLEKBState {
    BLEKB_IDLE = 0,
    BLEKB_SCANNING,
    BLEKB_CONNECTING,
    BLEKB_CONNECTED,
    BLEKB_ERROR
};

class BLEKeyboardHost {
public:
    BLEKeyboardHost();
    ~BLEKeyboardHost();

    // Lifecycle
    void begin();
    void stop();
    bool isConnected() const { return _state == BLEKB_CONNECTED; }
    BLEKBState getState() const { return _state; }

    // Scan and connect
    void startScan(uint32_t durationSec = 10);
    bool connectToDevice(NimBLEAdvertisedDevice* device);
    void disconnect();

    // Input
    bool hasInput() const { return _inputBuffer.length() > 0; }
    String getInput();           // Returns and clears the buffer
    char getChar();              // Returns next char or 0
    void clearBuffer();

    // Callback bridge (public for NimBLE callback access)
    void onNotify(NimBLERemoteCharacteristic* chr, uint8_t* data, size_t len, bool isNotify);
    void onDisconnect();

    // UI
    static void pairMenu();
    static void statusMenu();

    // Found devices during scan
    std::vector<NimBLEAdvertisedDevice*> foundDevices;

private:
    BLEKBState _state;
    NimBLEClient* _pClient;
    String _inputBuffer;
    bool _shiftPressed;
    bool _ctrlPressed;
    bool _altPressed;

    // HID keycode to ASCII mapping
    char _hidToChar(uint8_t keycode, uint8_t modifiers);
    void _parseHIDReport(uint8_t* data, size_t len);

    // Scan callback class
    class ScanCallbacks : public NimBLEScanCallbacks {
    public:
        BLEKeyboardHost* host;
        void onResult(const NimBLEAdvertisedDevice* device) override;
    };
    ScanCallbacks _scanCallbacks;
};

// Global instance
extern BLEKeyboardHost bleKeyboardHost;

#endif // __BLE_KEYBOARD_HOST_H__

// =============================================================================
// HexPulse — BLE Keyboard Host Module (Implementation)
// Receives keystrokes from BLE HID keyboards/Android phones
// Uses NimBLE for low memory footprint and high performance
// Creator: Arjun TM (@cyberkallan / @imarjunarz)
// =============================================================================
#include "ble_keyboard_host.h"
#include "core/display.h"
#include "core/utils.h"
#include <globals.h>

BLEKeyboardHost bleKeyboardHost;

// USB HID Keycode to ASCII lookup table (lowercase)
static const char HID_KEY_MAP[] = {
    0, 0, 0, 0,                                 // 0x00-0x03 (reserved)
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',    // 0x04-0x0B
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',    // 0x0C-0x13
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x',    // 0x14-0x1B
    'y', 'z',                                     // 0x1C-0x1D
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', // 0x1E-0x27
    '\n', 0x1B, '\b', '\t', ' ',                 // Enter, Esc, Backspace, Tab, Space
    '-', '=', '[', ']', '\\',                     // 0x2D-0x31
    '#', ';', '\'', '`', ',', '.', '/',           // 0x32-0x38
};

// Shift variants
static const char HID_KEY_MAP_SHIFT[] = {
    0, 0, 0, 0,
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    '\n', 0x1B, '\b', '\t', ' ',
    '_', '+', '{', '}', '|',
    '~', ':', '"', '~', '<', '>', '?',
};

// =====================================================================
// Constructor / Destructor
// =====================================================================
BLEKeyboardHost::BLEKeyboardHost()
    : _state(BLEKB_IDLE), _pClient(nullptr), _inputBuffer(""),
      _shiftPressed(false), _ctrlPressed(false), _altPressed(false) {
    _scanCallbacks.host = this;
}

BLEKeyboardHost::~BLEKeyboardHost() { stop(); }

// =====================================================================
// Lifecycle
// =====================================================================
void BLEKeyboardHost::begin() {
    if (!NimBLEDevice::isInitialized()) {
        NimBLEDevice::init("HexPulse");
    }
    _state = BLEKB_IDLE;
}

void BLEKeyboardHost::stop() {
    disconnect();
    _state = BLEKB_IDLE;
}

// =====================================================================
// Scan for BLE HID devices
// =====================================================================
void BLEKeyboardHost::startScan(uint32_t durationSec) {
    _state = BLEKB_SCANNING;
    foundDevices.clear();

    NimBLEScan *pScan = NimBLEDevice::getScan();
    pScan->setScanCallbacks(&_scanCallbacks, false);
    pScan->setActiveScan(true);
    pScan->setInterval(45);
    pScan->setWindow(15);

    displayInfo("Scanning for BLE keyboards...", true);

    pScan->start(durationSec, false);
    pScan->stop();
    _state = BLEKB_IDLE;
}

// Scan callback — filter for HID devices
void BLEKeyboardHost::ScanCallbacks::onResult(
    const NimBLEAdvertisedDevice *device) {
    // Check if device advertises HID service
    if (device->isAdvertisingService(NimBLEUUID(HID_SERVICE_UUID))) {
        Serial.printf("[BLE-KB] Found HID device: %s (%s)\n",
                      device->getName().c_str(),
                      device->getAddress().toString().c_str());
        // Store non-const copy
        host->foundDevices.push_back(
            const_cast<NimBLEAdvertisedDevice *>(device));
    }
}

// =====================================================================
// Connect to a specific BLE HID device
// =====================================================================
bool BLEKeyboardHost::connectToDevice(NimBLEAdvertisedDevice *device) {
    _state = BLEKB_CONNECTING;

    displayInfo("Connecting to: " + String(device->getName().c_str()), true);

    _pClient = NimBLEDevice::createClient();
    _pClient->setConnectTimeout(10); // 10 second timeout

    if (!_pClient->connect(device)) {
        Serial.println("[BLE-KB] Connection failed");
        _state = BLEKB_ERROR;
        NimBLEDevice::deleteClient(_pClient);
        _pClient = nullptr;
        return false;
    }

    // Find HID service
    NimBLERemoteService *pService =
        _pClient->getService(NimBLEUUID(HID_SERVICE_UUID));
    if (!pService) {
        Serial.println("[BLE-KB] HID service not found");
        _pClient->disconnect();
        NimBLEDevice::deleteClient(_pClient);
        _pClient = nullptr;
        _state = BLEKB_ERROR;
        return false;
    }

    // Find all Input Report characteristics and subscribe
    auto characteristics = pService->getCharacteristics(true);
    bool subscribed = false;

    for (auto *chr : characteristics) {
        if (chr->getUUID() == NimBLEUUID(HID_REPORT_CHAR_UUID)) {
            if (chr->canNotify()) {
                // Lambda callback for notifications
                auto notifyCb = [this](NimBLERemoteCharacteristic *pChar,
                                       uint8_t *pData, size_t length,
                                       bool isNotify) {
                    this->onNotify(pChar, pData, length, isNotify);
                };
                if (chr->subscribe(true, notifyCb)) {
                    subscribed = true;
                    Serial.println("[BLE-KB] Subscribed to HID reports");
                }
            }
        }
    }

    if (!subscribed) {
        Serial.println("[BLE-KB] No subscribable HID reports found");
        _pClient->disconnect();
        NimBLEDevice::deleteClient(_pClient);
        _pClient = nullptr;
        _state = BLEKB_ERROR;
        return false;
    }

    _state = BLEKB_CONNECTED;
    Serial.printf("[BLE-KB] Connected to: %s\n",
                  device->getName().c_str());
    return true;
}

void BLEKeyboardHost::disconnect() {
    if (_pClient && _pClient->isConnected()) {
        _pClient->disconnect();
    }
    if (_pClient) {
        NimBLEDevice::deleteClient(_pClient);
        _pClient = nullptr;
    }
    _state = BLEKB_IDLE;
}

// =====================================================================
// Notification callback — parse HID keyboard reports
// =====================================================================
void BLEKeyboardHost::onNotify(NimBLERemoteCharacteristic *chr,
                                uint8_t *data, size_t len, bool isNotify) {
    if (len >= 3) { // Minimum keyboard report: modifier + reserved + key
        _parseHIDReport(data, len);
    }
}

void BLEKeyboardHost::onDisconnect() {
    _state = BLEKB_IDLE;
    Serial.println("[BLE-KB] Device disconnected");
}

// =====================================================================
// Parse 8-byte HID keyboard report
// Format: [modifier, reserved, key1, key2, key3, key4, key5, key6]
// =====================================================================
void BLEKeyboardHost::_parseHIDReport(uint8_t *data, size_t len) {
    uint8_t modifiers = data[0];
    // data[1] is reserved

    for (size_t i = 2; i < len && i < 8; i++) {
        uint8_t keycode = data[i];
        if (keycode == 0)
            continue; // No key pressed

        char c = _hidToChar(keycode, modifiers);
        if (c != 0) {
            _inputBuffer += c;

            // Also set button presses for navigation
            if (keycode == 0x52)
                UpPress = true; // Up arrow
            else if (keycode == 0x51)
                DownPress = true; // Down arrow
            else if (keycode == 0x50)
                PrevPress = true; // Left arrow
            else if (keycode == 0x4F)
                NextPress = true; // Right arrow
            else if (keycode == 0x28)
                SelPress = true; // Enter
            else if (keycode == 0x29)
                EscPress = true; // Escape
        }
    }
}

// =====================================================================
// HID keycode to ASCII character conversion
// =====================================================================
char BLEKeyboardHost::_hidToChar(uint8_t keycode, uint8_t modifiers) {
    bool shift = (modifiers & 0x22) != 0; // Left or Right Shift

    if (keycode < sizeof(HID_KEY_MAP)) {
        return shift ? HID_KEY_MAP_SHIFT[keycode] : HID_KEY_MAP[keycode];
    }

    // Special keys
    switch (keycode) {
    case 0x28:
        return '\n'; // Enter
    case 0x29:
        return 0x1B; // Escape
    case 0x2A:
        return '\b'; // Backspace
    case 0x2B:
        return '\t'; // Tab
    case 0x2C:
        return ' '; // Space
    default:
        return 0;
    }
}

// =====================================================================
// Input buffer management
// =====================================================================
String BLEKeyboardHost::getInput() {
    String input = _inputBuffer;
    _inputBuffer = "";
    return input;
}

char BLEKeyboardHost::getChar() {
    if (_inputBuffer.length() == 0)
        return 0;
    char c = _inputBuffer[0];
    _inputBuffer = _inputBuffer.substring(1);
    return c;
}

void BLEKeyboardHost::clearBuffer() { _inputBuffer = ""; }

// =====================================================================
// Menu Entry Points
// =====================================================================
void BLEKeyboardHost::pairMenu() {
    bleKeyboardHost.begin();
    bleKeyboardHost.startScan(10);

    if (bleKeyboardHost.foundDevices.empty()) {
        displayWarning("No BLE keyboards found", true);
        delay(2000);
        return;
    }

    options = {};
    for (auto *dev : bleKeyboardHost.foundDevices) {
        String name = dev->getName().length() > 0
                          ? String(dev->getName().c_str())
                          : dev->getAddress().toString().c_str();
        options.push_back({name, [dev]() {
                                if (bleKeyboardHost.connectToDevice(dev)) {
                                    displaySuccess("Keyboard connected!", true);
                                    delay(1500);
                                } else {
                                    displayError("Connection failed", true);
                                    delay(1500);
                                }
                            }});
    }
    addOptionToMainMenu();
    loopOptions(options);
}

void BLEKeyboardHost::statusMenu() {
    options = {};

    String status;
    switch (bleKeyboardHost.getState()) {
    case BLEKB_IDLE:
        status = "Idle";
        break;
    case BLEKB_SCANNING:
        status = "Scanning...";
        break;
    case BLEKB_CONNECTING:
        status = "Connecting...";
        break;
    case BLEKB_CONNECTED:
        status = "Connected";
        break;
    case BLEKB_ERROR:
        status = "Error";
        break;
    }

    options.push_back({"Status: " + status, [=]() {}});
    options.push_back({"Pair Keyboard", [=]() { pairMenu(); }});

    if (bleKeyboardHost.isConnected()) {
        options.push_back({"Disconnect", [=]() {
                                bleKeyboardHost.disconnect();
                                displaySuccess("Disconnected", true);
                                delay(1000);
                            }});
        options.push_back({"Test Input", [=]() {
                                displayInfo("Type on keyboard...\nPress ESC to exit", true);
                                while (true) {
                                    if (bleKeyboardHost.hasInput()) {
                                        String input = bleKeyboardHost.getInput();
                                        displayInfo("Input: " + input, true);
                                    }
                                    if (check(EscPress))
                                        break;
                                    vTaskDelay(50 / portTICK_PERIOD_MS);
                                }
                            }});
    }

    addOptionToMainMenu();
    loopOptions(options);
}

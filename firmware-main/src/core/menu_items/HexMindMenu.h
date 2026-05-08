// =============================================================================
// HexPulse — HexMind Menu Item
// Main menu entry for the HexMind AI ecosystem features
// Creator: Arjun TM (@cyberkallan / @imarjunarz)
// =============================================================================
#ifndef __HEXMIND_MENU_H__
#define __HEXMIND_MENU_H__

#include <MenuItemInterface.h>
#include "modules/hexmind/hexmind_chat.h"
#include "modules/hexmind/ble_keyboard_host.h"
#include "core/scrollableTextArea.h"
#include "core/utils.h"

class HexMindMenu : public MenuItemInterface {
public:
    HexMindMenu() : MenuItemInterface("HexMind AI") {}

    void optionsMenu(void) override {
        options = {};

        options.push_back({"AI Chat", [=]() {
            HexMindChat::chatMenu();
        }});

        options.push_back({"AI Diagnostics", [=]() {
            HexMindChat::diagnosticsMenu();
        }});

        options.push_back({"BLE Keyboard", [=]() {
            BLEKeyboardHost::statusMenu();
        }});

        options.push_back({"AI Settings", [=]() {
            HexMindChat::settingsMenu();
        }});

        options.push_back({"About HexPulse", [this]() {
            this->showAboutHexPulse();
        }});

        addOptionToMainMenu();
        loopOptions(options, MENU_TYPE_SUBMENU, getName().c_str());
    }

    String getName(void) { return "HexMind AI"; }
    bool hasTheme() override { return false; }
    String themePath() override { return ""; }

    void drawIcon(float scale) override {
        // Draw HexMind AI icon — hexagonal brain
        int x = iconCenterX;
        int y = iconCenterY;

        clearIconArea();

        // Hexagon shape
        int r = 28 * scale;
        for (int i = 0; i < 6; i++) {
            float a1 = (i * 60 - 30) * PI / 180.0;
            float a2 = ((i + 1) * 60 - 30) * PI / 180.0;
            tft.drawLine(
                x + r * cos(a1), y + r * sin(a1),
                x + r * cos(a2), y + r * sin(a2),
                bruceConfig.priColor
            );
        }

        // Inner circle (brain)
        tft.drawCircle(x, y, r * 0.5, bruceConfig.priColor);

        // Neural connections
        tft.drawLine(x - r * 0.3, y - r * 0.2, x + r * 0.3, y + r * 0.2, bruceConfig.priColor);
        tft.drawLine(x + r * 0.3, y - r * 0.2, x - r * 0.3, y + r * 0.2, bruceConfig.priColor);
        tft.drawLine(x, y - r * 0.4, x, y + r * 0.4, bruceConfig.priColor);

        // Dots at intersections
        tft.fillCircle(x, y, 3, bruceConfig.priColor);
        tft.fillCircle(x - r * 0.3, y - r * 0.2, 2, bruceConfig.secColor);
        tft.fillCircle(x + r * 0.3, y - r * 0.2, 2, bruceConfig.secColor);
        tft.fillCircle(x - r * 0.3, y + r * 0.2, 2, bruceConfig.secColor);
        tft.fillCircle(x + r * 0.3, y + r * 0.2, 2, bruceConfig.secColor);
    }

private:
    void showAboutHexPulse() {
        ScrollableTextArea area = ScrollableTextArea("ABOUT HEXPULSE");

        area.addLine("HexPulse " HEXPULSE_VERSION);
        area.addLine("Codename: " HEXPULSE_CODENAME);
        area.addLine("");
        area.addLine("Portable Intelligence");
        area.addLine("Platform");
        area.addLine("");
        area.addLine("[CREATOR]");
        area.addLine(HEXPULSE_CREATOR);
        area.addLine("GitHub: " HEXPULSE_GITHUB);
        area.addLine("Instagram: " HEXPULSE_INSTA);
        area.addLine("");
        area.addLine("[ECOSYSTEM]");
        area.addLine(HEXMIND_ECOSYSTEM);
        area.addLine("Web: " HEXMIND_URL);
        area.addLine("");
        area.addLine("[HARDWARE]");
        area.addLine("HackCat V3");
        area.addLine("ESP32-WROOM | 16MB");
        area.addLine("");
        area.addLine("[LICENSE]");
        area.addLine("GPL-3.0");
        area.addLine("Based on Bruce Firmware");
        area.addLine("by pr3y & contributors");

        area.show();
    }
};

#endif // __HEXMIND_MENU_H__

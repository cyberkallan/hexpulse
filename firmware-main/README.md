# <img src="docs/assets/hexpulse-icon.svg" width="32" height="32"> HexPulse
### ⚡ Portable Intelligence Platform | HexMind AI Ecosystem

<p align="center">
  <img src="docs/assets/hexpulse-banner.png" alt="HexPulse Banner" width="600"><br><br>
  <a href="https://cyberkallan.github.io/hexpulse/"><img src="https://img.shields.io/badge/⚡_INSTALL-Web_Flasher-00FFFF?style=for-the-badge&logoColor=white" alt="Install"></a>
  <a href="https://github.com/cyberkallan/hexpulse/releases"><img src="https://img.shields.io/badge/📦_DOWNLOAD-Latest_Release-04FF00?style=for-the-badge" alt="Download"></a>
  <a href="https://hexmind.space"><img src="https://img.shields.io/badge/🧠_HEXMIND-AI_Ecosystem-FEA000?style=for-the-badge" alt="HexMind"></a>
  <br><br>
  <code>v1.0.0 "Neon Genesis"</code> · <strong>HackCat V3</strong> · ESP32 16MB · WiFi + BLE<br>
  Created by <a href="https://github.com/cyberkallan"><strong>Arjun TM</strong></a> · <a href="https://instagram.com/imarjunarz">@imarjunarz</a>
</p>

---

## 🧠 What is HexPulse?

**HexPulse** is a production-grade, modular firmware that transforms your **HackCat V3** into an AI-powered portable intelligence platform. Built on battle-tested ESP32 foundations, supercharged with cloud AI and cyberpunk aesthetics.

> *"Your HackCat is no longer just a tool — it's an intelligent companion."*

### ✨ Killer Features

| | Feature | Description |
|---|---------|-------------|
| 🤖 | **HexMind AI Chat** | Cloud AI assistant (Google Gemini / ChatGPT) directly on your OLED display |
| ⌨️ | **BLE Keyboard** | Pair your Android phone or any Bluetooth keyboard for full text input |
| 📡 | **WiFi Arsenal** | Scanner, Sniffer, Packet Monitor, Wardriving, Deauth Detector |
| 📶 | **BLE Analysis** | Device Scanner, Fingerprinting, Advertisement Parser |
| 🔌 | **NRF24 Tools** | Spectrum Analyzer, Channel Scanner, Protocol Sniffer |
| 📻 | **RF 435MHz** | Signal Capture, Protocol Decode, Signal Replay |
| 🔴 | **IR Blaster** | Remote Capture, Signal Reader, Multi-protocol Replay |
| 🌐 | **WebUI** | Full browser control panel at `http://hexpulse.local` |
| 💾 | **SD Card** | Script storage, log management, payload deployment |
| ⬆️ | **OTA Updates** | Over-the-air firmware upgrades |
| 🎮 | **JS Runtime** | On-device JavaScript scripting engine |
| 🎨 | **Neon Themes** | Cyberpunk cyan, toxic green, pulse red, hexmind gold |

---

## ⚡ Installation

### Method 1: 🌐 Web Flasher (Easiest — Recommended)

> **One-click install from your browser. No tools needed.**

1. Connect HackCat V3 to your PC via USB-C
2. Open **Chrome/Edge** browser
3. Visit → **[cyberkallan.github.io/hexpulse](https://cyberkallan.github.io/hexpulse/)**
4. Click **"Install HexPulse"**
5. Select your COM port
6. Wait for flash to complete (~2 minutes)
7. Done! Your HackCat reboots with HexPulse ⚡

### Method 2: 💾 SD Card Flash (No PC needed after download)

> **Copy files to SD card, insert into HackCat, and flash from the device itself.**

1. Download the latest release from [Releases](https://github.com/cyberkallan/hexpulse/releases)
2. Extract the ZIP file
3. Copy `firmware.bin` to your MicroSD card root folder
4. Insert the SD card into your HackCat V3
5. Power on the device
6. Navigate to **Config → OTA Update → SD Card Update**
7. Select `firmware.bin` and confirm
8. Device will flash and reboot with HexPulse!

> [!TIP]
> SD Card must be **FAT32** formatted, max **32GB**

### Method 3: 🔧 esptool.py (Command Line)

```bash
# Install esptool
pip install esptool

# Flash (replace COM5 with your port)
esptool.py --chip esp32 --port COM5 --baud 921600 \
  write_flash -z \
  0x1000 bootloader.bin \
  0x8000 partitions.bin \
  0x10000 firmware.bin
```

> [!NOTE]
> On **Linux/Mac**, your port will be `/dev/ttyUSB0` or `/dev/ttyACM0`

### Method 4: 🛠️ PlatformIO (For Developers)

```bash
git clone https://github.com/cyberkallan/hexpulse
cd hexpulse/firmware-main
pio run -e hackcat-v3 -t upload
```

---

## 🤖 HexMind AI Setup

<table>
<tr><td width="50%">

### Quick Start
1. Flash HexPulse to your HackCat V3
2. Connect to WiFi → **WiFi → Connect**
3. Open **HexMind AI → AI Settings**
4. Select provider (Gemini = free)
5. Enter API key
6. Go to **HexMind AI → AI Chat**
7. Start asking questions! 🧠

</td><td width="50%">

### Get Your API Key
| Provider | Free Tier | Link |
|----------|-----------|------|
| **Google Gemini** ⭐ | 15 RPM free | [aistudio.google.com](https://aistudio.google.com) |
| **OpenAI** | Pay-per-use | [platform.openai.com](https://platform.openai.com) |
| **Custom** | Self-hosted | Any OpenAI-compatible endpoint |

</td></tr>
</table>

### What Can HexMind Do?
- 💬 **Chat** — Ask about protocols, vulnerabilities, networking concepts
- 📡 **WiFi Analysis** — Auto-analyze scan results for security issues
- 📶 **BLE Analysis** — Identify IoT devices and their security posture
- 📋 **Reports** — Generate comprehensive security diagnostic reports
- 💾 **Export** — Save conversations and reports to SD card

---

## ⌨️ BLE Keyboard Setup

Use your **Android phone** or any **Bluetooth keyboard** as a full QWERTY input device:

1. Go to **HexMind AI → BLE Keyboard → Pair Keyboard**
2. **For BT Keyboard**: Put it in pairing mode
3. **For Android**: Install any "BLE Keyboard" app from Play Store
4. Select your device from the scan results
5. Once connected, type anywhere in HexPulse!

> [!TIP]
> Arrow keys on the BT keyboard work as navigation (Up/Down/Left/Right)  
> Enter = Select, Escape = Back

---

## 📱 Hardware — HackCat V3

<table>
<tr>
<td width="50%">

| Component | Detail |
|-----------|--------|
| **MCU** | ESP32-WROOM (240MHz dual-core) |
| **Flash** | 16MB |
| **RAM** | 520KB SRAM |
| **Display** | 1.3" OLED 128×64 (I2C) |
| **Input** | 4 tactile push buttons |
| **Battery** | 800mAh LiPo |
| **Charging** | USB-C |

</td>
<td width="50%">

| Module | Detail |
|--------|--------|
| **WiFi** | 2.4GHz 802.11 b/g/n |
| **Bluetooth** | BLE 4.2 + Classic |
| **NRF24** | NRF24L01 2.4GHz |
| **RF** | 435MHz TX/RX |
| **IR** | TX + RX |
| **Storage** | MicroSD (up to 32GB) |
| **GPIO** | Expansion pins |

</td>
</tr>
</table>

**Buy HackCat V3**: [store.hackgears.in](https://store.hackgears.in/product/hack_cat-v3/)

---

## 🎨 Themes

HexPulse ships with exclusive cyberpunk themes:

| Theme | Primary | Secondary | Vibe |
|-------|---------|-----------|------|
| **Neon Cyan** ⭐ | `#00FFFF` | `#00BFFF` | HexPulse signature |
| **Toxic Green** | `#00FF00` | `#00BF00` | Matrix / Terminal |
| **Pulse Red** | `#FF0000` | `#BF0000` | Alert mode |
| **HexMind Gold** | `#FFD400` | `#BFA400` | AI mode |
| + 15 more from Bruce | Various | Various | Classic |

---

## 📁 Project Structure

```
firmware-main/
├── boards/hackcat-v3/          # ★ HackCat V3 board profile
│   ├── hackcat-v3.ini          #   Build configuration
│   ├── interface.cpp           #   Button/power handlers
│   └── pins_arduino.h          #   GPIO pin map
├── src/
│   ├── main.cpp                # Boot screen + main loop
│   ├── core/
│   │   ├── config.h            # System configuration
│   │   ├── display.cpp         # UI rendering
│   │   ├── theme.h             # Color system
│   │   ├── main_menu.h/cpp     # Menu system
│   │   └── menu_items/
│   │       └── HexMindMenu.h   # ★ HexMind AI menu
│   └── modules/
│       └── hexmind/            # ★ HexPulse exclusive modules
│           ├── hexmind_chat.h/cpp        # AI Chat (Gemini/ChatGPT)
│           └── ble_keyboard_host.h/cpp   # BLE Keyboard Host
├── flash/                      # Web flasher files
│   ├── index.html              # Flasher webpage
│   └── manifest.json           # ESP Web Tools manifest
├── docs/                       # Documentation
└── platformio.ini              # Build system
```

---

## 🔧 Building from Source

### Prerequisites
- [PlatformIO](https://platformio.org/install) (CLI or VSCode extension)
- USB-C cable
- HackCat V3 device

### Build & Flash
```bash
# Clone
git clone https://github.com/cyberkallan/hexpulse
cd hexpulse/firmware-main

# Build
pio run -e hackcat-v3

# Build + Flash
pio run -e hackcat-v3 -t upload

# Monitor serial output
pio device monitor -b 115200
```

### Build Output
The firmware binary will be at:
```
.pio/build/hackcat-v3/firmware.bin
```

---

## 📜 Credits

<table>
<tr>
<td align="center" width="200">
<strong>Arjun TM</strong><br>
Creator & Developer<br>
<a href="https://github.com/cyberkallan">@cyberkallan</a><br>
<a href="https://instagram.com/imarjunarz">@imarjunarz</a><br>
<a href="https://hexmind.space">hexmind.space</a>
</td>
<td align="center" width="200">
<strong>Bruce Firmware</strong><br>
Base Firmware<br>
<a href="https://github.com/pr3y/Bruce">pr3y/Bruce</a><br>
GPL-3.0 License
</td>
<td align="center" width="200">
<strong>Hack Gears</strong><br>
Hardware Platform<br>
<a href="https://hackgears.in">hackgears.in</a><br>
HackCat V3
</td>
</tr>
</table>

---

## ⚖️ License

**GPL-3.0** — Free to use, modify, and distribute. Must keep open source.

Based on [Bruce Firmware](https://github.com/pr3y/Bruce) with full attribution.

---

## ⚠️ Disclaimer

HexPulse is designed for **authorized security testing and educational purposes only**. Always obtain proper written authorization before testing any network, system, or device you do not own. The creator assumes no responsibility for misuse.

---

<p align="center">
  <strong>HexPulse v1.0.0 "Neon Genesis"</strong><br>
  Built with ⚡ by <a href="https://github.com/cyberkallan">Arjun TM</a><br>
  <em>HexMind AI Ecosystem</em> · <em>@cyberkallan</em> · <em>@imarjunarz</em><br><br>
  <a href="https://cyberkallan.github.io/hexpulse/"><img src="https://img.shields.io/badge/⚡_FLASH_NOW-00FFFF?style=for-the-badge" alt="Flash Now"></a>
</p>

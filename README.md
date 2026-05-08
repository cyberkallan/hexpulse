<![CDATA[<div align="center">

<!-- Animated Header -->
<img src="https://capsule-render.vercel.app/api?type=waving&color=0:000000,50:001a1a,100:00FFFF&height=200&section=header&text=⚡%20HEXPULSE&fontSize=70&fontColor=00FFFF&fontAlignY=35&desc=AI-Powered%20Pentesting%20Ecosystem&descSize=20&descAlignY=55&descColor=ffffff&animation=fadeIn" width="100%"/>

<!-- Dynamic Badges -->
<p>
  <a href="https://cyberkallan.github.io/hexpulse/web-flasher-dist/">
    <img src="https://img.shields.io/badge/⚡_FLASH_NOW-Web_Installer-00FFFF?style=for-the-badge&logoColor=white&labelColor=0a0a0f" alt="Flash Now">
  </a>
  <a href="https://github.com/cyberkallan/hexpulse/releases">
    <img src="https://img.shields.io/badge/📦_DOWNLOAD-Latest_Release-04FF00?style=for-the-badge&labelColor=0a0a0f" alt="Download">
  </a>
  <a href="https://hexmind.space">
    <img src="https://img.shields.io/badge/🧠_HEXMIND-AI_Cloud-FFD400?style=for-the-badge&labelColor=0a0a0f" alt="HexMind">
  </a>
</p>

<p>
  <img src="https://img.shields.io/github/stars/cyberkallan/hexpulse?style=social" alt="Stars">
  <img src="https://img.shields.io/github/forks/cyberkallan/hexpulse?style=social" alt="Forks">
  <img src="https://img.shields.io/github/license/cyberkallan/hexpulse?color=00FFFF&labelColor=0a0a0f" alt="License">
  <img src="https://img.shields.io/badge/version-1.0.0-00FFFF?labelColor=0a0a0f" alt="Version">
  <img src="https://img.shields.io/badge/platform-ESP32-blue?labelColor=0a0a0f" alt="Platform">
</p>

<p>
  <code>v1.0.0 "Neon Genesis"</code> · <strong>ESP32 16MB</strong> · WiFi + BLE + NRF24 + RF + IR<br>
  Created by <a href="https://github.com/cyberkallan"><strong>Arjun TM</strong></a> · <a href="https://instagram.com/imarjunarz">@imarjunarz</a>
</p>

<br>

<!-- Call to Action -->
<a href="https://cyberkallan.github.io/hexpulse/web-flasher-dist/">
  <img src="https://img.shields.io/badge/🚀_DEPLOY_HEXPULSE_FROM_YOUR_BROWSER-Click_Here-00FFFF?style=for-the-badge&logoColor=black&labelColor=0a0a0f&color=00FFFF" alt="Deploy HexPulse" width="500">
</a>

</div>

---

## 🧠 What is HexPulse?

**HexPulse** is a production-grade, modular firmware that transforms your **ESP device** into an **AI-powered portable intelligence platform**. Built on battle-tested ESP32 foundations, supercharged with cloud AI and cyberpunk aesthetics.

> *"Your device is no longer just a tool — it's an intelligent companion."*

<div align="center">
<table>
<tr>
<td align="center" width="140">

🤖<br><strong>HexMind AI</strong><br><sub>Cloud AI Chat</sub>

</td>
<td align="center" width="140">

⌨️<br><strong>BLE Keyboard</strong><br><sub>Phone Input</sub>

</td>
<td align="center" width="140">

📡<br><strong>WiFi Arsenal</strong><br><sub>Full Pentesting</sub>

</td>
<td align="center" width="140">

📶<br><strong>BLE Scanner</strong><br><sub>Device Analysis</sub>

</td>
<td align="center" width="140">

🔌<br><strong>NRF24</strong><br><sub>2.4GHz Tools</sub>

</td>
</tr>
<tr>
<td align="center">

📻<br><strong>RF 435MHz</strong><br><sub>Signal Replay</sub>

</td>
<td align="center">

🔴<br><strong>IR Blaster</strong><br><sub>Remote Clone</sub>

</td>
<td align="center">

🌐<br><strong>WebUI</strong><br><sub>Browser Panel</sub>

</td>
<td align="center">

🎮<br><strong>JS Runtime</strong><br><sub>Scripting Engine</sub>

</td>
<td align="center">

⬆️<br><strong>OTA Update</strong><br><sub>Wireless Flash</sub>

</td>
</tr>
</table>
</div>

---

## ⚡ Quick Install — Web Flasher

> **The easiest way. Flash directly from your browser in under 2 minutes.**

<div align="center">

### 👉 [cyberkallan.github.io/hexpulse/web-flasher-dist](https://cyberkallan.github.io/hexpulse/web-flasher-dist/) 👈

</div>

| Step | Action |
|:----:|--------|
| **1** | Connect your ESP device to your PC via **USB-C data cable** |
| **2** | Open **[Web Flasher](https://cyberkallan.github.io/hexpulse/web-flasher-dist/)** in **Chrome** or **Edge** |
| **3** | Click **"⚡ DEPLOY HEXPULSE"** |
| **4** | Select your **COM port** from the browser popup |
| **5** | Wait ~2 minutes for the flash to complete |
| **6** | Device reboots into HexPulse! 🎉 |

> [!TIP]
> **No drivers, no tools, no terminal commands.** Just a browser and a USB cable.

> [!IMPORTANT]
> **Browser Requirement:** Web Serial API is only supported on **Chrome**, **Edge**, and **Opera**. Safari and Firefox will not work.

---

## 💾 Alternative Install Methods

<details>
<summary><strong>📂 Method 2: SD Card Flash (No PC needed after download)</strong></summary>

<br>

1. Download the latest firmware ZIP from [**Releases**](https://github.com/cyberkallan/hexpulse/releases)
2. Extract — you'll get `firmware.bin`
3. Format your MicroSD card as **FAT32** (max 32GB)
4. Copy `firmware.bin` to the **root** of the SD card
5. Insert the SD card into your ESP device
6. Power on → Navigate to `Config → OTA Update → SD Card Update`
7. Select `firmware.bin` and confirm
8. Device reboots with HexPulse! 🎉

</details>

<details>
<summary><strong>🔧 Method 3: esptool.py (Command Line)</strong></summary>

<br>

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

> **Linux/Mac:** Use `/dev/ttyUSB0` or `/dev/ttyACM0` instead of `COM5`

> **Connection Error?** Hold the **BOOT** button while plugging in the USB cable

</details>

<details>
<summary><strong>🛠️ Method 4: PlatformIO (Developer Build)</strong></summary>

<br>

```bash
git clone https://github.com/cyberkallan/hexpulse
cd hexpulse/firmware-main
pio run -e hackcat-v3 -t upload
```

Build output: `.pio/build/hackcat-v3/firmware.bin`

</details>

---

## 🤖 HexMind AI Setup

HexPulse integrates a cloud-based AI assistant powered by **Google Gemini** or **ChatGPT/OpenAI**, accessible directly on your device's OLED screen.

<table>
<tr><td width="50%">

### 🚀 Quick Start
1. Flash HexPulse to your ESP device
2. Connect to WiFi → `WiFi → Connect`
3. Open `HexMind AI → AI Settings`
4. Select your provider (**Gemini** = free tier)
5. Enter your API key
6. Go to `HexMind AI → AI Chat`
7. Start asking questions! 🧠

</td><td width="50%">

### 🔑 Get Your API Key

| Provider | Free Tier | Link |
|----------|-----------|------|
| **Google Gemini** ⭐ | 15 RPM free | [aistudio.google.com](https://aistudio.google.com) |
| **OpenAI** | Pay-per-use | [platform.openai.com](https://platform.openai.com) |
| **Custom** | Self-hosted | Any OpenAI-compatible endpoint |

</td></tr>
</table>

### What Can HexMind Do?

| Capability | Description |
|------------|-------------|
| 💬 **Chat** | Ask about protocols, vulnerabilities, networking concepts |
| 📡 **WiFi Analysis** | Auto-analyze scan results for security issues |
| 📶 **BLE Analysis** | Identify IoT devices and their security posture |
| 📋 **Reports** | Generate comprehensive security diagnostic reports |
| 💾 **Export** | Save conversations and reports to SD card |

> [!NOTE]
> **Security:** API keys are stored locally on your device's EEPROM. They are never transmitted anywhere except directly to the AI provider's API endpoint over HTTPS.

---

## ⌨️ BLE Keyboard Setup

Use your **Android phone** or any **Bluetooth keyboard** as a full QWERTY input device:

1. Go to `HexMind AI → BLE Keyboard → Pair Keyboard`
2. **For BT Keyboard:** Put it in pairing mode
3. **For Android:** Install any "BLE Keyboard" app from Play Store
4. Select your device from the scan results
5. Once connected, type anywhere in HexPulse!

> [!TIP]
> Arrow keys = Navigation (Up/Down/Left/Right) · Enter = Select · Escape = Back

---

## 📱 Hardware Specifications

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

---

## 🎨 Themes

HexPulse ships with exclusive cyberpunk themes:

| Theme | Color | Vibe |
|-------|-------|------|
| **Neon Cyan** ⭐ | `#00FFFF` | HexPulse signature |
| **Toxic Green** | `#00FF00` | Matrix / Terminal |
| **Pulse Red** | `#FF0000` | Alert mode |
| **HexMind Gold** | `#FFD400` | AI mode |
| + 15 more built-in | Various | Classic collection |

---

## 📁 Project Structure

```
hexpulse/
├── boards/                         # Board JSON definitions
├── firmware-main/                  # ★ Full firmware source
│   ├── boards/                     #   Board-specific configs
│   │   └── hackcat-v3/             #   ESP device profile
│   ├── src/
│   │   ├── main.cpp                #   Boot + main loop
│   │   ├── core/                   #   UI, menus, themes, config
│   │   └── modules/
│   │       ├── hexmind/            #   ★ HexMind AI + BLE Keyboard
│   │       ├── wifi/               #   WiFi pentesting suite
│   │       ├── ble/                #   BLE analysis tools
│   │       ├── rf/                 #   RF 435MHz tools
│   │       ├── ir/                 #   IR blaster
│   │       └── others/             #   NRF24, GPS, BadUSB, etc.
│   ├── flash/                      #   Web flasher (index.html)
│   └── docs/                       #   Documentation
├── web-flasher-dist/               # ★ Ready-to-host flasher page
│   ├── index.html                  #   Premium flasher UI
│   └── manifest.json               #   ESP Web Tools config
├── scripts/                        # Build scripts
└── platformio.ini                  # PlatformIO config
```

---

## 🔧 Building from Source

### Prerequisites
- [PlatformIO](https://platformio.org/install) (CLI or VSCode extension)
- USB-C data cable
- ESP32-based device

### Build & Flash

```bash
# Clone the repo
git clone https://github.com/cyberkallan/hexpulse
cd hexpulse/firmware-main

# Build only
pio run -e hackcat-v3

# Build + Flash
pio run -e hackcat-v3 -t upload

# Monitor serial output
pio device monitor -b 115200
```

### Build Output
```
.pio/build/hackcat-v3/firmware.bin       ← main firmware
.pio/build/hackcat-v3/bootloader.bin     ← bootloader
.pio/build/hackcat-v3/partitions.bin     ← partition table
```

---

## 🔒 Security

HexPulse is built with security-first principles:

| Aspect | Implementation |
|--------|---------------|
| **API Key Storage** | Stored locally on device EEPROM only — never in source code |
| **HTTPS Only** | All cloud AI communication uses TLS/HTTPS |
| **No Telemetry** | Zero data collection, zero phone-home |
| **Open Source** | Full source code is auditable by anyone |
| **OTA Auth** | OTA updates require authentication password |
| **Web Flasher** | Runs entirely client-side — no server-side code |

> [!CAUTION]
> **Legal Disclaimer:** HexPulse is designed for **authorized security testing and educational purposes only**. Always obtain proper written authorization before testing any network, system, or device you do not own. The creator assumes no responsibility for misuse.

---

## 📜 Credits

<table>
<tr>
<td align="center" width="220">
<strong>Arjun TM</strong><br>
Creator & Lead Developer<br>
<a href="https://github.com/cyberkallan">@cyberkallan</a><br>
<a href="https://instagram.com/imarjunarz">@imarjunarz</a><br>
<a href="https://hexmind.space">hexmind.space</a>
</td>
<td align="center" width="220">
<strong>Bruce Firmware</strong><br>
Base ESP32 Framework<br>
<a href="https://github.com/pr3y/Bruce">pr3y/Bruce</a><br>
GPL-3.0 License
</td>
<td align="center" width="220">
<strong>HexMind AI</strong><br>
Cloud Intelligence Layer<br>
<a href="https://hexmind.space">hexmind.space</a><br>
Gemini + OpenAI
</td>
</tr>
</table>

---

## ⚖️ License

**GPL-3.0** — Free to use, modify, and distribute. Must keep open source.

Based on [Bruce Firmware](https://github.com/pr3y/Bruce) with full attribution maintained.

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:000000,50:001a1a,100:00FFFF&height=120&section=footer" width="100%"/>

<strong>HexPulse v1.0.0 "Neon Genesis"</strong><br>
Built with ⚡ by <a href="https://github.com/cyberkallan">Arjun TM</a><br>
<em>HexMind AI Ecosystem</em> · <em>@cyberkallan</em> · <em>@imarjunarz</em><br><br>
<a href="https://cyberkallan.github.io/hexpulse/web-flasher-dist/">
  <img src="https://img.shields.io/badge/⚡_FLASH_NOW-00FFFF?style=for-the-badge&labelColor=0a0a0f" alt="Flash Now">
</a>
<a href="https://github.com/cyberkallan/hexpulse">
  <img src="https://img.shields.io/badge/⭐_STAR_THIS_REPO-FFD400?style=for-the-badge&labelColor=0a0a0f" alt="Star">
</a>

</div>
]]>

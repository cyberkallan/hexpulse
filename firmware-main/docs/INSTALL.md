# HexPulse Installation Guide

> Complete guide for flashing HexPulse firmware onto your HackCat V3

---

## Prerequisites

| Item | Required |
|------|----------|
| **HackCat V3** | The device itself |
| **USB-C cable** | Data-capable (not charge-only) |
| **Chrome/Edge browser** | For web flasher method |
| **MicroSD card** | FAT32, max 32GB (for SD method) |
| **PC** | Windows, Mac, or Linux |

---

## Method 1: 🌐 Web Flasher (Auto Flash)

**Easiest method — works directly in your browser.**

### Step-by-Step

1. **Connect** your HackCat V3 to your PC via USB-C cable

2. **Open** Chrome or Edge browser

3. **Navigate** to: `https://cyberkallan.github.io/hexpulse/`

4. **Click** the "⚡ INSTALL HEXPULSE" button

5. **Select** your COM port from the popup:
   - Windows: `COM3`, `COM4`, `COM5` etc.
   - Mac: `/dev/cu.usbserial-xxxx`
   - Linux: `/dev/ttyUSB0` or `/dev/ttyACM0`

6. **Wait** for the flash process to complete (~2 minutes)
   - Progress bar will show upload status
   - DO NOT disconnect during flashing!

7. **Done!** Device reboots automatically with HexPulse

### Troubleshooting

| Problem | Solution |
|---------|----------|
| No COM port shown | Install [CP2102 drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) |
| "Failed to connect" | Hold BOOT button while clicking Install |
| Browser not supported | Use Chrome or Edge (Firefox/Safari don't support Web Serial) |
| Flash stuck | Disconnect USB, reconnect while holding BOOT, retry |

---

## Method 2: 💾 SD Card Flash (Manual)

**Flash from the device itself — no PC needed after downloading!**

### Step-by-Step

1. **Download** the latest release:
   - Go to: `https://github.com/cyberkallan/hexpulse/releases`
   - Download: `hexpulse-v1.0.0-hackcat-v3.zip`

2. **Extract** the ZIP file on your PC
   - You'll get: `firmware.bin` (~2-3 MB)

3. **Prepare SD card**:
   - Format as **FAT32** (use Windows format tool or SD Card Formatter)
   - Card must be **32GB or smaller**

4. **Copy** `firmware.bin` to the **root** of the SD card
   ```
   SD Card Root/
   └── firmware.bin    ← place here
   ```

5. **Eject** SD card safely from your PC

6. **Insert** the MicroSD card into your HackCat V3

7. **Power on** the device (if it has existing firmware)

8. **Navigate** the menu:
   ```
   Config → OTA Update → SD Card Update
   ```

9. **Select** `firmware.bin` from the file list

10. **Confirm** the flash — press the Select button

11. **Wait** for the progress bar to reach 100%

12. **Done!** Device reboots with HexPulse ⚡

### First-Time Flash (No Existing Firmware)

If your HackCat V3 has no firmware or is bricked:

1. You'll need to use the **Web Flasher** or **esptool.py** method instead
2. SD card update requires a working firmware to be already running
3. After the first flash via USB, future updates can use SD card

---

## Method 3: 🔧 esptool.py (Command Line)

**For advanced users who prefer the terminal.**

### Install esptool

```bash
pip install esptool
```

### Download Firmware Files

Download from [Releases](https://github.com/cyberkallan/hexpulse/releases):
- `bootloader.bin`
- `partitions.bin`
- `firmware.bin`

### Flash Command

**Windows:**
```bash
esptool.py --chip esp32 --port COM5 --baud 921600 write_flash -z 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin
```

**Linux:**
```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600 write_flash -z 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin
```

**Mac:**
```bash
esptool.py --chip esp32 --port /dev/cu.usbserial-0001 --baud 921600 write_flash -z 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin
```

### Full Erase + Flash (Clean Install)

```bash
# Erase everything first
esptool.py --chip esp32 --port COM5 erase_flash

# Then flash
esptool.py --chip esp32 --port COM5 --baud 921600 write_flash -z 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin
```

---

## Method 4: 🛠️ PlatformIO (Build from Source)

**For developers who want to modify the firmware.**

### Prerequisites
- [PlatformIO CLI](https://platformio.org/install/cli) or [VSCode Extension](https://platformio.org/install/ide?install=vscode)
- Git

### Build & Flash

```bash
# Clone the repo
git clone https://github.com/cyberkallan/hexpulse
cd hexpulse/firmware-main

# Build only
pio run -e hackcat-v3

# Build + Flash via USB
pio run -e hackcat-v3 -t upload

# Monitor serial output
pio device monitor -b 115200
```

### Build Output Location
```
.pio/build/hackcat-v3/firmware.bin      ← main firmware
.pio/build/hackcat-v3/bootloader.bin    ← bootloader
.pio/build/hackcat-v3/partitions.bin    ← partition table
```

---

## Post-Installation

After flashing, your HackCat V3 will boot into HexPulse:

1. **Boot screen**: "HexPulse v1.0.0" with neon cyan branding
2. **Main menu**: Navigate with 4 buttons (UP/DOWN/SELECT/BACK)
3. **First thing to do**: Connect to WiFi
   - Navigate to **WiFi → Connect**
   - Select your network and enter password

### Setup HexMind AI
1. Go to **HexMind AI → AI Settings**
2. Select your AI provider (Google Gemini recommended — free)
3. Enter your API key
4. Start chatting in **HexMind AI → AI Chat**

### Access WebUI
1. Connect to WiFi (same network as your PC)
2. Open browser: `http://hexpulse.local`
3. Login: `admin` / `hexpulse`

---

## OTA Update (Future Updates)

Once HexPulse is installed, future updates can be done wirelessly:

### Via WebUI
1. Connect to WiFi
2. Open `http://hexpulse.local`
3. Go to **Settings → OTA Update**
4. Upload the new `firmware.bin`

### Via SD Card
1. Copy new `firmware.bin` to SD card
2. **Config → OTA Update → SD Card Update**
3. Select the file and confirm

---

## FAQ

**Q: Will this brick my HackCat V3?**
A: No. If something goes wrong, you can always re-flash using esptool.py with the `erase_flash` command followed by a fresh flash.

**Q: Can I go back to original firmware?**
A: Yes. Flash the original HackCat firmware using the same methods described above.

**Q: Do I need an internet connection for AI chat?**
A: Yes. The AI runs in the cloud (Google/OpenAI servers). Your HackCat connects via WiFi to send queries.

**Q: Is the API key stored securely?**
A: The API key is stored in the device's internal flash (LittleFS). It's not transmitted anywhere except to the configured AI provider.

**Q: What SD card should I use?**
A: Any MicroSD card up to 32GB, formatted as FAT32. Class 10 or higher recommended.

---

<p align="center">
<strong>HexPulse v1.0.0</strong> · Created by Arjun TM · <a href="https://github.com/cyberkallan">@cyberkallan</a>
</p>

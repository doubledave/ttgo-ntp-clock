
# TTGO ESP32 T-Display Project

## Overview
This repository contains the code for a project using the TTGO ESP32 T-Display. This project includes functionality for displaying the local time, managing WiFi connections, and handling user input through buttons.

## Features
- Display the current local time on the TTGO ESP32 T-Display.
- Connect to a WiFi network and fetch the current time from an NTP server.
- Display battery voltage.
- Screen timeout management with adjustable settings.
- Button interactions for resetting screen timeout.

## Hardware Requirements
- TTGO ESP32 T-Display module.
- USB cable for programming and power supply.

## Software Requirements
- Arduino IDE
- Required Libraries:
  - TFT_eSPI (from Bodmer)
  - Button2
  - WiFi
  - SPI
  - time

## Setup and Installation

### Arduino IDE Configuration
1. Add the ESP32 board manager URL in Arduino IDE under `File > Preferences`.
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
2. Install the ESP32 board from `Tools > Board > Boards Manager`.
3. Select `ESP32 Dev Module` under `Tools > Board`.
4. Choose the correct COM port for your device.

### Library Installation
1. Install `TFT_eSPI` library using the Library Manager in the Arduino IDE.
2. Update the `TFT_eSPI` library with the specific version for TTGO ESP32 T-Display from the GitHub repository.
   ```
   https://github.com/Xinyuan-LilyGO/TTGO-T-Display
   ```
3. Replace the existing `TFT_eSPI` directory in your Arduino libraries folder with the downloaded version.

## Usage
Upload the provided code to your TTGO ESP32 T-Display. Once running, the device will display the current time, connect to WiFi, and update the time via NTP.

## Customization
- WiFi credentials and NTP server settings can be adjusted in the code.
- Screen timeout duration can be changed by modifying the `SCREEN_TIMEOUT` constant.

## Contributing
Contributions to this project are welcome. Please ensure to follow best practices for coding and documentation.

## License
[MIT](https://mit-license.org/)

## Acknowledgements
- Thanks to the creators and contributors of the ESP32 and TFT_eSPI libraries.


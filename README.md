# TTGO ESP32 T-Display Project with UPS

## Overview
This project leverages the TTGO ESP32 T-Display, an ESP32 development board with an integrated display, and is designed to work with a large UPS (Uninterruptible Power Supply) for enhanced power management and reliability. It features WiFi connectivity, time display, button interaction, and UPS voltage monitoring.

## Features
- **WiFi Connectivity**: Connects to a specified WiFi network and prints the connection status.
- **Time Display**: Displays the current time obtained from an NTP server.
- **Button Functions**: Utilizes onboard buttons for display interaction.
- **UPS Voltage Measurement**: Measures and displays the UPS voltage.
- **Screen Time Management**: Controls the display backlight based on user interaction.

## Hardware Requirements
- TTGO ESP32 T-Display board
- Large UPS (Uninterruptible Power Supply)
- USB cable for programming

## Software Requirements
- Arduino IDE
- ESP32 board support (installation URL: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`)
- Required Libraries:
  - TFT_eSPI from Bodmer
  - WiFi
  - SPI
  - time.h
  - esp_adc_cal.h
  - Button2

## Installation

### Setting up Arduino IDE
1. Add ESP32 board support to the Arduino IDE. In File > Preferences, add the following to 'Additional Board Manager URLs':
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
2. Install ESP32 board support via Tools > Board > Boards Manager.

### Installing Libraries
- Open Tools > Library Manager and install:
  - `TFT_eSPI` by Bodmer
- Download the repository from `https://github.com/Xinyuan-LilyGO/TTGO-T-Display` and replace the `TFT_eSPI` directory in `Documents/Arduino/libraries/` with the one from the repository.

### Hardware Setup
- Connect the TTGO ESP32 T-Display to the UPS and to your computer via a USB cable.

### Loading the Sketch
- Open the provided Arduino sketch in the Arduino IDE.
- Select `ESP32 Dev Module` under Tools > Board.
- Select the correct COM port under Tools > Port.
- Upload the sketch to the board.

## Usage
- The device will automatically connect to the specified WiFi network.
- Time will be displayed on the screen, updated from the NTP server.
- Button 1 resets the screen time counter, while Button 2 sets it to a specific value.
- The device measures and displays the voltage of the UPS.
- The display backlight is managed automatically based on user interaction.

## Customization
- Update WiFi credentials in the sketch with your network details.
- Modify NTP server settings as required.
- Adjust screen time management settings as per your preference.

> :clipboard: **Note:** <br>
>     You can find more information on configuration on the [configuration wiki page](https://github.com/doubledave/ttgo-ntp-clock/wiki/Configuration)

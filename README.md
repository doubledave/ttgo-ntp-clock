# ttgo-ntp-clock

[Arduino IDE setup instructions](https://sites.google.com/site/jmaathuis/arduino/lilygo-ttgo-t-display-esp32#h.p_0m3yqZ8aormc) (a little out of date)

### For Version with Button

In Arduino IDE:
  - go to Tools > Manage Libraries
  - click
  - click in the searchbox and type 'Button2' and await your search results.
  - install 'Button2'

In Arduino IDE set this as one of the boards manager URLs in File > Preferences:

`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`

Then go to Tools > board > boards manager and allow it to update.

Tools > board > select ESP32 Arduino > ESP32 Dev Module

Installing the needed library for the screen attached to the TTGO ESP32 T-Display:

Tools > Library Manager, find "TFT_eSPI" from "Bodmer"

Then for it to work right needs an update:

Obtain/clone/download the github repository: https://github.com/Xinyuan-LilyGO/TTGO-T-Display

Take the entire TFT_eSPI directory of this repository and copy/paste this folder into:

C:\Users\\[username]\Documents\Arduino\libraries\

This folder will already exist because you added it in Library Manager.  Overwrite all existing files/subfolders.

With the TTGO T-Display connected by USB, choose the correct COM port from the Tools > Port menu.  The right port won't exist if you're in Windows and the drivers for the USB to serial interface chip didn't get installed.  You can check for the port/driver by looking in the device manager (start > run > devmgmt.msc) in the ports section and/or listed unknown USB devices.  Running Windows Update with the device connected will result in it finding and giving you the option to automatically install the driver for it.

Article explaining much of this: https://lastminuteengineers.com/esp32-ntp-server-date-time-tutorial/

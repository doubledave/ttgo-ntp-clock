// Arduino IDE setup instructions (a little out of date) at
// https://sites.google.com/site/jmaathuis/arduino/lilygo-ttgo-t-display-esp32#h.p_0m3yqZ8aormc
// 
// Arduino IDE set this as one of the boards manager URLs in File > Preferences:
// https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
// 
// Then go to Tools > board > boards manager and allow it to update.
// Tools > board > select ESP32 Arduino > ESP32 Dev Module
// Set the correct COM port.
//
// Installing the needed library for the screen attached to the TTGO ESP32 T-Display:
// Tools > Library Manager, find "TFT_eSPI" from "Bodmer"
// Then for it to work right needs an update:
// Obtain/clone/download the github repository: https://github.com/Xinyuan-LilyGO/TTGO-T-Display
// Take the entire TFT_eSPI directory of this repository and copy/paste this folder into:
// C:\Users\[username]\Documents\Arduino\libraries\
// This folder will already exist because you added it in Library Manager.  Overwrite all existing files/subfolders.
//
// Article explaining this: https://lastminuteengineers.com/esp32-ntp-server-date-time-tutorial/

#include <WiFi.h>
#include "time.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include "esp_adc_cal.h"
#include "Button2.h"


#define TFT_GREY 0x5AEB
#define ADC_EN              14  //ADC_EN is the ADC detection enable port
#define ADC_PIN             34
#define BUTTON_1            35

int vref = 1100;
float battery_voltage;

// Bring in our button library and give it context. - TJB
Button2 btn1(BUTTON_1);

TFT_eSPI tft = TFT_eSPI();
byte fontNum = 2;
  // Only font numbers 2,4,6,7 are valid. Font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : . - a p m
  // Font 7 is a 7 segment font and only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : .

const char* ssid       = "****";
const char* password   = "****";
// const char* ssid2       = "";
// const char* apssword2   = "";

// const char* ntpServer = "us.pool.ntp.org";
const char* ntpServer = "192.168.1.1";
const long  gmtOffset_sec = (-6 * 3600);
const int   daylightOffset_sec = 3600;

String msg = String(0);
// An accumulator to track how many 
// cycles the screen has been active for 
int screen_time = 0;

int btnClck = false;

float voltage()
{
  uint16_t v = analogRead(ADC_PIN);
  float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  String voltage = "Voltage :" + String(battery_voltage) + "V";
  tft.drawCentreString(voltage, tft.width()/2, tft.height()/2+36, 4);
  return battery_voltage;
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    tft.drawCentreString("Failed to obtain time", tft.width()/2, tft.height()/2-16, fontNum);
    Serial.println("Failed to obtain time");
    Serial2.println("Failed to obtain time");
    return;
  }
  char timeStringBuff[50];
  digitalWrite(TFT_BL, HIGH);
  strftime(timeStringBuff, sizeof(timeStringBuff), "%H:%M:%S", &timeinfo);
  tft.setTextColor(TFT_BLACK, TFT_GREY);
  tft.drawCentreString(timeStringBuff, tft.width()/2, tft.height()/2-16, 7);

  
  
  strftime(timeStringBuff, sizeof(timeStringBuff), "     %A %B %d %Y     ", &timeinfo); // DoW, Month, Day, Year
  tft.setTextColor(TFT_WHITE, TFT_GREY);
  tft.drawCentreString(timeStringBuff, tft.width()/2, tft.height()/2-40,2);
  Serial.println(&timeinfo, "%A %B %d %Y %H:%M:%S");
  Serial2.println(&timeinfo, "%A %B %d %Y %H:%M:%S");

  // delay(200); Slowing things down
  if (screen_time >= 30) {
    digitalWrite(TFT_BL, LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1,25,26);

    /*
    ADC_EN is the ADC detection enable port
    If the USB port is used for power supply, it is turned on by default.
    If it is powered by battery, it needs to be set to high level
    */
  pinMode(ADC_EN, OUTPUT);
  digitalWrite(ADC_EN, HIGH);

  button_init();

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_GREY);
  tft.setTextColor(TFT_BLACK, TFT_GREY);

  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);    //Check type of calibration value used to characterize ADC
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
      Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
      vref = adc_chars.vref;
  } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
      Serial.printf("Two Point --> coeff_a:%umV coeff_b:%umV\n", adc_chars.coeff_a, adc_chars.coeff_b);
  } else {
      Serial.println("Default Vref: 1100mV");
  }

  battery_voltage = voltage();  //also display voltage on screen
  
  //connect to WiFi
  tft.drawCentreString(String(ssid), tft.width()/2, tft.height()/2-16, fontNum);
  Serial.printf("Connecting to %s ", ssid);
  Serial2.printf("Connecting to %s ", ssid);
  int wifinum = 0;
  
  if (sizeof(password) > 0)
  { WiFi.begin(ssid, password); }
  else
  { WiFi.begin(ssid); }
  int retrycount = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
      delay(500);
      Serial.print(".");
      Serial2.print(".");
      battery_voltage = voltage();  //also display voltage on screen
  }
  tft.drawCentreString(" CONNECTED ", tft.width()/2, tft.height()/2-16, 4);
  Serial.println(" CONNECTED");
  Serial2.println(" CONNECTED");
  delay(500);
  battery_voltage = voltage();  //also display voltage on screen
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  tft.fillScreen(TFT_GREY);
  battery_voltage = voltage();  //also display voltage on screen
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  Serial.println(" Disconnecting WiFi as it's no longer needed");
  Serial2.println(" Disconnecting WiFi as it's no longer needed");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  battery_voltage = voltage();  //also display voltage on screen
}

void button_init(){
  // Initialize the button on pin35 
  btn1.setLongClickHandler([](Button2 & b){
    screen_time = 0;
  });
}

void button_loop(){
  // Check the buttons - TJB
  btn1.loop();
}

void loop()
{
  // Run the button loop to check
  // for presses. - TJB
  button_loop();
  delay(1000);

  // Check screen status. - TJB
  int (scrn) = digitalRead(TFT_BL);
  screen_time = screen_time + 1;
  button_loop();
  //Serial.println(screen_time);
  //Serial.println(scrn);
  if (screen_time >= 30) {
    if (scrn == 1 ) {
      digitalWrite(TFT_BL, LOW);
    }
  }

  // Timeout below 30s.
  // This can also mean that the button 
  // was pressed which resets the timer. - TJB
  if (screen_time <= 29) {

    // If the screen is off, and the counter 
    // is under or at 29, turn on the screen. - TJB
    if (scrn == 0) {
      digitalWrite(TFT_BL, HIGH);
    }

    // Moved calls that write to screen to within loop - TJB
    battery_voltage = voltage();  //also display voltage on screen
    printLocalTime();
    delay(100);
  }
}
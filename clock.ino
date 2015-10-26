/*********************

Colored clock for the Adafruit RGB Character LCD Shield + SD-RTC shield

**********************/

#include <Wire.h>
#include "RTClib.h"
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7
#define aref_voltage 3.3 

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
RTC_DS1307 rtc;
DateTime now;

void setup()
{
  lcd.begin(16,2);
  lcd.setBacklight(YELLOW);
  Wire.begin();
  rtc.begin();
  //Serial.begin(9600); 
}

void loop() 
{
  now = rtc.now();
  updateTime();
  updateColor();
  //updateSense();
  updateLight();
}

void updateTime()
{

 // Time variables
 int s = now.second(); 
 int m = now.minute(); 
 int h = now.hour();
 int d = now.day();  
 int M = now.month();
 int y = now.year(); 
 int D = now.dayOfWeek();
 
 // Clock
 lcd.setCursor(6,1);
 if (h-1<10) {lcd.print(0);} lcd.print(h-1);
 lcd.print(":");
 if (m<10) {lcd.print(0);} lcd.print(m);
 lcd.print(":");
 if (s<10) {lcd.print(0);} lcd.print(s);

 // Calendar
 lcd.setCursor(2,0);
 if (D=1)lcd.print("Mon");
 else if (D=2)lcd.print("Thu");
 else if (D=3)lcd.print("Wed");
 else if (D=4)lcd.print("Thu");
 else if (D=5)lcd.print("Fri");
 else if (D=6)lcd.print("Sat");
 else if (D=7)lcd.print("Sun");
 lcd.setCursor(6,0);
 if (d<10) {lcd.print(0);} lcd.print(d);
 lcd.print(".");
lcd.print(M);
 lcd.print(".");
 lcd.print(y-2000);

}

void updateColor()
{

 uint8_t buttons = lcd.readButtons();
 
  if (buttons) 
  {
    if (buttons & BUTTON_UP) {
      lcd.setBacklight(RED);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.setBacklight(YELLOW);
    }
    if (buttons & BUTTON_LEFT) {
      lcd.setBacklight(GREEN);
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.setBacklight(TEAL);
    }
    if (buttons & BUTTON_SELECT) {
      lcd.setBacklight(VIOLET);
    } 
   }
} 

//void updateTemp() 
//{

  //int tempPin = 1; 
  //int tempReading;


//}

void updateLight() 
{

  int photocellPin = 0; 
  int photocellReading; 

  photocellReading = analogRead(photocellPin);
  lcd.setCursor(2,1); 
  lcd.print(photocellReading);

}

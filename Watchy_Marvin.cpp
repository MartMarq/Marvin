#include "Watchy_Marvin.h"

#define DARKMODE false

const uint8_t BATTERY_SEGMENT_WIDTH = 5;
const uint8_t BATTERY_SEGMENT_HEIGHT = 5;
const uint8_t BATTERY_SEGMENT_SPACING = 5;

void WatchyMarvin::drawWatchFace(){
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    drawTime();
    drawDate();
    drawSteps();
    drawBattery();
    }


void WatchyMarvin::drawTime(){
    display.setFont(&FreeSans40pt7b);
    display.setCursor(0, 60);
    uint8_t displayHour;
    displayHour = currentTime.Hour;
    
    if(displayHour < 10){
        display.print("0");
    }
    display.print(displayHour);
    display.print(":");
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.println(currentTime.Minute);
   
  }

void WatchyMarvin::drawDate(){
    display.setFont(&FreeSans20pt7b);

    int16_t  x1, y1;
    uint16_t w, h;

    String dayOfWeek = dayShortStr(currentTime.Wday);
    display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
    if(currentTime.Wday == 4){
        w = w - 5;
    }
    display.setCursor(50, 155);
    display.println(dayOfWeek);

    String month = monthShortStr(currentTime.Month);
    display.getTextBounds(month, 60, 110, &x1, &y1, &w, &h);
    display.setCursor(50, 118);
    display.println(month);

    display.setCursor(5, 118);
    if(currentTime.Day < 10){
    display.print("0");
    }
    display.println(currentTime.Day);
    
}
void WatchyMarvin::drawSteps(){
    // reset step counter at midnight
    if (currentTime.Hour == 00 && currentTime.Minute == 00){
      sensor.resetStepCounter();
              //turn off radios
      WiFi.mode(WIFI_OFF);
      btStop();   
          }
          
    //time adjustment start
    //if you don't need a time adjustment, just delete all lines between time adjustment start and end
    //my watchy runs too fast (15 seconds and 150 ms a day), this code set back time each day by 15 seconds and 150 ms
    
	if (currentTime.Hour == 00 && currentTime.Minute == 30){
        
        RTC.read(currentTime);
        int8_t sekunde = currentTime.Second;
        int8_t minute = currentTime.Minute;
        int8_t hour = currentTime.Hour;
        int8_t day = currentTime.Day;
        int8_t month = currentTime.Month;
        int8_t year = tmYearToY2k(currentTime.Year);

        delay(15150);

        tmElements_t tm;
        tm.Month = month;
        tm.Day = day;
        tm.Year = y2kYearToTm(year);
        tm.Hour = hour;
        tm.Minute = minute ;
        tm.Second = sekunde;

        RTC.set(tm);     
         }

    // time adjustment end

    uint32_t stepCount = sensor.getCounter();
    display.drawBitmap(5, 175, steps, 19, 23, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.drawBitmap(145, 90, marvin, 53, 100, DARKMODE ? GxEPD_BLACK : GxEPD_BLACK);
    display.setCursor(30, 195);
    display.println(stepCount);
    
}
void WatchyMarvin::drawBattery(){
   
 
    float VBAT = getBatteryVoltage();
   
    int8_t batteryLevel = ((1.1-(4.2 - VBAT)) * 36.36);

          for(int8_t batterySegments = 0; batterySegments <= batteryLevel; batterySegments++){
          display.fillRect(0 + (batterySegments * BATTERY_SEGMENT_SPACING), 70, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    }
}

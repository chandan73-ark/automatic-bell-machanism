#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
RTC_DS3231 rtc;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int hour , minute, dayofWeek, second;
const int bellpin = 9;
int backlightPin = 8;
int address = 0;
int brightness = 130;
bool Issunday = true;
void setup() 
{
  lcd.begin(20, 4);
  pinMode(backlightPin, OUTPUT);
  analogWrite(backlightPin, brightness);
  Wire.begin();
  rtc.begin();
  pinMode(bellpin, OUTPUT);
  digitalWrite(bellpin, LOW);
  rtc.adjust(DateTime(2023, 8, 7, 10, 14, 50));
  dateandtime();
}


void loop() 
{ 
  dateandtime();

  if (!Issunday)
  {
    working_days();
  }
  else if(Issunday)
  {
    Issunday = false;
  }

}
void working_days()
{
  DateTime now = rtc.now();
  hour = now.hour();
  minute = now.minute();
  second = now.second();
  dayofWeek = now.dayOfTheWeek();
  if (dayofWeek >=1 && dayofWeek <=6){
    if(hour == 10 && minute == 15 && second == 1)
    {
        longBell();
    }
    else if(hour == 10 && minute == 30 && second == 1)
    {
        shortBell();
    }
    else if(hour == 11  && minute == 10 && second == 1 )
    {
        shortBell();
    }
    else if(hour == 11 && minute == 50 && second == 1)
    {
        shortBell();
    }
    else if (hour == 12 && minute == 30 && second == 1)
    {
        shortBell();
    }
    else if (hour == 13 && minute == 10 && second == 1)
    {
        longBell();
    }
    else if(hour == 13 &&  minute == 50 && second == 1)
    {
        longBell();
    }
    else if(hour == 14 && minute == 30 && second == 1)
    {
        shortBell();
    }
    else if(hour == 15 && minute == 10 && second == 1)
    {
        shortBell();
    }
    else if(hour == 15 && minute == 50 && second == 1)
    {
        shortBell();
    }
    else if(hour == 16 && minute == 30 && second == 1)
    {
        longBell();
    }
}
}


void dateandtime()
{ 
  digitalWrite(backlightPin, HIGH);
  DateTime now = rtc.now();
  hour = now.hour();
  minute = now.minute();
  second = now.second();
  dayofWeek = now.dayOfTheWeek();
  if (dayofWeek != 0)
    { lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print(now.day());  
      lcd.print('-');
      lcd.print(now.month());
      lcd.print('-');
      lcd.print(now.year(), DEC);
      lcd.setCursor(5,1);
      switch (now.dayOfTheWeek())
      {
        case 0: lcd.print("Sunday"); break;
        case 1: lcd.print("Monday"); break;
        case 2: lcd.print("Tuesday"); break;
        case 3: lcd.print("Wednesday"); break;
        case 4: lcd.print("Thursday"); break;
        case 5: lcd.print("Friday"); break;
        case 6: lcd.print("Saturday"); break;
        default: lcd.print("Invalid day"); break;
      }
      lcd.setCursor(5, 2);
      lcd.print(now.hour());
      lcd.print(':');
      lcd.print(now.minute());
      lcd.print(':');
      lcd.print(now.second());
      // Store the time and date in the EEPROM
      EEPROM.put(address, now);
      delay(1000);
    }
  else if(dayofWeek == 0)
  {
    Issunday;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TODAY IS SUNDAY");
    delay(1000);
    EEPROM.put(address, now);
    delay(1000);
  }
  EEPROM.put(address, now);
}

void longBell()
{
  lcd.clear();
  lcd.print("LONG BELL");
  digitalWrite(bellpin,HIGH);
  delay(5000);
  digitalWrite(bellpin, LOW);
}

void shortBell()
{
  lcd.clear();
  lcd.print("SHORT BELL");
  digitalWrite(bellpin, HIGH);
  delay(2500);
  digitalWrite(bellpin, LOW);
}

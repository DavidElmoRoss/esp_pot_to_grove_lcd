/*
  Title:  Program to send Analog value and voltage to Monitor and Grove LCD
  Author: David Elmo Ross
  Date:   July 21, 2025
  Description: This program takes the reading from the POT and puts
               the Analog Value & Voltage on the SERIAL MONITOR and GROVE LCD
*/

#include <Arduino.h>                // include arduino.h

#include <Wire.h>                   // include Wire.h library
#include "rgb_lcd.h"                // include rgb_lcd library
#define PIN_ANALOG_IN 34            // Pin 34 is the A/D being used
                                    // other a2d pins are 35,36, 39
char buff[16];                      // char buff for convert float to string
short adcVal;                       // declare adcVal as a short
double voltage;                     // declare voltage as a double
rgb_lcd lcd;                        // make lcd an instance of rgb_lcd 

void setup()
{
  Serial.begin(115200);           // platformio.ini has monitor_speed = 115200                                    
  Wire.begin();                     // initialize WIRE system
  lcd.begin(16,2);                  // start up the LCD
  lcd.display();                    // turn on LCD display
                                    // clears Monitor and positions cursor at
                                    // (10,30) and makes text bold red
                                    // and prints title                                            
  printf("\e[1;1H\e[2J\e[10;30H\e[1;31mAnalog Value Analog Voltage");
  printf("\e[0m\e[34m");            // set data colour to by cyan
  lcd.setCursor(0,0);               // set lcd cursor to col 0 row 0
  lcd.setRGB(0x00,0x80,0x80);       // make lcd colour TEAL
  lcd.print("  Value  Voltage");    // print title on LCD
}

void loop() 
{
  for(;;)                                   // endless loop
  {
    adcVal = analogRead(PIN_ANALOG_IN);   // adcVal gets value from 0-4095
    voltage = adcVal / 4096.0 * 3.333;    // voltages gets value from 0-3.33
    printf("\e[11;35H");                  // position cursor at (11,35)
    printf("%4d\t\t%4.2f",adcVal,voltage); // print adcVal and voltage there
    sprintf(buff,"%4d   %4.2f",           // convert adVal, voltage to 
            adcVal,voltage);              // string array and put in buff
    lcd.setCursor(2,1);                   // position cursor at col 2 and row 1
    lcd.print(buff);                      // print contents of buff to lcd
    fflush(stdout);                       // fflush stdout to synch screen data
    delay(200);                           // wait 200 ms between samples
  }
}





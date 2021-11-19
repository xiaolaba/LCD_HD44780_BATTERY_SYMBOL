/*
xiaolaba, 2017-JUN-12
UNO, Arduino 1.82
Demo my own battery gauge and symbol.
use a 16x2 LCM display, Hitachi HD44780 compatible
LiquidCrystal library driver.
*/
 
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
//modified 2013/may/11, xiaolaba
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // change D12, D11 to D7, D6, because Atmega328p D12 = MISO, D11 = MOSI, may interfere with max6675 SPI, test ok
 
// ref: http://omerk.github.io/lcdchargen/
// build my degree symbol
byte degreeC[8] = {
  0b00000,
  0b10000,
  0b00110,
  0b01001,
  0b01000,
  0b01000,
  0b01001,
  0b00110
};


// xiaolaba, custom battery gauge symbols, 13% - 100%, 8 steps
const byte bat_13[8] = { 0xe, 0x1b, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f};
const byte bat_25[8] = { 0xe, 0x1b, 0x11, 0x11, 0x11, 0x11, 0x1f, 0x1f};
const byte bat_38[8] = { 0xe, 0x1b, 0x11, 0x11, 0x11, 0x1f, 0x1f, 0x1f};
const byte bat_50[8] = { 0xe, 0x1b, 0x11, 0x11, 0x1f, 0x1f, 0x1f, 0x1f};
const byte bat_63[8] = { 0xe, 0x1b, 0x11, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
const byte bat_75[8] = { 0xe, 0x1b, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
const byte bat_88[8] = { 0xe, 0x11, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
const byte bat_100[8] ={ 0xe, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};


// xiaolaba, custom battery gauge symbols, one table only, 13% - 100%, 8 steps
const byte battery_symbols[64] = { 
  0xe, 0x1b, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f,  // battery charge, 13%
  0xe, 0x1b, 0x11, 0x11, 0x11, 0x11, 0x1f, 0x1f,  // 25%
  0xe, 0x1b, 0x11, 0x11, 0x11, 0x1f, 0x1f, 0x1f,  // 38%
  0xe, 0x1b, 0x11, 0x11, 0x1f, 0x1f, 0x1f, 0x1f,  // 50%
  0xe, 0x1b, 0x11, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,  // 63%
  0xe, 0x1b, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,  // 75%
  0xe, 0x11, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,  // 88%
  0xe, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f   // 100%
};

// LCM line1 and line2, easy for human
#define line1 0
#define line2 1
 
void setup()
{
  // set up number of columns and rows of LCM, 16 colume x 2 rows
  lcd.begin(16, 2);
  
  // create 8 battery symbols, custom characters, one by one, write to LCM CGM RAM
  // 100% by 8 steps, each step about 13% increament
  // simple way
  lcd.createChar(0, bat_13);  // create the first custom battery symbol, 13%
  lcd.createChar(1, bat_25);  // second battery symbol, 25%
  lcd.createChar(2, bat_38);  // so on...
  lcd.createChar(3, bat_50);
  lcd.createChar(4, bat_63);
  lcd.createChar(5, bat_75);
  lcd.createChar(6, bat_88);
  lcd.createChar(7, bat_100);
  //lcd.createChar(7, degreeC);

  lcd.setCursor(0, line1);  //move to position 0, line 1
      
  // write the battery gauge symbol one by one to the LCM
  lcd.write((uint8_t) 0);
  lcd.write((uint8_t) 1);
  lcd.write((uint8_t) 2);
  lcd.write((uint8_t) 3);
  lcd.write((uint8_t) 4);
  lcd.write((uint8_t) 5);
  lcd.write((uint8_t) 6);
  lcd.write((uint8_t) 7);

  //lcd.setCursor(8, line1); //move to position 8, line1
  lcd.print("xiaolaba");  // Print a message to the LCD.

  


  lcd.setCursor(0, line2); //move to position 0, line2
  lcd.print("hi,line");  // Print a message to the LCM, final display "hi,line2"
  lcd.print((uint8_t) 2); //print integer 2 to LCM, why typecast? see: http://arduino.cc/forum/index.php?topic=74666.0

  // create & write 8 battery symbols, custom character, one by one, programable way
  for ( int i = 0; i < 8; i++) {
    lcd.createChar(i, battery_symbols + i*8 ); // create one symbol at a time
    lcd.setCursor(i+8, line2);  //move to next position at line2
    lcd.write((uint8_t) i);     //write the symbol to LCM
  }

}
 
void loop()
{
  //demo battery charging status
  for ( int i = 0; i < 8; i++) {
    lcd.setCursor(7, line1);  //always point to position 7, line1
    lcd.write((uint8_t) i);   //write 8 battery symbols to LCM, one by one
    delay(200);
  }

}

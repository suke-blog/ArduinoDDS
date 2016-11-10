//*****************************************************************************
//
// File Name	: 'ArduinoDDS.ino'
// Title		: AVR DDS2 signal generator for Arduino
// Author		: suke-blog.com
// Created		: 2016-11-09
// Revised		: 2016-11-09
// Version		: 1.0
// Target MCU	: Atmel AVR series ATmega168/328(for Arduino)
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//serial
#define SERIAL_RATE 9600
#define SERIAL_TIMEOUT 1000

//mode select pin
#define MODE_PIN A7
#define MODE_READCOUNT 10
#define MODE_THRESHOLD (0xE0 * 10)

bool flag_debug = false;

//export from AVR DDS SignalGenerator
extern "C" {
  int avrdds_main(void);
}

//LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

extern "C" void debug_write(char *buf){
  if(flag_debug){
    Serial.write(buf);
  }
}

extern "C" void LCDinit(){
}

extern "C" void LCDclr(){
  lcd.clear();
}

extern "C" void LCDGotoXY(uint8_t col, uint8_t row){
  lcd.setCursor(col, row);
}

extern "C" void LCDcursorOFF(){
  lcd.noCursor();
}

extern "C" void LCDsendChar(uint8_t ch){
  lcd.write(ch);
}

extern "C" void CopyStringtoLCD(const uint8_t *FlashLoc, uint8_t x, uint8_t y){
  uint8_t i = 0;

  lcd.setCursor(x,y);
  for(i=0; (uint8_t)pgm_read_byte(&FlashLoc[i]); i++){
    lcd.write((uint8_t)pgm_read_byte(&FlashLoc[i]));
  }
}

void setup() {
  uint32_t mode_value = 0;
  uint8_t i = 0;

  Serial.begin(SERIAL_RATE);
  Serial.setTimeout(SERIAL_TIMEOUT);
  Serial.write("AVR DDS SignalGenerator for Arduino.\n");

  lcd.begin(16, 2);
  lcd.print("DDS for Arduino");
  delay(1000);

  //get modepin value
  for(i=0; i<MODE_READCOUNT; i++){
    mode_value += analogRead(MODE_PIN);
  }

  //select DDS or debug mode
  if(mode_value > MODE_THRESHOLD){
    Serial.write("[DDS mode]\n");
    Serial.end();
    flag_debug = false;

    //reset avr peripheral
    cli();                                  //disable global interrupt
    WDTCSR = (1<<WDCE) | (1<<WDP3) | (1<<WDP0);//stop wdt
    UCSR0B = 0x00;                          //disable UART

    //reset all timer
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TIMSK0 = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TIMSK1 = 0x00;
    TCCR2A = 0x00;
    TCCR2B = 0x00;
    TIMSK2 = 0x00;

    sei();  //enable global interrupt

  }else{
    //for debug
    Serial.write("[debug mode]\n");
    flag_debug = true;
  }

  //jump AVR DDS main function
  avrdds_main();
}


void loop() {
}

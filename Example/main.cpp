// display test for C12832A1Z mbed Application Board
// sstaub(c)2017

#include "mbed.h"
#include "C12832A1Z.h"
#include "Small_7.h"
#include "Fonts/ArialR12x14.h"

C12832A1Z lcd(p5, p7, p6, p8, p11); // MOSI, SCK, Reset, A0, CS

int main() {
  // creating logo
  lcd.update(MANUAL);
  lcd.rectangle(0, 0, 127, 31, 1);
  lcd.fillrect(2, 2, 4, 4, 1);
  lcd.fillrect(2, 27, 4, 29, 1);
  lcd.fillrect(61, 2, 63, 4, 1);
  lcd.fillrect(61, 27, 63, 29, 1);
  lcd.line(65, 0, 65, 31, 1);
  lcd.circle(33, 15, 10, 1);
  lcd.circle(33, 15, 6, 1);
  lcd.fillcircle(33, 15, 3, 1);
  lcd.update();
  lcd.update(AUTO);
  // creating description
  lcd.locate(70, 1);
  lcd.font((unsigned char*)ArialR12x14);
  lcd.printf("mbed");
  lcd.locate(70, 13);
  lcd.font((unsigned char*)Small_7);
  lcd.printf("NHD");
  lcd.locate(70, 22);
  lcd.printf("C12832A1Z");

  ThisThread::sleep_for(1s);
  lcd.display(CONTRAST, 16); // contrast low
  ThisThread::sleep_for(1s);
  lcd.display(CONTRAST, 40); // contrast high
  ThisThread::sleep_for(1s);
  lcd.display(CONTRAST);     // contrast default
  ThisThread::sleep_for(1s);
  lcd.display(OFF);          // display off
  ThisThread::sleep_for(1s);
  lcd.display(ON);           // display on
  ThisThread::sleep_for(1s);
  lcd.display(SLEEP);        // display sleep mode
  ThisThread::sleep_for(1s);
  lcd.display(ON);

  while(1) {                 // main loop
    lcd.display(INVERT);     // display inverted
    lcd.display(BOTTOM);     // display rotated
    ThisThread::sleep_for(2s);
    lcd.display(NORM);    // display normal
    lcd.display(TOPVIEW);    // display normal orientation
    ThisThread::sleep_for(2s);
    }
  }

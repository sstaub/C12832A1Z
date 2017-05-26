# mbed LCD library for the mbed application board / shield

This library is for the LCD of the mbed application board and shield 
https://developer.mbed.org/components/mbed-Application-Board/ and https://developer.mbed.org/components/mbed-Application-Shield/<br>
It uses better algorithms (Bresenham) for the graphics than the original library.


## Installation

1. "Download":https://github.com/sstaub/C12832A1Z/archive/master.zip the Master branch from GitHub.
2. Unzip and modify the folder name to "C12832A1Z"
3. Move the modified folder on your Library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).


## Example

Here is an example for the application board with the mbed lpc1768.

```
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

  wait(1);
  lcd.display(CONTRAST, 16); // contrast low
  wait(1);
  lcd.display(CONTRAST, 40); // contrast high
  wait(1);
  lcd.display(CONTRAST);     // contrast default
  wait(1);
  lcd.display(OFF);          // display off
  wait(1);
  lcd.display(ON);           // display on
  wait(1);
  lcd.display(SLEEP);        // display sleep mode
  wait(1);
  lcd.display(ON);

  while(1) {                 // main loop
    lcd.display(INVERT);     // display inverted
    lcd.display(BOTTOM);     // display rotated
    wait(2);
    lcd.display(DEFAULT);    // display normal
    lcd.display(TOPVIEW);    // display normal orientation
    wait(2);
    }
  }


```

## Documentation

### Constructor
**C12832A1Z(PinName mosi, PinName sck, PinName reset, PinName a0, PinName cs)**<br>
create a C12832A1Z object connected to SPI <br>
	
### Functions

**void bitmap(Bitmap bm, int x, int y)**<br>
print bitmap to buffer <br>
>**Parameters**<br>
>bm -> Bitmap in flash<br> 
>x -> x start<br> 
>y -> y start<br>

**void character(uint8_t x, uint8_t y, uint8_t  c)**<br>
draw a character on given position out of the active font to the LCD <br>

**void circle(int x, int y, int r, uint8_t  colour)**<br>
draw a circle<br> 
>**Parameters**<br>
>x0,y0 -> center<br> 
>r -> radius<br>
>colour -> 1 set pixel, 0 erase pixel <br>

**void cls()**<br>
clears the screen

**void display(uint8_t display)**<br>
display functions<br>
>**Parameter display**<br>
>ON switch display on, or wake up from sleep<br>
>OFF set display off<br>
>SLEEP set display off and to sleep mode<br>
>BOTTOM (default) set display orientation 0°<br>
>TOPVIEW set display oriention to 180°<br> 
>INVERT invert the pixels<br>
>DEFAULT normal pixel display<br>
>CONTRAST set display contrast to default<br>

**void display(uint8_t display, uint8_t value)**<br>
display functions<br>
>**Parameter display**<br>
>CONTRAST set diplay contrast
>**Parameter value**<br>
>value -> set the contrast value from 0 to 63, default is 31

**void fillcircle(int x, int y, int r, uint8_t colour)**<br>
draw a filled circle<br>
>**Parameters**<br>
>x0,y0 -> center<br> 
>r -> radius<br> 
>color -> 1 set pixel, 0 erase pixel<br>

**void fillrect(int x0, int y0, int x1, int y1, uint8_t colour)**<br>
draw a filled rect<br>
>**Parameters**<br>
>x0,y0 -> top left corner<br>
>x1,y1 -> down right corner<br>
>color -> 1 set pixel, 0 erase pixel<br>

**void fillrrect(int x0, int y0, int x1, int y1, int rnd, uint8_t colour)**<br>
draw a filled rounded rect<br>
>x0,y0 -> top left corner<br>
>x1,y1 -> down right corner<br> 
>rnd -> radius of the rounding<br>
>color -> 1 set pixel, 0 erase pixel<br>

**void font(uint8_t * f)**<br>
select the font to use<br>
>**Parameter**<br>
>f -> pointer to font array<br>
font array can created with GLCD Font Creator from http://www.mikroe.com you have to add 4 parameter at the beginning of the font array to use:
the number of byte / char
the vertial size in pixel
the horizontal size in pixel
the number of byte per vertical line you also have to change the array to char[]

```
lcd.font((unsigned char*)Small_7);
```

**void line(int x0, int y0, int x1, int y1, uint8_t colour)**<br>
draw a 1 pixel line<br>
>**Parameters**<br>
>x0,y0 -> start point<br>
>x1,y1 -> end point<br>
>color -> 1 set pixel, 0 erase pixel<br>

**void locate(uint8_t x, uint8_t y)**<br>
set top left position of char/printf<br>
>**Parameters**<br>
>x -> x-position<br> 
>y -> y-position<br>

**void pixel(int x, int y, uint8_t colour)**<br>
draw a pixel in buffer at x, y black or white<br>
>**Parameters**<br>
>x -> horizontal position<br>
>y -> vertical position<br>
>colour -> 1 set pixel, 0 erase pixel there is no update, it writes the pixel only in the buffer<br>

**void point(int x, int y, uint8_t colour)**<br>
draw a single point<br>
>**Parameters**<br>
>x -> horizontal position<br>
>y -> vertical position<br>
>colour -> 1 set pixel, 0 erase pixel<br>

**void rectangle(int x0, int y0, int x1, int y1, uint8_t colour)**<br>
draw a rect<br>
>**Parameters**<br>
>x0,y0 -> top left corner<br>
>x1,y1 -> down right corner<br>
>color -> 1 set pixel, 0 erase pixel<br>

**void roundrect(int x0, int y0, int x1, int y1, int rnd, uint8_t colour)**<br>
draw a rounded rect<br>
>**Parameters**<br>
>x0,y0 -> top left corner<br>
>x1,y1 -> down right corner<br>
>rnd -> radius of the rounding<br>
>color -> 1 set pixel, 0 erase pixel<br>

**void update()**<br>
**void update(uint8_t mode)**<br>
update to copy display buffer to lcd<br>
>**Parameter mode**<br>
>AUTO set update mode to auto, default<br>
>MANUELL the update function must manually set

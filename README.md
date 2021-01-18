# mbed LCD library for the mbed application board / shield

This library is for the LCD of the mbed application board and shield 
https://developer.mbed.org/components/mbed-Application-Board/ and https://developer.mbed.org/components/mbed-Application-Shield/<br>
It uses better algorithms (Bresenham) for the graphics than the original library.


## Installation

1. "Download":https://github.com/sstaub/C12832A1Z/archive/master.zip the Master branch from GitHub
2. Unzip and modify the folder name to "C12832A1Z"
3. Move the modified folder on your Library folder (On your `Libraries` folder inside Sketchbooks or Arduino software)


## Example

Here is an example for the application board with the mbed lpc1768 for mbed 6

```cpp
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
  lcd.rectangle(0, 0, 127, 31);
  lcd.fillrect(2, 2, 4, 4);
  lcd.fillrect(2, 27, 4, 29);
  lcd.fillrect(61, 2, 63, 4);
  lcd.fillrect(61, 27, 63, 29);
  lcd.line(65, 0, 65, 31);
  lcd.circle(33, 15, 10);
  lcd.circle(33, 15, 6);
  lcd.fillcircle(33, 15, 3);
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
    lcd.display(DEFAULT);    // display normal
    lcd.display(TOPVIEW);    // display normal orientation
    ThisThread::sleep_for(2s);
    }
  }


```

# Documentation

## Constructor

```cpp
C12832A1Z::C12832A1Z(PinName mosi, PinName sck, PinName reset, PinName select, PinName cs) : spi(mosi, NC, sck), rst(reset), a0(select), cs1(cs), graphic_buffer()
```

Create a C12832A1Z object connected to SPI

- **mosi** MOSI pin
- **sck** SCK clock pin
- **reset** Reset pin
- **select** A0 pin
- **cs1** CS pin

**Example**

```cpp
C12832A1Z lcd(p5, p7, p6, p8, p11); // MOSI, SCK, Reset, A0, CS
```

## Class Functions

### Update

```cpp
void C12832A1Z::update(update_t mode)
void C12832A1Z::update()
```

Update to copy display buffer to lcd

- **mode** update mode<br>
AUTO set update mode to auto, default<br>
MANUELL the update function must manually set

**Example**

```cpp
lcd.update(MANUAL); // switch to manual update
lcd.update(); // make the last graphic command in manual mode visible
```

### Clear Screen

```cpp
void C12832A1Z::cls()
```

Clears the screen

**Example**

```cpp
lcd.cls();
```

### Location

```cpp
void C12832A1Z::locate(uint8_t x, uint8_t y)
```

Set the top left position of char / printf

- **x** position for x
- **y** position for y

### Display Functions

```cpp
void C12832A1Z::display(modes_t display)
```

Display functions modes:

- **ON** switch display on, or wake up from sleep
- **OFF** set display off
- **SLEEP** set display off and to sleep mode
- **BOTTOM** (default) set display orientation 0°
- **TOPVIEW** set display oriention to 180° 
- **INVERT** invert the pixels
- **DEFAULT** normal pixel display
- **CONTRAST** set display contrast to default

```cpp
void C12832A1Z::display(modes_t display, uint8_t value)
```

Display function **CONTRAST** with an additional parameter

**Examples**

```cpp
lcd.display(CONTRAST, 16); // contrast low
lcd.display(CONTRAST, 40); // contrast high
lcd.display(CONTRAST);     // contrast default

```
### Fonts

```cpp
void C12832A1Z::font(uint8_t *f)
```

Select the font to use

- **f** pointer to font array<br>

Font array can created with GLCD Font Creator from http://www.mikroe.com you have to add 4 parameter at the beginning of the font array to use:

- the number of byte / char
- the vertial size in pixel
- the horizontal size in pixel
- the number of byte per vertical line you also have to change the array to char[]

**Example**

```cpp
lcd.font((unsigned char*)Small_7);
```

## Drawing Functions

Each Pixel can have two colors:

```cpp
enum color_t {
	WHITE,
	BLACK
	};
```
The Algorithms are based on Bresenham [https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)

### Point

```cpp
void C12832A1Z::pixel(int x, int y, color_t color)
```

Draw a single point

- **x** horizontal position x
- **y** vertical position y
- **color** point color, BLACK (standard) set pixel, WHITE erase pixel

**Example**

```cpp
lcd.pixel(10, 10); // draws a point on 10 / 10 in black
```

### Line

```cpp
void C12832A1Z::line(int x0, int y0, int x1, int y1, color_t color)
```

Draw a 1 pixel line

- **x0, y0** start point
- **x1, y1** end point
- **color** line color, BLACK (standard) set pixel, WHITE erase pixel

**Example**

```cpp
lcd.line(65, 0, 65, 31); // draws a black line
```

### Rectangle

```cpp
void C12832A1Z::rectangle(int x0, int y0, int x1, int y1, color_t color)
```

Draw a rectangle

- **x0, y0** top left corner
- **x1, y1** down right corner
- **color** line color, BLACK (standard) set pixel, WHITE erase pixel

**Example**

```cpp
lcd.rectangle(0, 0, 127, 31); // draws a black rectangle
```

### Filled Rectangle

```cpp
void C12832A1Z::fillrect(int x0, int y0, int x1, int y1, color_t color)
```

Draw a filled rectangle

- **x0, y0** top left corner
- **x1, y1** down right corner
- **color** fill color, BLACK (standard) set pixel, WHITE erase pixel

**Example**

```cpp
lcd.fillrect(0, 0, 127, 31); // draws a filled rectangle
```


### Rounded Recatangle

```cpp
void C12832A1Z::roundrect(int x0, int y0, int x1, int y1, int rnd, color_t color)
```

Draw a rounded rectangle

- **x0, y0** top left corner
- **x1, y1** down right corner
- **rnd** radius of the rounding
- **color** line color, BLACK (standard) set pixel, WHITE erase pixel

**Example**

```cpp
lcd.fillrect(0, 0, 127, 31, 3); // draws a rounded rectangle with radius 3
```

### Filled Rounded Rectangle

```cpp
void C12832A1Z::fillrrect(int x0, int y0, int x1, int y1, int rnd, color_t color)
```

Draw a filled rounded rect

- **x0, y0** top left corner
- **x1, y1** down right corner
- **rnd** radius of the rounding
- **color** fill color, BLACK (standard) set pixel, WHITE erase pixel

**Example**

```cpp
lcd.fillrrect(0, 0, 127, 31, 3); // draws a filled, rounded rectangle with radius 3
```

### Circle

```cpp
void C12832A1Z::circle(int x0, int y0, int r, color_t color)
```

Draw a circle

- **x0, y0** center
- **r** radius
- **color** circle color, BLACK (standard) set pixel, WHITE erase pixel

**Example**

```cpp
lcd.circle(33, 15, 10); // draws a circle with radius 10
```

### Filled Circle

```cpp
void C12832A1Z::fillcircle(int x0, int y0, int r, color_t color)
```

Draw a filled circle

- **x0, y0** center
- **r** radius
- **color** fill color, BLACK (standard) set pixel, WHITE erase pixel

**Example**

```cpp
lcd.fillcircle(33, 15, 3);
```

### Bitmap

```cpp
struct Bitmap {
	int xSize;
	int ySize;
	int byte_in_Line;
	char *data;
	};
```
File structure of a Bitmap.

```cpp
void C12832A1Z::bitmap(Bitmap bm, int x, int y)
```

Draw bitmap to buffer

- **bm** Bitmap structure
- **x** start position x
- **y** start position y


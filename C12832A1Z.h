/* mbed library for the C12832A1Z, 132x28 pixel LCD for mbed6
 * use ST7565R controller
 * Copyright (c) 2020 Stefan Staub
 * Released under the MIT License: http://mbed.org/license/mit
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef C12832A1Z_H
#define C12832A1Z_H

#include "mbed.h"
#include "Stream.h"

/** @brief update modes
 *
 * @param AUTO default
 * @param MANUELL
 *
 */
enum update_t{MANUAL, AUTO};

/** @brief display settings
 *
 * @param ON display on, default
 * @param OFF display off
 * @param SLEEP sets the display to sleep mode
 * @param DEFAULT default
 * @param INVERT inverts display
 * @param BOTTOM rotate the screento 180°
 * @param TOPVIEW default 0° rotate the screento 180°
 *
 */
enum modes_t{ON, OFF, SLEEP, DEFAULT, INVERT, BOTTOM, TOPVIEW, CONTRAST, RST};

/** @brief bitmap
 *
 */
struct Bitmap {
	int xSize;
	int ySize;
	int byte_in_Line;
	char *data;
	};

/** @brief Library for the LCD Display of the mbed Application Board
 *
 */
class C12832A1Z : public Stream  {

	public:

		/** @brief create a C12832A1Z object connected to SPI
		 *
		 * @param mosi pinname
		 * @param sck pinname
		 * @param reset pinname
		 * @param a0 pinname
		 * @param cs pinname
		 *
		 */
		C12832A1Z(PinName mosi, PinName sck, PinName reset, PinName a0, PinName cs);

		/** @brief draw a pixel in buffer at x, y black or white
		 *
		 * @param x horizontal position
		 * @param y vertical position
		 * @param colour 1 set pixel, 0 erase pixel
		 * there is no update, it writes the pixel only in the buffer
		 */
		void pixel(int x, int y, uint8_t color);

		/** @brief draw a single point
		 *
		 * @param x horizontal position
		 * @param y vertical position
		 * @param colour 1 set pixel, 0 erase pixel
		 *
		 */
		void point(int x, int y, uint8_t color);

		/** @brief draw a 1 pixel line
		 *
		 * @param x0,y0 start point
		 * @param x1,y1 end point
		 * @param color 1 set pixel, 0 erase pixel
		 *
		 */
		void line(int x0, int y0, int x1, int y1, uint8_t color);

		/** @brief draw a rect
		 *
		 * @param x0,y0 top left corner
		 * @param x1,y1 down right corner
		 * @param color 1 set pixel, 0 erase pixel
		 *
		 */
		void rectangle(int x0, int y0, int x1, int y1, uint8_t color);

		/** @brief draw a filled rect
		 *
		 * @param x0,y0 top left corner
		 * @param x1,y1 down right corner
		 * @param color 1 set pixel, 0 erase pixel
		 *
		 */
		void fillrect(int x0, int y0, int x1, int y1, uint8_t color);

		/** @brief draw a rounded rect
		 *
		 * @param x0,y0 top left corner
		 * @param x1,y1 down right corner
		 * @param rnd radius of the rounding
		 * @param color 1 set pixel, 0 erase pixel
		 *
		 */
		void roundrect(int x0, int y0, int x1, int y1, int rnd, uint8_t color);

		/** @brief draw a filled rounded rect
		 *
		 * @param x0,y0 top left corner
		 * @param x1,y1 down right corner
		 * @param rnd radius of the rounding
		 * @param color 1 set pixel, 0 erase pixel
		 *
		 */
		void fillrrect(int x0, int y0, int x1, int y1, int rnd, uint8_t color);


		/** @brief draw a circle
		 *
		 * @param x0,y0 center
		 * @param r radius
		 * @param color 1 set pixel, 0 erase pixel
		 *
		 */
		void circle(int x, int y, int r, uint8_t color);

		/** @brief draw a filled circle
		 *
		 * @param x0,y0 center
		 * @param r radius
		 * @param color 1 set pixel, 0 erase pixel
		 *
		 * use circle with different radius,
		 * can miss some pixel
		 *
		 */
		void fillcircle(int x, int y, int r, uint8_t color);

		/** @brief copy display buffer to lcd
		 *
		 */
		void update();

		/**
		 * @brief set the update mode
		 * 
		 * @param mode AUTO set update mode to auto, default
		 * @param mode MANUELL the update function must manually set
		 */
		void update(update_t mode);

		/** @brief display functions
		 *
		 * @param display ON switch display on, or wake up from sleep
		 * @param display OFF set display off
		 * @param display SLEEP set display off and to sleep mode
		 * @param display BOTTOM (default) draw display oriention 0°
		 * @param display TOPVIEW draw display oriention to 180°
		 * @param display INVERT invert the pixels
		 * @param display DEFAULT normal pixel display
		 * @param display CONTRAST set display contrast to default
		 *
		 */
		void display(modes_t display);

		/** @brief display functions
		 *
		 * @param display CONTRAST set display contrast with value,
		 * @param value sets display contrast 0 - 63, default 31
		 *
		 */
		void display(modes_t display, uint8_t value);

		/** @brief clear the screen
		 *
		 */
		void cls();

		/** @brief draw a character on given position out of the active font to the LCD
		 *
		 * @param x x-position of char (top left)
		 * @param y y-position
		 * @param c char to print
		 *
		 */
		void character(uint8_t x, uint8_t y, uint8_t c);

		/** @brief set top left position of char/printf
		 *
		 * @param x x-position
		 * @param y y-position
		 *
		 */
		void locate(uint8_t x, uint8_t y);

		/** @brief select the font to use
		 *
		 * @param f pointer to font array
		 *
		 *   font array can created with GLCD Font Creator from http://www.mikroe.com
		 *   you have to add 4 parameter at the beginning of the font array to use:
		 *   - the number of byte / char
		 *   - the vertial size in pixel
		 *   - the horizontal size in pixel
		 *   - the number of byte per vertical line
		 *   you also have to change the array to char[]
		 * @code
		 * lcd.font((unsigned char*)Small_7);
		 * @endcode
		 */
		void font(uint8_t *f);

		/** @brief print bitmap to buffer
		 *
		 * @param bm Bitmap in flash
		 * @param x  x start
		 * @param y  y start
		 *
		 */
		void bitmap(Bitmap bm, int x, int y);

	protected:

		/** @brief stream class, put a char on the screen
		 *
		 * @param value char to print
		 * @returns printed char
		 *
		 */
		virtual int _putc(int value);

		/** @brief stream class, dummy
		 *
		 */
		virtual int _getc();

		/** @brief init the C12832A1Z LCD
		 *
		 */
		void init();

		/** @brief write data to the LCD controller
		 *
		 * @param dat data written to LCD controller
		 *
		 */
		void write_data(uint8_t data);

		/** @brief write a command the LCD controller
		 *
		 * @param cmd command to be written
		 *
		 */
		void write_command(uint8_t command); // Write a command the LCD controller

		// declarations
		SPI _spi;
		DigitalOut _reset;
		DigitalOut _a0;
		DigitalOut _cs;

		// Variables
		uint8_t *font_buffer;
		uint8_t char_x;
		uint8_t char_y;
		uint8_t auto_update;
		uint8_t orientation;
		uint8_t graphic_buffer[512];

	};

#endif

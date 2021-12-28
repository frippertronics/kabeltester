#include "kabeltester/i2c.h"
#include "kabeltester/serial.h"

#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#define DISPLAY_TWI_ADDRESS (0x27U)

#define SHIFTED_DISPLAY_ADDRESS (DISPLAY_TWI_ADDRESS << 1U)
#define DELAY_US (600U)

void lcd_init(void);

// Reset all output pins and set the address
void DISPLAY_Setup(void)
{
    char message[] = "Initialising display \n";
    SERIAL_SendMessage(message, ARRAY_LEN(message));
    i2c_init();
    lcd_init();
}

/* Example code to drive a 16x2 LCD panel via a I2C bridge chip (e.g. PCF8574)
   NOTE: The panel must be capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefor I2C) cannot be used at 5v.
   You will need to use a level shifter on the I2C lines if you want to run the
   board at 5v, otherwise it will still work, but it will be dimmer than usual.
   Connections on Raspberry Pi Pico board, other boards may vary.
   GPIO 4 (pin 6)-> SDA on LCD bridge board
   GPIO 5 (pin 7)-> SCL on LCD bridge board
   3.3v (pin 36) -> VCC on LCD bridge board
   GND (pin 38)  -> GND on LCD bridge board
*/
// commands
const int LCD_CLEARDISPLAY = 0x01;
const int LCD_RETURNHOME = 0x02;
const int LCD_ENTRYMODESET = 0x04;
const int LCD_DISPLAYCONTROL = 0x08;
const int LCD_CURSORSHIFT = 0x10;
const int LCD_FUNCTIONSET = 0x20;
const int LCD_SETCGRAMADDR = 0x40;
const int LCD_SETDDRAMADDR = 0x80;

// flags for display entry mode
const int LCD_ENTRYSHIFTINCREMENT = 0x01;
const int LCD_ENTRYLEFT = 0x02;

// flags for display and cursor control
const int LCD_BLINKON = 0x01;
const int LCD_CURSORON = 0x02;
const int LCD_DISPLAYON = 0x04;

// flags for display and cursor shift
const int LCD_MOVERIGHT = 0x04;
const int LCD_DISPLAYMOVE = 0x08;

// flags for function set
const int LCD_5x10DOTS = 0x04;
const int LCD_2LINE = 0x08;
const int LCD_8BITMODE = 0x10;

// flag for backlight control
const int LCD_BACKLIGHT = 0x08;

const int LCD_ENABLE_BIT = 0x04;

// Modes for lcd_send_byte
#define LCD_CHARACTER  1
#define LCD_COMMAND    0

#define MAX_LINES      4
#define MAX_CHARS      20

/* Quick helper function for single byte transfers */
void i2c_write_byte(uint8_t val) {
    char retval = i2c_start(SHIFTED_DISPLAY_ADDRESS + I2C_WRITE);
    char message[] = "\n\r I2C start status: ";
    SERIAL_SendMessageWithInteger(message, ARRAY_LEN(message), retval);

    char message2[] = "\n\r Sending I2C value:";
    SERIAL_SendMessageWithInteger(message2, ARRAY_LEN(message2), val);
    retval = i2c_write(val);
    
    i2c_stop();
}

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
    _delay_us(DELAY_US);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    _delay_us(DELAY_US);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
    _delay_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t val, int mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

// go to location on LCD
void lcd_set_cursor(int line, int position) {
    int line_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    int val = 0x80 + line_offsets[line] + position;
    lcd_send_byte(val, LCD_COMMAND);
}

static void inline lcd_char(char val) {
    lcd_send_byte(val, LCD_CHARACTER);
}

void lcd_string(const char *s) {
    while (*s) {
        lcd_char(*s++);
    }
}

void lcd_init(void) {
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x02, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}

void DISPLAY_test(void) {
    char start_message[] = "Testing display \n";
    SERIAL_SendMessage(start_message, ARRAY_LEN(start_message));
    static char* message[] =
            {
                    "RP2040 by", "Raspberry Pi",
                    "A brand new", "microcontroller",
                    "Twin core M0", "Full C SDK",
                    "More power in", "your product",
                    "More beans", "than Heinz!","  ","  "
            };

    for (int m = 0; m < sizeof(message) / sizeof(message[0]); m += MAX_LINES) {
        for (int line = 0; line < MAX_LINES; line++) {
            lcd_set_cursor(line, (MAX_CHARS / 2) - strlen(message[m + line]) / 2);
            lcd_string(message[m + line]);
        }
        _delay_ms(4000);
        lcd_clear();
    }
    char new_message[] = "Display test done \n";
    SERIAL_SendMessage(new_message, ARRAY_LEN(new_message));
}
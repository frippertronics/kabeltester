#include "kabeltester/i2c.h"
#include "kabeltester/serial.h"
#include "kabeltester/display.h"

#include "display_commands.h"

#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#define DISPLAY_TWI_ADDRESS (0x27U)
#define INT_TO_ASCII_OFFSET (48U)

#define SHIFTED_DISPLAY_ADDRESS (DISPLAY_TWI_ADDRESS << 1U)
#define DELAY_US (600U)
#define MAX_CHAR_ARRAY_SIZE (100U)

#define MAX_LINES      4
#define MAX_CHARS      20

static char PinToLkMap[37U] = {
    'E', 'F', 'A', 'B', 'C', 'G', 'H', 'J',
    'D', 'S', 'T', 'K', 'L', 'M', 'U', 'V',
    'W', 'N', 'P', 'R', 'X', 'a', 'b', 'g',
    'c', 'd', 'j', 'e', 'f', 'm', 'n', 'p',
    'h', 'r', 's', 'k', 'z',
};


/* Quick helper function for single byte transfers */
static void I2C_WriteByte(uint8_t val) {
    (void) I2C_Start(SHIFTED_DISPLAY_ADDRESS + I2C_WRITE);
    (void) I2C_Write(val);
    I2C_Stop();
    // Small write delay to prevent garbage data on the display
    _delay_us(DELAY_US);
}

static void LCD_ToggleEnable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
    _delay_us(DELAY_US);
    I2C_WriteByte(val | LCD_ENABLE_BIT);
    _delay_us(DELAY_US);
    I2C_WriteByte(val & ~LCD_ENABLE_BIT);
    _delay_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
static void LCD_SendByte(uint8_t val, int mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    I2C_WriteByte(high);
    LCD_ToggleEnable(high);
    I2C_WriteByte(low);
    LCD_ToggleEnable(low);
}

static void LCD_SetCursor(int line, int position) {
    int line_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    int val = 0x80 + line_offsets[line] + position;
    LCD_SendByte(val, LCD_COMMAND);
}

static void inline LCD_SendChar(char val) {
    LCD_SendByte(val, LCD_CHARACTER);
}

static void LCD_SendString(const char *s) {
    while (*s) {
        LCD_SendChar(*s++);
    }
}

static void LCD_Init(void) {
    LCD_SendByte(0x03, LCD_COMMAND);
    LCD_SendByte(0x03, LCD_COMMAND);
    LCD_SendByte(0x03, LCD_COMMAND);
    LCD_SendByte(0x02, LCD_COMMAND);

    LCD_SendByte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    LCD_SendByte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    LCD_SendByte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    DISPLAY_Clear();
}

void DISPLAY_Setup(void)
{
    I2C_Init();
    LCD_Init();
}

void DISPLAY_Clear(void) 
{
    LCD_SendByte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

void DISPLAY_PrintMessage(char* message, uint8_t line, uint8_t offset)
{
    LCD_SetCursor(line, offset);
    LCD_SendString(message);
}

void DISPLAY_PrintWelcomeMessage(void)
{
    LCD_SetCursor(1, 2);
    LCD_SendString("LK37-kabeltester");
    LCD_SetCursor(3, 0);
    LCD_SendString("-Beiken og Tak, 2021");
    _delay_ms(2000U);
    DISPLAY_Clear();
}

void DISPLAY_PrintIntegerArray(uint8_t* integerArray, uint8_t numElements, uint8_t line)
{
    // Convert integer array to character array
    if (numElements < MAX_CHAR_ARRAY_SIZE)
    {
        // Create a buffer array of spaces
        char charArray[MAX_CHAR_ARRAY_SIZE];
        memset(charArray, 32U, MAX_CHAR_ARRAY_SIZE);

        int charArrayCount = 0U;
        for(int i = 0; i < numElements; i++)
        {
            charArray[charArrayCount] = PinToLkMap[integerArray[i]];
            charArrayCount += 2U;
        }
        // Print the characters on the display, changing lines if necessary
        for(int charNum = 0; charNum < (4 * MAX_CHARS); charNum+=MAX_CHARS)
        {
            uint8_t printLine = line + (charNum / MAX_CHARS);
            if (printLine < MAX_LINES)
            {
                LCD_SetCursor(printLine, 0U);
                for(int i = 0; i < MAX_CHARS; i++)
                {
                    LCD_SendChar(charArray[charNum + i]);
                }
            }
        }
    }
}

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <stdlib.h>

#include "kabeltester/serial.h"

#define MAX_STRING_LENGTH (30)

static char s_SerialBuffer[255] = {0U};
static volatile uint8_t s_SerialBufferIndex = 0U;

static inline void SERIAL_EnableUartInterrupt(void)
{
    UCSR0B |= (1<<UDRIE0);
}

static inline void SERIAL_ClearUartInterrupt(void)
{
    UCSR0B &= ~(1<<UDRIE0);
}

inline void SERIAL_PrintLetter(void)
{
    SERIAL_ClearUartInterrupt();
    char character = s_SerialBuffer[s_SerialBufferIndex];
    if (character != '\0')
    {
        UDR0 = character;
        s_SerialBufferIndex++;
        SERIAL_EnableUartInterrupt();
    }
}

void SERIAL_Setup(void)
{
    // Enable transmit
    UCSR0B |= (1 << TXEN0);
    // Set character data size to 8
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
    // Set baud rate to 9600
    UBRR0 = 103U;
}

void SERIAL_SendMessage(char* pString, uint8_t string_len)
{
    (void) memcpy(s_SerialBuffer, pString, string_len);
    s_SerialBufferIndex = 0U;
    SERIAL_EnableUartInterrupt();
    _delay_ms(50);
}

void SERIAL_SendMessageWithInteger(char* pString, uint8_t string_len, int integer)
{
    SERIAL_SendMessage(pString, string_len);
    itoa(integer, pString, 10);
    SERIAL_SendMessage(pString, string_len);
}
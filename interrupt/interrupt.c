#include <avr/io.h>
#include <avr/interrupt.h>

#include "kabeltester/interrupt.h"
#include "kabeltester/serial.h"

void INT_Setup(void)
{
    sei();
}

// Serial printing
ISR(USART0_UDRE_vect){
    SERIAL_PrintLetter();
}
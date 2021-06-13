#include <avr/io.h>
#include <util/delay.h>

#include "kabeltester/gpio.h"

void GPIO_Setup(void)
{
    DDRB |= 1 << PINB7;
}

void GPIO_TogglePin(void)
{ 
    PORTB ^= 1 << PINB7;
    _delay_ms(1000);
}
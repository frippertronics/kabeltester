#include "kabeltester/gpio.h"
#include "kabeltester/interrupt.h"
#include "kabeltester/serial.h"

#include <util/delay.h>

#define ARRAY_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

void init(void)
{
    // Modules
    GPIO_Setup();
    SERIAL_Setup();

    // Enable interrupts last to avoid funky behaviour
    INT_Setup();
}

int main(void)
{
    init();
    char hello_world[] = "Hello world! \n";
    SERIAL_SendMessage(hello_world, ARRAY_LEN(hello_world));
    while(1)
    {
        GPIO_ToggleSanityLED();
        _delay_ms(1000);
    }
}
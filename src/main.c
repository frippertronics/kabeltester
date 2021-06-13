#include "kabeltester/gpio.h"
#include "kabeltester/interrupt.h"
#include "kabeltester/serial.h"

void init(void)
{
    // Modules
    GPIO_Setup();
    SERIAL_Setup();
    INT_Setup();
}

int main(void)
{
    init();
    SERIAL_SetMessage();
    while(1)
    {
        GPIO_TogglePin();
    }
}
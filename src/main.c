#include "kabeltester/gpio.h"

int main(void)
{
    GPIO_Setup();
    while(1)
    {
        GPIO_TogglePin();
    }
}
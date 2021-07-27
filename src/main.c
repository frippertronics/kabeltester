#include "kabeltester/gpio.h"
#include "kabeltester/interrupt.h"
#include "kabeltester/serial.h"
#include "kabeltester/tester.h"

#include <util/delay.h>

void init(void)
{
    // Modules
    GPIO_Setup();
    SERIAL_Setup();
    TESTER_Setup();

    // Enable interrupts last to avoid funky behaviour
    INT_Setup();
}

int main(void)
{
    init();
    PIN_STATUS_E test_results[NUM_TESTER_INPUT_PINS];
    TESTER_TestLk37(test_results);
    while(1)
    {
        GPIO_ToggleSanityLED();
        _delay_ms(1000);
    }
}
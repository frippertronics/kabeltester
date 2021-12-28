#include "kabeltester/gpio.h"
#include "kabeltester/interrupt.h"
#include "kabeltester/serial.h"
#include "kabeltester/tester.h"
#include "kabeltester/display.h"

#include <util/delay.h>

static void init(void)
{
    // Modules
    GPIO_Setup();
    SERIAL_Setup();
    TESTER_Setup();
    DISPLAY_Setup();

    // Enable interrupts last to avoid funky behaviour
    INT_Setup();
}

int main(void)
{
    init();
    DISPLAY_PrintWelcomeMessage();
    TEST_RESULTS_T test_results[NUM_PINS_LK37];
    (void) TESTER_TestLk37(test_results);

    while(1)
    {
        GPIO_ToggleSanityLED();
        _delay_ms(1000);
    }
}
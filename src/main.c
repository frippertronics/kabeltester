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
    //DISPLAY_Setup();

    // Enable interrupts last to avoid funky behaviour
    INT_Setup();
}

int main(void)
{
    init();
    //TEST_RESULTS_T test_results[NUM_TESTER_INPUT_PINS];
    //TESTER_TestLk37(test_results);

    char message[] = "Testing display \n";
    SERIAL_SendMessage(message, ARRAY_LEN(message));
    DISPLAY_Setup();
    DISPLAY_test();
    char new_message[] = "Display test done \n";
    SERIAL_SendMessage(new_message, ARRAY_LEN(new_message));
    while(1)
    {
        GPIO_ToggleSanityLED();
        _delay_ms(1000);
    }
}
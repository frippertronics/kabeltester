#include "kabeltester/tester.h"
#include "kabeltester/gpio.h"
#include "kabeltester/serial.h"

#include "hardware/util.h"

#include <stdlib.h>
#include <string.h>

#define NUM_PINS_PER_MUX (8)

// A mux is enabled by resetting the DISABLE signal
static void TESTER_EnableMux(MUX_SELECT_E mux)
{
    GPIO_ClearMuxDisablePin(mux);
}

static void TESTER_SetMuxChannel(uint8_t channel)
{
    // Convert form Uint8_t to 3 bit (pins)
    for(uint8_t bit = 0; bit < NUM_MUX_CONTROL_PINS; bit++)
    {
        bool pin_enabled = ((channel & (1U << bit)) != 0U);
        if(pin_enabled)
        {
            GPIO_SetMuxControlPin((MUX_CONTROL_E) bit);
        }
        else
        {
            GPIO_ClearMuxControlPin((MUX_CONTROL_E) bit);
        }
    }
    // Wait for mux to switch and settle
    _delay_ms(1);
}

static void TESTER_DisableMux(MUX_SELECT_E mux)
{
    GPIO_SetMuxDisablePin(mux);
}

static void TESTER_CheckPin(TESTER_PINS_E pin_to_check, TEST_RESULTS_T* pin_test_results)
{
    // Cycle through all pins.
    // If only the target pin is high, it's ok
    // If other pins are high, it is shorted
    // If no pins are high, it is open
    char message[] = "\n\r Checking pin: ";
    SERIAL_SendMessageWithInteger(message, ARRAY_LEN(message), pin_to_check);
    
    uint8_t short_pin_count = 0U;
    pin_test_results->pin_status = OPEN;
    for (TESTER_PINS_E pin = PIN_E; pin < NUM_TESTER_INPUT_PINS; pin++)
    {
        uint8_t current_pin_level = GPIO_ReadTesterPin(pin);
        if(current_pin_level == 1U)
        {
            if(pin != pin_to_check)
            {
                pin_test_results->pin_status |= SHORTED;
                if (short_pin_count < NUM_SHORT_PINS_TO_STORE)
                {
                    pin_test_results->short_pins[short_pin_count] = pin;
                    short_pin_count++;
                }

                char message[] = "\n\r Short: ";
                SERIAL_SendMessageWithInteger(message, ARRAY_LEN(message), pin);
            }
            else
            {
                pin_test_results->pin_status |= OK;
                char message[] = "\n\r OK";
                SERIAL_SendMessage(message, ARRAY_LEN(message));
            }
        }
        else if (pin == pin_to_check)
        {
            char message[] = "\n\r OPEN";
            SERIAL_SendMessage(message, ARRAY_LEN(message)); 
        }
        else
        {
            // Do nothing. This is the expected response for all inactive pins.
        }
    }
}

// Reset all output pins
void TESTER_Setup(void)
{
    for(MUX_CONTROL_E control_pin = MUX_A; control_pin < NUM_MUX_CONTROL_PINS; control_pin++)
    {
        GPIO_ClearMuxControlPin(control_pin);
    }

    for(MUX_SELECT_E disable_pin = MUX_S1; disable_pin < NUM_MUX_DISABLE_PINS; disable_pin++)
    {
        GPIO_SetMuxDisablePin(disable_pin);
    }
}

// Test a 37-pin LK37 cable. 
// The function expects an array of test results
// with at least 37 elements.
bool TESTER_TestLk37(TEST_RESULTS_T* test_results)
{
    bool error = false;
    uint8_t current_pin = PIN_E;

    char message[] = "Testing LK37 \n";
    SERIAL_SendMessage(message, ARRAY_LEN(message));

    // Reset all control pins and disable all muxes to ensure clean 
    TESTER_Setup();

    // Cycle through each mux and set each channel
    for(MUX_SELECT_E mux = MUX_S1; mux < NUM_MUX_DISABLE_PINS; mux++)
    {
        TESTER_EnableMux(mux);
        for(uint8_t mux_channel = 0U; mux_channel < NUM_PINS_PER_MUX; mux_channel++)
        {   
            // Test pins until all pins have been tested (pin 37)
            if (current_pin < NUM_TESTER_INPUT_PINS)
            {
                TEST_RESULTS_T pin_test_results;
                TESTER_SetMuxChannel(mux_channel);
                TESTER_CheckPin(current_pin, &pin_test_results);
                (void) memcpy(&test_results[current_pin], &pin_test_results, sizeof(TEST_RESULTS_T));
                current_pin++;
            }
            else
            {
                break;
            }
        }
        TESTER_DisableMux(mux);
    }
    // Quickly check results
    for(int i = 0; i < NUM_TESTER_INPUT_PINS; i++)
    {
        error |= (test_results[i].pin_status != OK);
    }
    if(error)
    {
        char message[] = "\n\r Cable is broken \n";
        SERIAL_SendMessage(message, ARRAY_LEN(message));
    }
    else
    {
        char message[] = "\n\r Cable is OK \n";
        SERIAL_SendMessage(message, ARRAY_LEN(message));
    }

    return(error);
}
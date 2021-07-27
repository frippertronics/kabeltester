#include "kabeltester/tester.h"
#include "kabeltester/gpio.h"
#include "kabeltester/serial.h"

#include <stdlib.h>

#define NUM_PINS_PER_MUX (8)

static void TESTER_SelectMux(MUX_SELECT_E mux)
{
    GPIO_SetMuxSelectPin(mux);
}

static void TESTER_SelectMuxChannel(uint8_t channel)
{
    // Convert form Uint8_t to 3 bit (pins)
    for(int bit = 0; bit < NUM_MUX_CONTROL_PINS; bit++)
    {
        bool pin_enabled = ((channel & (1 << bit)) == true);
        if(pin_enabled)
        {
            GPIO_SetMuxControlPin((MUX_CONTROL_E) bit);
        }
        else
        {
            GPIO_ClearMuxControlPin((MUX_CONTROL_E) bit);
        }
    }
}

static void TESTER_ClearMux(MUX_SELECT_E mux)
{
    GPIO_ClearMuxSelectPin(mux);
    for(MUX_CONTROL_E control_pin = 0; control_pin < NUM_MUX_CONTROL_PINS; control_pin++)
    {
        GPIO_ClearMuxControlPin(control_pin);
    }
}

static PIN_STATUS_E TESTER_CheckPin(TESTER_PINS_E pin_to_check)
{
    PIN_STATUS_E pin_status = OPEN;
    // Cycle through all pins.
    // If only the target pin is high, it's ok
    // If other pins are high, it is shorted
    // If no pins are high, it is open
    char message[] = "\n\r Checking pin: ";
    SERIAL_SendMessage(message, ARRAY_LEN(message));
    itoa(pin_to_check, message, 10);
    SERIAL_SendMessage(message, ARRAY_LEN(message));
    for (TESTER_PINS_E pin = PIN_E; pin < NUM_TESTER_INPUT_PINS; pin++)
    {
        uint8_t current_pin_level = GPIO_ReadTesterPin(pin);
        if(current_pin_level != 0U)
        {
            if(pin != pin_to_check)
            {
                pin_status |= SHORTED;
                char message[] = "\n\r Short: ";
                SERIAL_SendMessage(message, ARRAY_LEN(message));
                itoa(pin, message, 10);
                SERIAL_SendMessage(message, ARRAY_LEN(message));
            }
            else
            {
                pin_status |= OK;
            }
        }
    }
    char message2[] = "\n\r Pin status: ";
    SERIAL_SendMessage(message2, ARRAY_LEN(message2));
    itoa(pin_status, message2, 10);
    SERIAL_SendMessage(message2, ARRAY_LEN(message2));
    return(pin_status);
}


void TESTER_Setup(void)
{
    // Reset all output pins
    for(MUX_CONTROL_E control_pin = 0; control_pin < NUM_MUX_CONTROL_PINS; control_pin++)
    {
        GPIO_ClearMuxControlPin(control_pin);
    }

    for(MUX_SELECT_E select_pin = 0; select_pin < NUM_MUX_SELECT_PINS; select_pin++)
    {
        GPIO_ClearMuxSelectPin(select_pin);
    }
}

bool TESTER_TestLk37(PIN_STATUS_E* pin_results)
{
    bool error = false;
    uint8_t current_pin = PIN_E;

    char message[] = "Testing LK37 \n";
    SERIAL_SendMessage(message, ARRAY_LEN(message));
    // Reset all output pins
    TESTER_Setup();
    // Cycle through each mux and set each channel
    for(MUX_SELECT_E mux = MUX_S1; mux < NUM_MUX_SELECT_PINS; mux++)
    {
        TESTER_SelectMux(mux);
        for(uint8_t mux_channel = 0U; mux_channel < NUM_PINS_PER_MUX; mux_channel++)
        {   
            // Check if the last pin to be tested has been reached
            if (current_pin < NUM_TESTER_INPUT_PINS)
            {
                TESTER_SelectMuxChannel(mux_channel);
                PIN_STATUS_E test_result = TESTER_CheckPin(current_pin);
                pin_results[current_pin] = test_result;
                current_pin++;
            }
            else
            {
                break;
            }
        }
        TESTER_ClearMux(mux);
    }
    // Quickly check results
    for(int i = 0; i < NUM_TESTER_INPUT_PINS; i++)
    {
        error |= (pin_results[i] != OK);
    }
    if(error)
    {
        char message[] = "Cable is broken \n";
        SERIAL_SendMessage(message, ARRAY_LEN(message));
    }
    else
    {
        char message[] = "Cable is OK \n";
        SERIAL_SendMessage(message, ARRAY_LEN(message));
    }

    return(error);
}
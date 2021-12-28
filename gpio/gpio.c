#include <avr/io.h>

#include "kabeltester/gpio.h"
#include "hardware/gpio_pins.h"
#include "kabeltester/serial.h"

static void GPIO_SetPin(volatile uint8_t* pPort, uint8_t pin);
static void GPIO_ClearPin(volatile uint8_t* pPort, uint8_t pin);
typedef enum 
{
    INPUT = 0,
    OUTPUT = 1
} GPIO_DIR_E;

static void GPIO_InitPin(volatile uint8_t* pDdr, uint8_t pin, GPIO_DIR_E direction)
{
    if (direction == OUTPUT)
    {
        *pDdr |= (1 << pin);
    }
    else
    {
        *pDdr &= ~(1 << pin);
    }
}

static void GPIO_InitInputPins(void)
{
    // Cable inputs
    for(int i = 0; i < NUM_TESTER_INPUT_PINS; i++)
    {
        GPIO_InitPin(TESTER_INPUT_PINS[i].ddr, TESTER_INPUT_PINS[i].number, INPUT);
    }

    // Extra inputs
    for(int i = 0; i < NUM_EXTRA_INPUT_PINS; i++)
    {
        GPIO_InitPin(EXTRA_INPUT_PINS[i].ddr, EXTRA_INPUT_PINS[i].number, INPUT);
    }
}

static void GPIO_InitOutputPins(void)
{
    // Mux functionality
    for(int i = 0; i < NUM_MUX_DISABLE_PINS; i++)
    {
        GPIO_InitPin(MUX_DISABLE_PINS[i].ddr, MUX_DISABLE_PINS[i].number, OUTPUT);
    }

    for(int i = 0; i < NUM_MUX_CONTROL_PINS; i++)
    {
        GPIO_InitPin(MUX_CONTROL_PINS[i].ddr, MUX_CONTROL_PINS[i].number, OUTPUT);
    }

    // TWI interface with pull-ups
    for(int i = 0; i < NUM_I2C_PINS; i++)
    {
        GPIO_InitPin(TWI_PINS[i].ddr, TWI_PINS[i].number, OUTPUT);
        GPIO_SetPin(TWI_PINS[i].port, TWI_PINS[i].number);
    }

    // Blinking LED for sanity check
    GPIO_InitPin(&DDRB, PINB7, OUTPUT);
}

static uint8_t GPIO_ReadPin(volatile uint8_t* pPort, uint8_t pin)
{
    uint8_t value = (((*pPort & (1 << pin)) >> pin));
    return(value);
}

static void GPIO_SetPin(volatile uint8_t* pPort, uint8_t pin)
{
    *pPort |= (1 << pin);
}

static void GPIO_ClearPin(volatile uint8_t* pPort, uint8_t pin)
{
    *pPort &= ~(1 << pin);
}

static void GPIO_TogglePin(volatile uint8_t* pPort, uint8_t pin)
{ 
    *pPort ^= 1 << pin;
}

void GPIO_Setup(void)
{
    // Inputs
    GPIO_InitInputPins();

    // Outputs
    GPIO_InitOutputPins();
}

uint8_t GPIO_ReadTesterPin(TESTER_PINS_E tester_pin)
{
    GPIO_PIN_T pin_info = TESTER_INPUT_PINS[tester_pin];
    uint8_t pin_value = GPIO_ReadPin(pin_info.port, pin_info.number);
    return(pin_value);
}

void GPIO_SetMuxDisablePin(MUX_SELECT_E mux_disable)
{
    GPIO_PIN_T pin_info = MUX_DISABLE_PINS[mux_disable];
    GPIO_SetPin(pin_info.port, 
                pin_info.number);
}

void GPIO_ClearMuxDisablePin(MUX_SELECT_E mux_disable)
{
    GPIO_PIN_T pin_info = MUX_DISABLE_PINS[mux_disable];
    GPIO_ClearPin(pin_info.port, 
                  pin_info.number);
}

void GPIO_SetMuxControlPin(MUX_CONTROL_E mux_control)
{
    GPIO_PIN_T pin_info = MUX_CONTROL_PINS[mux_control];
    GPIO_SetPin(pin_info.port, 
                pin_info.number);
}

void GPIO_ClearMuxControlPin(MUX_CONTROL_E mux_control)
{
    GPIO_PIN_T pin_info = MUX_CONTROL_PINS[mux_control];
    GPIO_ClearPin(pin_info.port, 
                  pin_info.number);
}

void GPIO_ToggleSanityLED()
{
    GPIO_TogglePin(&PORTB, PINB7);
}
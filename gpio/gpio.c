#include <avr/io.h>

#include "kabeltester/gpio.h"

#define PORT_A_PTR (&DDRA)
#define PORT_B_PTR (&DDRB)
#define PORT_C_PTR (&DDRC)
#define PORT_D_PTR (&DDRD)
#define PORT_E_PTR (&DDRE)
#define PORT_F_PTR (&DDRF)
#define PORT_G_PTR (&DDRG)
#define PORT_H_PTR (&DDRH)
#define PORT_I_PTR (&DDRI)
#define PORT_J_PTR (&DDRJ)
#define PORT_K_PTR (&DDRK)
#define PORT_L_PTR (&DDRL)

typedef struct
{
    volatile uint8_t* bank;
    uint8_t number;
} GPIO_PIN_T;

typedef enum 
{
    INPUT = 0,
    OUTPUT = 1
} GPIO_DIR_E;

// INPUT PINS
static const GPIO_PIN_T TESTER_INPUT_PINS[NUM_TESTER_INPUT_PINS] = {
    {PORT_F_PTR, PINF0}, // Input 0 (E)
    {PORT_F_PTR, PINF1}, // Input 1 (F)
    {PORT_F_PTR, PINF2}, // Input 2 (A)
    {PORT_F_PTR, PINF3}, // Input 3 (B)
    {PORT_F_PTR, PINF4}, // Input 4 (C)
    {PORT_F_PTR, PINF5}, // Input 5 (G)
    {PORT_F_PTR, PINF6}, // Input 6 (H)
    {PORT_F_PTR, PINF7}, // Input 7 (J)

    {PORT_K_PTR, PINK0}, // Input 8 (D)
    {PORT_K_PTR, PINK1}, // Input 9 (S)
    {PORT_K_PTR, PINK2}, // Input 10 (T)
    {PORT_K_PTR, PINK3}, // Input 11 (K)
    {PORT_K_PTR, PINK4}, // Input 12 (L)
    {PORT_K_PTR, PINK5}, // Input 13 (M)
    {PORT_K_PTR, PINK6}, // Input 14 (U)
    {PORT_K_PTR, PINK7}, // Input 15 (V)

    {PORT_A_PTR, PINA4}, // Input 16 (W)
    {PORT_A_PTR, PINA5}, // Input 17 (N)
    {PORT_A_PTR, PINA6}, // Input 18 (P)
    {PORT_A_PTR, PINA7}, // Input 19 (R)

    {PORT_C_PTR, PINC7}, // Input 20 (X)
    {PORT_C_PTR, PINC6}, // Input 21 (a)
    {PORT_C_PTR, PINC5}, // Input 22 (b)
    {PORT_C_PTR, PINC4}, // Input 23 (g)
    {PORT_C_PTR, PINC3}, // Input 24 (c)
    {PORT_C_PTR, PINC2}, // Input 25 (d)
    {PORT_C_PTR, PINC1}, // Input 26 (j)
    {PORT_C_PTR, PINC0}, // Input 27 (e)

    {PORT_D_PTR, PIND7}, // Input 28 (f)

    {PORT_G_PTR, PING2}, // Input 29 (m)
    {PORT_G_PTR, PING1}, // Input 30 (n)
    {PORT_G_PTR, PING0}, // Input 31 (p)

    {PORT_L_PTR, PINL7}, // Input 32 (h)
    {PORT_L_PTR, PINL6}, // Input 33 (r)
    {PORT_L_PTR, PINL5}, // Input 34 (s)
    {PORT_L_PTR, PINL4}, // Input 35 (k)
    {PORT_L_PTR, PINL3}, // Input 36 (z)
};

static const GPIO_PIN_T EXTRA_INPUT_PINS[NUM_EXTRA_INPUT_PINS] = {
    {PORT_L_PTR, PINL2}, // Input 37
    {PORT_L_PTR, PINL1}, // Input 38
    {PORT_L_PTR, PINL0}, // Input 39
};

// OUTPUT PINS
static const GPIO_PIN_T MUX_SELECT_PINS[NUM_MUX_SELECT_PINS] = {
    {PORT_H_PTR, PINH6}, // MuxS 1
    {PORT_H_PTR, PINH5}, // MuxS 2
    {PORT_H_PTR, PINH4}, // MuxS 3
    {PORT_H_PTR, PINH3}, // MuxS 4
    {PORT_E_PTR, PINE3}, // MuxS 5
};

static const GPIO_PIN_T MUX_CONTROL_PINS[NUM_MUX_CONTROL_PINS] = {
    {PORT_E_PTR, PINE4}, // Mux A
    {PORT_E_PTR, PINE5}, // Mux B
    {PORT_G_PTR, PING5}, // Mux C
}; 

static void GPIO_InitPin(volatile uint8_t* pPort, uint8_t pin, GPIO_DIR_E direction)
{
    if (direction == OUTPUT)
    {
        *pPort |= (1 << pin);
    }
    else
    {
        *pPort &= ~(1 << pin);
    }
}

static void GPIO_InitInputPins(void)
{
    // Cable inputs
    for(int i = 0; i < NUM_TESTER_INPUT_PINS; i++)
    {
        GPIO_InitPin(TESTER_INPUT_PINS[i].bank, TESTER_INPUT_PINS[i].number, INPUT);
    }

    // Extra inputs
    for(int i = 0; i < NUM_EXTRA_INPUT_PINS; i++)
    {
        GPIO_InitPin(EXTRA_INPUT_PINS[i].bank, EXTRA_INPUT_PINS[i].number, INPUT);
    }
}

static void GPIO_InitOutputPins(void)
{
    // Mux functionality
    for(int i = 0; i < NUM_MUX_SELECT_PINS; i++)
    {
        GPIO_InitPin(MUX_SELECT_PINS[i].bank, MUX_SELECT_PINS[i].number, OUTPUT);
    }

    for(int i = 0; i < NUM_MUX_CONTROL_PINS; i++)
    {
        GPIO_InitPin(MUX_CONTROL_PINS[i].bank, MUX_CONTROL_PINS[i].number, OUTPUT);
    }

    // Blinking LED for sanity check
    GPIO_InitPin(&DDRB, PINB7, OUTPUT);
}

static uint8_t GPIO_ReadPin(volatile uint8_t* pPort, uint8_t pin)
{
    uint8_t value = *pPort & (1 << pin);
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
    uint8_t pin_value = (GPIO_ReadPin(pin_info.bank,
                         pin_info.number));
    return(pin_value);
}

void GPIO_SetMuxSelectPin(MUX_SELECT_E mux_select)
{
    GPIO_PIN_T pin_info = MUX_SELECT_PINS[mux_select];
    GPIO_SetPin(pin_info.bank, 
                pin_info.number);
}

void GPIO_ClearMuxSelectPin(MUX_SELECT_E mux_select)
{
    GPIO_PIN_T pin_info = MUX_SELECT_PINS[mux_select];
    GPIO_ClearPin(pin_info.bank, 
                  pin_info.number);
}

void GPIO_SetMuxControlPin(MUX_CONTROL_E mux_control)
{
    GPIO_PIN_T pin_info = MUX_CONTROL_PINS[mux_control];
    GPIO_SetPin(pin_info.bank, 
                pin_info.number);
}

void GPIO_ClearMuxControlPin(MUX_CONTROL_E mux_control)
{
    GPIO_PIN_T pin_info = MUX_CONTROL_PINS[mux_control];
    GPIO_ClearPin(pin_info.bank, 
                  pin_info.number);
}

void GPIO_ToggleSanityLED()
{
    GPIO_TogglePin(&PORTB, PINB7);
}
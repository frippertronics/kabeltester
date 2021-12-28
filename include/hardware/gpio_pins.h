#ifndef GPIO_PINS_H
#define GPIO_PINS_H

#include <avr/io.h>

#include "kabeltester/gpio.h"
#include "kabeltester/i2c.h"

#define DDR_A_PTR (&DDRA)
#define DDR_B_PTR (&DDRB)
#define DDR_C_PTR (&DDRC)
#define DDR_D_PTR (&DDRD)
#define DDR_E_PTR (&DDRE)
#define DDR_F_PTR (&DDRF)
#define DDR_G_PTR (&DDRG)
#define DDR_H_PTR (&DDRH)
#define DDR_I_PTR (&DDRI)
#define DDR_J_PTR (&DDRJ)
#define DDR_K_PTR (&DDRK)
#define DDR_L_PTR (&DDRL)

#define PIN_A_PTR (&PINA)
#define PIN_B_PTR (&PINB)
#define PIN_C_PTR (&PINC)
#define PIN_D_PTR (&PIND)
#define PIN_E_PTR (&PINE)
#define PIN_F_PTR (&PINF)
#define PIN_G_PTR (&PING)
#define PIN_H_PTR (&PINH)
#define PIN_I_PTR (&PINI)
#define PIN_J_PTR (&PINJ)
#define PIN_K_PTR (&PINK)
#define PIN_L_PTR (&PINL)

#define PORT_A_PTR (&PORTA)
#define PORT_B_PTR (&PORTB)
#define PORT_C_PTR (&PORTC)
#define PORT_D_PTR (&PORTD)
#define PORT_E_PTR (&PORTE)
#define PORT_F_PTR (&PORTF)
#define PORT_G_PTR (&PORTG)
#define PORT_H_PTR (&PORTH)
#define PORT_I_PTR (&PORTI)
#define PORT_J_PTR (&PORTJ)
#define PORT_K_PTR (&PORTK)
#define PORT_L_PTR (&PORTL)

// Pin information. The bank has to be a volatile pointer as 
// it is set during compilation
typedef struct
{
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    uint8_t number;
} GPIO_PIN_T;

// INPUT PINS
static const GPIO_PIN_T TESTER_INPUT_PINS[NUM_TESTER_INPUT_PINS] = {
    {DDR_F_PTR, PIN_F_PTR, PINF0}, // Input 0 (E)
    {DDR_F_PTR, PIN_F_PTR, PINF1}, // Input 1 (F)
    {DDR_F_PTR, PIN_F_PTR, PINF2}, // Input 2 (A)
    {DDR_F_PTR, PIN_F_PTR, PINF3}, // Input 3 (B)
    {DDR_F_PTR, PIN_F_PTR, PINF4}, // Input 4 (C)
    {DDR_F_PTR, PIN_F_PTR, PINF5}, // Input 5 (G)
    {DDR_F_PTR, PIN_F_PTR, PINF6}, // Input 6 (H)
    {DDR_F_PTR, PIN_F_PTR, PINF7}, // Input 7 (J)

    {DDR_K_PTR, PIN_K_PTR, PINK0}, // Input 8 (D)
    {DDR_K_PTR, PIN_K_PTR, PINK1}, // Input 9 (S)
    {DDR_K_PTR, PIN_K_PTR, PINK2}, // Input 10 (T)
    {DDR_K_PTR, PIN_K_PTR, PINK3}, // Input 11 (K)
    {DDR_K_PTR, PIN_K_PTR, PINK4}, // Input 12 (L)
    {DDR_K_PTR, PIN_K_PTR, PINK5}, // Input 13 (M)
    {DDR_K_PTR, PIN_K_PTR, PINK6}, // Input 14 (U)
    {DDR_K_PTR, PIN_K_PTR, PINK7}, // Input 15 (V)

    {DDR_A_PTR, PIN_A_PTR, PINA4}, // Input 16 (W)
    {DDR_A_PTR, PIN_A_PTR, PINA5}, // Input 17 (N)
    {DDR_A_PTR, PIN_A_PTR, PINA6}, // Input 18 (P)
    {DDR_A_PTR, PIN_A_PTR, PINA7}, // Input 19 (R)

    {DDR_C_PTR, PIN_C_PTR, PINC7}, // Input 20 (X)
    {DDR_C_PTR, PIN_C_PTR, PINC6}, // Input 21 (a)
    {DDR_C_PTR, PIN_C_PTR, PINC5}, // Input 22 (b)
    {DDR_C_PTR, PIN_C_PTR, PINC4}, // Input 23 (g)
    {DDR_C_PTR, PIN_C_PTR, PINC3}, // Input 24 (c)
    {DDR_C_PTR, PIN_C_PTR, PINC2}, // Input 25 (d)
    {DDR_C_PTR, PIN_C_PTR, PINC1}, // Input 26 (j)
    {DDR_C_PTR, PIN_C_PTR, PINC0}, // Input 27 (e)
    
    {DDR_D_PTR, PIN_D_PTR, PIND7}, // Input 28 (f)

    {DDR_G_PTR, PIN_G_PTR, PING2}, // Input 29 (m)
    {DDR_G_PTR, PIN_G_PTR, PING1}, // Input 30 (n)
    {DDR_G_PTR, PIN_G_PTR, PING0}, // Input 31 (p)

    {DDR_L_PTR, PIN_L_PTR, PINL7}, // Input 32 (h)
    {DDR_L_PTR, PIN_L_PTR, PINL6}, // Input 33 (r)
    {DDR_L_PTR, PIN_L_PTR, PINL5}, // Input 34 (s)
    {DDR_L_PTR, PIN_L_PTR, PINL4}, // Input 35 (k)
    {DDR_L_PTR, PIN_L_PTR, PINL3}, // Input 36 (z)
};

static const GPIO_PIN_T EXTRA_INPUT_PINS[NUM_EXTRA_INPUT_PINS] = {
    {DDR_L_PTR, PIN_L_PTR, PINL2}, // Input 37
    {DDR_L_PTR, PIN_L_PTR, PINL1}, // Input 38
    {DDR_L_PTR, PIN_L_PTR, PINL0}, // Input 39
};

// OUTPUT PINS
static const GPIO_PIN_T MUX_DISABLE_PINS[NUM_MUX_DISABLE_PINS] = {
    {DDR_H_PTR, PORT_H_PTR, PINH6}, // MuxS 1
    {DDR_H_PTR, PORT_H_PTR, PINH5}, // MuxS 2
    {DDR_H_PTR, PORT_H_PTR, PINH4}, // MuxS 3
    {DDR_H_PTR, PORT_H_PTR, PINH3}, // MuxS 4
    {DDR_E_PTR, PORT_E_PTR, PINE3}, // MuxS 5
};

static const GPIO_PIN_T MUX_CONTROL_PINS[NUM_MUX_CONTROL_PINS] = {
    {DDR_E_PTR, PORT_E_PTR, PINE4}, // Mux A
    {DDR_E_PTR, PORT_E_PTR, PINE5}, // Mux B
    {DDR_G_PTR, PORT_G_PTR, PING5}, // Mux C
}; 

static const GPIO_PIN_T TWI_PINS[NUM_I2C_PINS] = {
    {DDR_D_PTR, PORT_D_PTR, PIND0}, // TWI SCL
    {DDR_D_PTR, PORT_D_PTR, PIND1}, // TWI SDA
};

#endif //GPIO_PINS_H
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define NUM_TESTER_INPUT_PINS (37)
#define NUM_EXTRA_INPUT_PINS (3)
#define NUM_MUX_CONTROL_PINS (3)
#define NUM_MUX_DISABLE_PINS (5)

// These enums act as abstraction interfaces for the actual
// GPIO pins. The interface expects the GPIO interface to 
// place the I/O pins in the order specified by the enum
typedef enum 
{
    PIN_E = 0, PIN_F, PIN_A,
    PIN_B, PIN_C, PIN_G,
    PIN_H, PIN_J, PIN_D,
    PIN_S, PIN_T, PIN_K,
    PIN_L, PIN_M, PIN_U,
    PIN_V, PIN_W, PIN_N,
    PIN_P, PIN_R, PIN_X,
    PIN_a, PIN_b, PIN_g,
    PIN_c, PIN_d, PIN_j,
    PIN_e, PIN_f, PIN_m,
    PIN_n, PIN_p, PIN_h,
    PIN_r, PIN_s, PIN_k,
    PIN_z,
} TESTER_PINS_E;

typedef enum 
{
    EXTRA_0 = 0, EXTRA_1, EXTRA_2
} EXTRA_PINS_E;

typedef enum
{
    MUX_S1 = 0, MUX_S2, MUX_S3, MUX_S4, MUX_S5
} MUX_SELECT_E;

typedef enum 
{
    MUX_A = 0, MUX_B, MUX_C
} MUX_CONTROL_E;

void GPIO_Setup(void);
void GPIO_ToggleSanityLED(void);
uint8_t GPIO_ReadTesterPin(TESTER_PINS_E tester_pin);
void GPIO_SetMuxDisablePin(MUX_SELECT_E mux_disable);
void GPIO_ClearMuxDisablePin(MUX_SELECT_E mux_disable);
void GPIO_SetMuxControlPin(MUX_CONTROL_E mux_control);
void GPIO_ClearMuxControlPin(MUX_CONTROL_E mux_control);

#endif
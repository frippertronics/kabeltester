#include "kabeltester/twi.h"

#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#define DISPLAY_TWI_ADDRESS (0x27U)

// Reset all output pins
void DISPLAY_Setup(void)
{
    TWI_Setup ();
}



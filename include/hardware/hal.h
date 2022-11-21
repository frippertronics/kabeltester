#ifndef HAL_H
#define HAL_H

#ifndef TEST
#include <avr/io.h>
#include <avr/interrupt.h>
#else
#include "hardware/simulator/interrupt.h"
#include "hardware/simulator/io.h"
#endif //TEST

#endif //HAL_H
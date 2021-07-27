#ifndef TESTER_H
#define TESTER_H

#include <stdbool.h>

typedef enum{
    OPEN,
    OK,
    SHORTED,
    OK_BUT_SHORTED,
} PIN_STATUS_E;

void TESTER_Setup(void);

// Note: This function expects an input array with a length >= 37
bool TESTER_TestLk37(PIN_STATUS_E* pin_results);

#endif //TESTER_H
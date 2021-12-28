#ifndef TESTER_H
#define TESTER_H

#include <stdbool.h>

#include "kabeltester/gpio.h"

#define NUM_PINS_LK37 (37U)
#define NUM_SHORT_PINS_TO_STORE (10U)

typedef enum{
    OPEN,
    OK,
    SHORTED,
    OK_BUT_SHORTED,
} PIN_STATUS_E;

typedef struct{
    PIN_STATUS_E pin_status;
    TESTER_PINS_E short_pins[NUM_SHORT_PINS_TO_STORE];
} TEST_RESULTS_T;

void TESTER_Setup(void);

// Note: This function expects an input array with a length >= 37
bool TESTER_TestLk37(TEST_RESULTS_T* test_results);
void TESTER_DisplayTestResults(bool cableHasErrors, TEST_RESULTS_T* testResultArray);

#endif //TESTER_H
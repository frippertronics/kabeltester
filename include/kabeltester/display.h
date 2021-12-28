#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

void DISPLAY_Setup(void);
void DISPLAY_Clear(void);
void DISPLAY_PrintMessage(char* message, uint8_t line, uint8_t offset);
void DISPLAY_PrintWelcomeMessage(void);
void DISPLAY_PrintIntegerArray(uint8_t* integerArray, uint8_t numElements, uint8_t line);

#endif //DISPLAY_H
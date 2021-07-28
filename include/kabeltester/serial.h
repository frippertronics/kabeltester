#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

#define ARRAY_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

void SERIAL_PrintLetter(void);
void SERIAL_Setup(void);
void SERIAL_SendMessage(char* pString, uint8_t string_len);
void SERIAL_SendMessageWithInteger(char* pString, uint8_t string_len, int integer);


#endif //SERIAL_H
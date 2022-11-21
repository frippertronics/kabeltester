#include "hardware/simulator/io.h"

uint8_t DDRA = 0x01U;
uint8_t DDRB = 0x04U;
uint8_t DDRC = 0x07U;
uint8_t DDRD = 0x0AU;
uint8_t DDRE = 0x0DU;
uint8_t DDRF = 0x10U;
uint8_t DDRG = 0x13U;
uint8_t DDRH = 0x16U;
uint8_t DDRJ = 0x19U;
uint8_t DDRK = 0x1CU;
uint8_t DDRL = 0x1FU;

uint8_t PINA = 0x00U;
uint8_t PINB = 0x03U;
uint8_t PINC = 0x06U;
uint8_t PIND = 0x09U;
uint8_t PINE = 0x0CU;
uint8_t PINF = 0x0FU;
uint8_t PING = 0x12U;
uint8_t PINH = 0x15U;
uint8_t PINJ = 0x18U;
uint8_t PINK = 0x1BU;
uint8_t PINL = 0x1EU;

uint8_t PORTA = 0x02U;
uint8_t PORTB = 0x05U;
uint8_t PORTC = 0x08U;
uint8_t PORTD = 0x0BU;
uint8_t PORTE = 0x0EU;
uint8_t PORTF = 0x11U;
uint8_t PORTG = 0x14U;
uint8_t PORTH = 0x17U;
uint8_t PORTJ = 0x1AU;
uint8_t PORTK = 0x1DU;
uint8_t PORTL = 0x20U;

// Constants
uint8_t UDRIE0 = 5U;
uint8_t TXEN0 = 3U;
uint8_t UCSZ01 = 2U;
uint8_t UCSZ00 = 1U;
// Targets
uint8_t UCSR0B = 0x00U;
uint8_t UCSR0C = 0x00U;
uint8_t UDR0 = 0x00U;
uint8_t UBRR0 = 0x00U;

#ifndef IO_H
#define IO_H

#include <stdint.h>

#define PIN0 (0U)
#define PIN1 (1U)
#define PIN2 (2U)
#define PIN3 (3U)
#define PIN4 (4U)
#define PIN5 (5U)
#define PIN6 (6U)
#define PIN7 (7U)

#define PINA0 (PIN0)
#define PINA1 (PIN1)
#define PINA2 (PIN2)
#define PINA3 (PIN3)
#define PINA4 (PIN4)
#define PINA5 (PIN5)
#define PINA6 (PIN6)
#define PINA7 (PIN7)

#define PINB7 (PIN7)

#define PINC0 (PIN0)
#define PINC1 (PIN1)
#define PINC2 (PIN2)
#define PINC3 (PIN3)
#define PINC4 (PIN4)
#define PINC5 (PIN5)
#define PINC6 (PIN6)
#define PINC7 (PIN7)

#define PIND7 (PIN7)

#define PINE3 (PIN3)
#define PINE4 (PIN4)
#define PINE5 (PIN5)
#define PINE6 (PIN6)

#define PINF0 (PIN0)
#define PINF1 (PIN1)
#define PINF2 (PIN2)
#define PINF3 (PIN3)
#define PINF4 (PIN4)
#define PINF5 (PIN5)
#define PINF6 (PIN6)
#define PINF7 (PIN7)

#define PING0 (PIN0)
#define PING1 (PIN1)
#define PING2 (PIN2)
#define PING3 (PIN3)
#define PING4 (PIN4)
#define PING5 (PIN5)

#define PINH3 (PIN3)
#define PINH4 (PIN4)
#define PINH5 (PIN5)
#define PINH6 (PIN6)

#define PINK0 (PIN0)
#define PINK1 (PIN1)
#define PINK2 (PIN2)
#define PINK3 (PIN3)
#define PINK4 (PIN4)
#define PINK5 (PIN5)
#define PINK6 (PIN6)
#define PINK7 (PIN7)

#define PINL0 (PIN0)
#define PINL1 (PIN1)
#define PINL2 (PIN2)
#define PINL3 (PIN3)
#define PINL4 (PIN4)
#define PINL5 (PIN5)
#define PINL6 (PIN6)
#define PINL7 (PIN7)

extern uint8_t DDRA;
extern uint8_t DDRB;
extern uint8_t DDRC;
extern uint8_t DDRD;
extern uint8_t DDRE;
extern uint8_t DDRF;
extern uint8_t DDRG;
extern uint8_t DDRH;
extern uint8_t DDRJ;
extern uint8_t DDRK;
extern uint8_t DDRL;

extern uint8_t PINA;
extern uint8_t PINB;
extern uint8_t PINC;
extern uint8_t PIND;
extern uint8_t PINE;
extern uint8_t PINF;
extern uint8_t PING;
extern uint8_t PINH;
extern uint8_t PINJ;
extern uint8_t PINK;
extern uint8_t PINL;

extern uint8_t PORTA;
extern uint8_t PORTB;
extern uint8_t PORTC;
extern uint8_t PORTD;
extern uint8_t PORTE;
extern uint8_t PORTF;
extern uint8_t PORTG;
extern uint8_t PORTH;
extern uint8_t PORTJ;
extern uint8_t PORTK;
extern uint8_t PORTL;


extern uint8_t UCSR0B;
extern uint8_t UCSR0C;
extern uint8_t UDRIE0;
extern uint8_t UDR0;
extern uint8_t UBRR0;
extern uint8_t TXEN0;
extern uint8_t UCSZ00;
extern uint8_t UCSZ01;

#endif //IO_H

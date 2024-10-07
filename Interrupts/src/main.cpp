#include <Arduino.h>

ISR(INT0_vect) { PORTB |= (1 << PB5); }    // when INT0 is triggered, turn on led
ISR(INT1_vect) { PORTB &= (~(1 << PB5)); } // when INT1 is triggered, turn off led

void setup() {
    DDRB |= (1 << DDB5);                  // setting pin 13 LED_BUILTIN output
    SREG |= (1 << 7);                     // enabling global interrupts
    EIMSK |= (1 << INT0) | (1 << INT1);   // enabling interrupts INT0 and INT1
    EICRA |= (1 << ISC00) | (1 << ISC01); // trigger interrupt at INT0 at rising edge
    EICRA |= (1 << ISC10) | (1 << ISC11); // trigger interrupt at INT1 at rising edge
}

void loop() {}
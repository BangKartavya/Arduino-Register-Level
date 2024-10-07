#include <Arduino.h>

void setup() { DDRB |= (1 << DDB5); }

void loop() {
    PORTB |= (1 << PB5);
    delay(1000);
    PORTB &= ~(1 << PB5);
    delay(1000);
}
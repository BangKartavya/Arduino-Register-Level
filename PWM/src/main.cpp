#include <Arduino.h>

void setup() {
    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B &= (~(1 << WGM13)); // fast pwm 10 bit

    TCCR1A |= (1 << COM1A1);
    TCCR1A &= (~(1 << COM1A0)); // set pwm mode to non inverting

    TCCR1B |= (1 << CS11) | (1 << CS10);
    TCCR1B &= (~(1 << CS12)); // prescaler = 64

    DDRB |= (1 << DDB1);
}

void loop() {
    for(int i = 0; i < 1024; i++) {
        OCR1A = i;
        delay(2);
    }
    delay(1000);
}
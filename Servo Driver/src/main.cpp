#include <Arduino.h>

void setup() {
    TCCR1A |= (1 << WGM11);
    TCCR1A &= (~(1 << WGM10)); // fast pwm 10-bit TOP = ICR1
    TCCR1B |= (1 << WGM13) | (1 << WGM12);

    TCCR1B |= (1 << CS11);
    TCCR1B &= (~(1 << CS10)) & (~(1 << CS12)); // set prescaler to 8 (freq = 2Mhz TP = 0.5us)

    TCCR1A |= (1 << COM1A1);
    TCCR1A &= (~(1 << COM1A0)); // clear OC1A clear on compare match

    ICR1 = 40000; // 50 Hz signal

    DDRB |= (1 << DDB1);
    pinMode(A0, INPUT);

    Serial.begin(115200);
}

void loop() {
    int val = analogRead(A0);
    Serial.println("Analog Value : " + String(val));
    OCR1A = map(val, 0, 1024, 1000, 5000);
    Serial.println("OCR1A Value : " + String(OCR1A));
}
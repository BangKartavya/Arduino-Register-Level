#include <Arduino.h>

ISR(ADC_vect) {
    Serial.println("ADC : " + String(ADC));
    OCR1A = ADC;
}

void setup() {
    Serial.begin(115200);

    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B &= (~(1 << WGM13));

    TCCR1A |= (1 << COM1A1);
    TCCR1A &= (~(1 << COM1A0));

    TCCR1B |= (1 << CS10) | (1 << CS11);
    TCCR1B &= (~(1 << CS12));

    DDRB |= (1 << DDB1);

    SREG |= (1 << 7); // enable global interrupts

    ADMUX &= (~(1 << REFS1)) & (~(1 << REFS0));         // no reference voltage
    ADMUX &= (~(1 << ADLAR));                           // right adjusted
    ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADATE); // enable ADC, ADC Auto trigger enable, ADC Interrupt Enable
    ADCSRA |= (1 << ADPS2);
    ADCSRA &= (~(1 << ADPS0)) & (~(1 << ADPS1));                                // prescaler = 16
    ADCSRA |= (1 << ADSC);                                                      // start conversion
    ADMUX &= (~(1 << MUX0)) & (~(1 << MUX1)) & (~(1 << MUX2)) & (~(1 << MUX3)); // select A0

    DDRC &= (~(1 << DDC0));

    OCR1A = 512;
}

void loop() {}
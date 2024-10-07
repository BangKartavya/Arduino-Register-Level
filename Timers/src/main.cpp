#include <Arduino.h>

// ISR(TIMER1_OVF_vect) {
//     // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//     PORTB ^= (1 << PB5); // toggle the led
//     TCNT1 = 49910;       // reset timer to 49910 to get 1 second delay again();
// }

ISR(TIMER1_COMPA_vect) {
    TCNT1 = 0;
    OCR1A = 15625;
}

void setup() {
    /*
    DDRB |= (1 << DDB5);
    // pinMode(LED_BUILTIN, OUTPUT);

    SREG = (1 << 7);        // enable global interrupts
    TIMSK1 |= (1 << TOIE1); // enables overflow interrupt
    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13); // set normal waveform generation
    TCCR1B |= (1 << CS10) | (1 << CS12);
    TCCR1B &= (~(1 << CS11)); // set prescaler to 1024
    TCNT1 = 49910;            // 1 second
    */
    Serial.begin(115200);
    SREG = (1 << 7);         // enable global interrupts
    TIMSK1 |= (1 << OCIE1A); // enable compare interrupt for channel A
    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12); // set normal mode
    TCCR1B |= (1 << CS10) | (1 << CS12);
    TCCR1B &= (~(1 << CS11)); // prescaler to be 1024

    TCCR1A |= (1 << COM1A0);
    TCCR1A &= (~(1 << COM1A1)); // set toggle mode

    TCNT1 = 0;
    OCR1A = 15625;

    DDRB = (1 << DDB1);
}

void loop() {}
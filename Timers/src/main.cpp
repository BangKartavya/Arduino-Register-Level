#include <Arduino.h>

unsigned int captured;

ISR(TIMER1_OVF_vect) {
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    PORTB ^= (1 << PB5); // toggle the led
    TCNT1 = 49910;       // reset timer to 49910 to get 1 second delay again();
}

ISR(TIMER1_COMPA_vect) {
    TCNT1 = 0;
    OCR1A = 15625;
}

ISR(TIMER1_CAPT_vect) {
    captured = ICR1;
    Serial.println(captured);
}

void setup() {
    Serial.begin(115200);

    // Timer Overflow
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

    // Timer Compare Channel A

    /*
    SREG = (1 << 7);         // enable global interrupts
    TIMSK1 |= (1 << OCIE1A); // enable compare interrupt for channel A
    TCCR1A &= (~(1 << WGM10)) & (~(1 << WGM11));
    TCCR1B &= (~(1 << WGM12)) & (~(1 << WGM13)); // set normal mode
    TCCR1B |= (1 << CS10) | (1 << CS12);
    TCCR1B &= (~(1 << CS11)); // prescaler to be 1024

    TCCR1A |= (1 << COM1A0);
    TCCR1A &= (~(1 << COM1A1)); // set toggle mode

    TCNT1 = 0;
    OCR1A = 15625;

    DDRB = (1 << DDB1);
    */

    // Timer Capture

    SREG |= (1 << 7);       // enable global interrupts
    TIMSK1 |= (1 << ICIE1); // enable capture interrupt
    TCCR1A &= (~(1 << WGM10)) & (~(1 << WGM11));
    TCCR1B &= (~(1 << WGM12)) & (~(1 << WGM13)); // normal mode

    TCCR1B &= (~(1 << CS11));
    TCCR1B |= (1 << CS10) | (1 << CS12); // prescaler = 1024

    TCNT1 = 0;

    DDRB &= (~(1 << DDB0));

    TCCR1B |= (1 << ICES1); // trigger on rising edge
}

void loop() {}
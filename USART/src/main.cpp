#include <Arduino.h>

unsigned char USART_Receive() {
    while(!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void USART_TxChar(char ch) {
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = ch;
}

void begin() {
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);                                                                 // enable Tx and Rx
    UCSR0C &= (~(1 << UMSEL01)) & (~(1 << UMSEL00)) & (~(1 << UPM01)) & (~(1 << UPM00)) & (~(1 << USBS0)); // Async USART, parity disabled, 1 stop bit

    UCSR0B &= (~(1 << UCSZ02)); // send 8 bits
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

    UCSR0A |= (1 << U2X0); // set double speed

    UBRR0 = 207; // set baud = 9600
}

void setup() {
    begin();
    String s = "Hello World";

    for(auto i : s) { USART_TxChar(i); }
    USART_TxChar('\n');
}

void loop() {}
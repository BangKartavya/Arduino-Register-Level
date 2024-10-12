/*

    ! Communication

    ? Serial -> Less Wire, Larger Distance
    ? Parallel -> Fast, Small Distance

    ? Asynchronous Serial Communication -> No clock

    * UART -> Universal Asynchronous Receiver Transmitter
    * We need some common config

    * Transmission Speed -> Baud Rate -> 9600 bits per sec
    * Speed of one bit = 1/9600 -> 104 us

    * Data Length -> Both devices should have same data length
    * Start and Stop bit -> Start Bit (high to low) Stop bit -> (low to high)

    ! UART in ATMEGA328p

    ? Enable the transmission and reception in usart bit
    * UCSRnB -> USART Control and Status Register n B
    * for example we have USART0. n = 0

    * RXENn -> Receiver Enable n
    * TXENn -> Transmitter Enable n

    * turn them both on

    * UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    ? Set USART Mode

    * UCSRnC -> USART Control and Status Register n C
    * we are usinig USART0 -> n = 0

    * UMSELn1:0 -> USART Mode Select

    * UMSELn1   UMSELn0     Mode
    * 0         0           Asynchronous USART
    * 0         1           Synchronous USART
    * 1         0           (Reserved)
    * 1         1           Master SPI (MSPIM)

    * We need to use Asynchronous USART

    * UCSR0C &= (~(1 << UMSEL01)) & (~(1 << UMSEL00));

    * UPMn1:0 -> Parity Mode

    * UPMn1     UPMn0       Parity Mode
    * 0         0           Disabled
    * 0         1           Reserved
    * 1         0           Enabled, even parity
    * 1         1           Enabled, odd parity

    * we need to disable parity

    * UCSR0C &= (~(1 << UPM01)) & (~(1 << UPM00));

    * USBSn -> Stop Bits

    * USBSn      Stop Bit(s)
    * 0          1-bit
    * 1          2-bit

    * we need to select 1 stop bit
    * UCSR0C &= (~(1 << USBS0));

    ? Set data size for communication

    ? Set the data length to be 8 bits

    * UCSZn -> Character Size Bits (in UCSRnC and USCRnB)

    * UCSZn2    UCSZn1  UCSZn0  Character Size
    * 0         0       0       5-bit
    * 0         0       1       6-bit
    * 0         1       0       7-bit
    * 0         1       1       8-bit
    * 1         0       0       Reserved
    * 1         0       1       Reserved
    * 1         1       0       Reserved
    * 1         1       1       9-bit

    * We need to set it to 8 bits (011)

    * UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    * UCSR0B &= (~(1 << UCSZ02));

    ? set the speed of the transmission

    * U2Xn -> Double the USART Transmission Speed (UCSRnA)

    * 0 -> Normal Speed
    * 1 -> Double Speed
    *
    * UCSR0A |= (1 << U2X0);

    ? set the baud rate

    * UBRRn -> USART Baud Rate Register

    * for baud = 9600 -> put value 103 for UBRR0 = 0 put value 207 for UBRR0 = 1

    * UBRR0 = 207;4

    ? Receive and Transmit Handlers

    * UDRn -> USART I/O Data Register n

    * Read -> RXB
    * Write -> TXB

*/

unsigned char USART_Receive() {
    while(!(UCSR0A & (1 << RXC0))); // wait for receive complete (unread bytes in the buffer)
    return UDR0;
}

void UART_TxChar(char ch) {
    while(!(UCS0A & (1 << UDRE0))); // wait for empty transmit buffer
    UDR0 = ch;
}
/*
    ! ADC working principle

    ? Uses succesive approximation method

    ! ADC in ATMEGA328p

    ? 10 bit

    ! Steps

    ? enable global interrupts

    * SREG = (1 << 7);

    ? Set reference to NO AVCC and input to ADC0

    * ADMUX -> ADC Multiplexer Selection Register

    * REFB1 , REFB0 -> Reference Selection Bits, clearing them turns off internal VREF

    * ADMUX &= (~(1 << REFB1)) & (~(1 << REFB0));

    ? Set data alignemnt in data register

    * ADCL and ADCH -> ADC Data register

    * If ADLAR = 0 -> Lower 8 bits of the ADC will be available in the ADCL register and remaining 2 in ADCH register (Right Adjusted)

    * IF ADLAR = 1 -> Lower 2 bits of the ADC will be available in the ADCL register and remaining 8 in ADCH register (Left Adjusted)

    * Selecting Right Adjusted

    * ADMUX &= (~(1 << ADLAR));

    ? Enable ADC, set prescaler

    * ADCSRA -> ADC Control and status Register A
    * ADEN -> ADC Enable

    * ADCSRA |= (1 << ADEN);

    * ADIE -> ADC Interrupt Enable

    * ADCSRA |= (1 << ADIE);

    * ADADTE -> ADC Automatic Trigger Enable

    * ADCSRA |= (1 << ADADTE);

    * ADPS2:0 -> ADC Prescaler Select Bits

    * ADPS2 ADPS1 ADPS0 Division Factor
    * 0       0       0       2
    * 0       0       1       2
    * 0       1       0       4
    * 0       1       1       8
    * 1       0       0       16
    * 1       0       1       32
    * 1       1       0       64
    * 1       1       1       128

    * For PS = 16 (100) is selected

    * ADCSRA |= (1 << ADPS2);
    * ADCSRA &= (~(1 << ADPS1)) & (~(1 << ADPS0));

    * ADC Conversion Clock = 16MHz/16 = 1MHz

    ? start the conversion

    * ADSC -> ADC Start Conversion

    * ADCSRA |= (1 << ADSC);

    ? Select the channel (A0 - A8)

    * MUX0:3 -> Analog Channel Selection Bits

    * For slecting A0 -> set 0000

    * ADMUX &= (~(1 << MUX0)) & (~(1 << MUX1)) & (~(1 << MUX2)) & (~(1 << MUX3));

    ? implement ISR Interrupt Handler

    * ISR(ADC_vect) {
        user code
    }
*/
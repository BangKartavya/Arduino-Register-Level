/*
    ! PWM -> Pulse Width Modulation

    ? Voltage Regulation in SMPS
    ? Brightness Adjustment of LED's
    ? Speed Control of Motor

    * PWM waves are generated in specific frequencies such that it turn ON and OFF certain devices with high switching speed

    * cycle = Ton + Toff
    * Ton is defined by duty cycle
    * duty cycle is the time wave is on

    * Output voltage = 5V * duty cycle


    ! PWM in Arduino

    ? Channel A of timer 1 to generate pwm of 250KHz

    ! Steps

    ? Set the mode of timer
    * TCCR1A |= (1 << WGM10) | (1 << WGM11);
    * TCCR1B |= (1 << WGM12);
    * TCCR1B &= (~(1 << WGM13)); // set value 0111 -> Fast PWM 10- bit

    ? Set pwm mode

    * COM1A1 and COM1A0 -> Setting inverting or Non Inverting output of PWM for channel A (10 -> Non Inverting 11 -> Inverting)
    * COM1B1 and COM1B0 -> Setting inverting or Non Inverting output of PWM for channel B (10 -> Non Inverting 11 -> Inverting)

    * TCCR1A |= (1 << COM1A1);
    * TCCR1A &= (~(1 << COM1A0));

    ? Set the prescaler for the timer for setting PWM frequency
    * CLK = 16MHz
    * PWM FREQ = 250KHz
    * prescaler = CLK/PWM FREQ = 64 (CS12 -> 0 CS11 -> 1 CS10 -> 1)

    * TCCR1B |= (1 << CS11) | (1 << CS10);
    * TCCR1B &= (1 << CS12);

    ? Configure the output compare pin as output

    * PB1 (pin 9) configured as output
    * DDRB |= (1 << DDB1);

    ? Set the duty cycle
    * in non inverting mode, whatever value in output compare register will be the on time of the wave

    * OCR1A = 512; 50%
    * OCR1A = 1023; 50%
*/
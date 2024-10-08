/*
    ! Timer
    * It is a peripheral of microcontroller

    ? Applications
    * Time delay generation
    * measuring frequency of pulses
    * generating pwm signals
    * triggering external devices or peripherals

    ? timer is a counter which counts time
    * up counting -> counts from 0 to preprogrammed value
    * down counting -> counts from preprogrammed value to 0

    ! Timer Working Principle

    * pre-programed value = 5, goes to maximum value and then falls back to pre-programmed value

    ? whenever timer falls from max to pre-programm value, timer overflow interrupt is generated

    ! Timer Prescalar

    * Timer Clock = SYSTEM_CLK / (PRESCALAR)

    ? Timer Frequency and Time Period

    if prescalar == 1

    TIMER CLOCK = SYSTEM_CLK
    SYSTEM_CLK = 16MHz
    TIME_PERIOD = 1/TIMER CLOCK = 1/16MHz = 62.5 ns -> Time gap between each step

    ! Arduino Timers

    * Timer 0 - 8-BIT
    * Timer 1 - 16-BIT
    * Timer 2 - 8-BIT

     Steps for Timer Overflow Interrupt

    ? Enable global interrupt

    * SREG |= (1 << 7);

    ? enable required timer interrupt

    * TIMSK1 -> Timer/Counter1 Interrupt Mask Register
    * Bit 0 -> TOIE1 -> Timer/Counter1 Overflow Interrupt Enable

    * TIMSK1 |= (1 << TOIE1);

    ? set mode of the timer

    * TCCR1A -> Timer/Counter1 Control Register A
    * Bit 0 -> WGM10 Bit 1 -> WGM11 Waveform Generation Mode
    * For normal mode set both 0

    * TCCR1A &= (~(1 << WGM10)) & (~(1 << WGM11));

    * TTCR1B -> Timer/Counter1 control Register B
    * Bit 3 -> WGM12 Bit 4 -> WGM13 Waveform Generation Mode

    * TCCR1B &= (~(1 << WGM12)) & (~(1 << WGM13));

    ? set the prescalar

    * TCCR1B -> Timer/Counter1 control Register B
    * Bit 0 -> CS10 Bit 1 -> CS11 Bit 2 -> CS12 Clock Select

    * CS12    CS11    CS10  Description
    * 0       0       0     No Clock source (Timer/Counter stopped)
    * 0       0       1     No prescaling (clk/1)
    * 0       1       0     clk/8
    * 0       1       1     clk/64
    * 1       0       0     clk/256
    * 1       0       1     clk/1024

    * for prescalar = 1024

    * TCCR1B |= (1 << CS12) | (1 << CS10);
    * TCCR1B &= (~(1 << CS11));

    ? set the period for the timer

    * System clk = 16MHz
    * Clock freq after prescaling = 16/1024 = 15625 MHz
    * Time for each tick = 1/15625 = 64 us

    * for reaching 1000ms (1 s) delay we need = 1000/64 = 15625 steps

    * to cause an overflow at exactly 15625 steps we need to reach 65535 after 15625 steps
    * therefore pre-programmed step = 65535 - 15625 = 49910

    * TCNT1 ->  Direct access for both reads and writes
    * TCNT1 = 49910; for 1 second

    ? implement the interrupt handler function

    * ISR(TIMER1_OVF_vect) {
        *user code
        ! TCNT1 = 49910; reset the counter
        }
*/

/*
    ! Output Compare of timer register

    * Lets assume the frequency of timer = 15625 Hz (prescaler = 1024)
    * Time Period = 64 us

    * we can load some pre-programmed value in compare register and whenever the timer reaches that value, it will toggle the output compare
    * this creates a pulse of 50% duty cycle and with time period of 2*n*64 us (n = pre-programmed value)

*/

/*
    ! Output Compare Channels

    ? OC0A and OC0B -> Timer 0
    ? OC1A and OC1B -> Timer 1
    ? OC2A -> Timer 2

    ! Steps to implement Output Compare

    ? Enable global interrupts

    * SREG |= (1 << 7);

    ? Enable the required timer interrupt

    * in TIMSK1 register
    * OCIE1A -> output compare A match interrupt Enable
    * OCIE1B -> output compare B match interrupt Enable

    * TIMSK1 |= (1 << OCIE1A);

    ? set mode of the timer
    * set normal mode

    ? set the compare output mode
    * can be set using the bits COM1A0 and COM1A1 or COM1B0 and COM1B1 of TCCR1A Register

    * COM1A1/COM1B1     COM1A0/COM1B0       Description
    * 0                 0                   Normal Port Operation OC1A/OC1B disconnected
    * 0                 1                   Toggle OC1A/OC1B on compare match.
    * 1                 0                   Clear OC1A/OC1B on compare match (set output to low level)
    * 1                 1                   Set OC1A/OC1B on compare match (set output to high level)

    * setting them to toggle

    * TCCR1A |= (1 << COM1A0);
    * TCCR1A &= (~(1 << COM1A1));

    ? set the prescaler for the timer

    * for prescalar = 1024

    * TCCR1B |= (1 << CS12) | (1 << CS10);
    * TCCR1B &= (~(1 << CS11));

    ? start the timer with initial value

    * TCNT1 = 0;

    ? load the period for the timer
    * load the timer start value in OCR1A (since now we are going from 0 to 15625 to get 1 sec pulse (timer will loop back to 0 after this))

    * OCR1A = 15625;

    ? configure the output compare pin as output

    *DDRB |= (1 << DDB1);

    ? implement the ISR function

    *ISR(TIMER1_COMPA_vect) {
        TCNT1 = 0;
        OCR1A = 15625;
    }
 */

/*
    ! Timer Input Capture

    ? Most often used for measuring frequency of signals
    ? The frequency is measured by counting the number of clock pulses appearing

    ? Capture Resgister stores the period of rising edge or falling edge of timer to calculate the frequency
    ? difference between two rising edges or 2 falling edges gives the time period of each pulse, inverse of which gives the frequency

    ! Input Timer Capture in Arduino

    ? Only one input capture channel in ATMEGA328p (ICP1)
    ? Only available in Timer 1 (16 bit timer)

    ! Steps

    ? Enable the global interrupts

    * SREG = (1 << 7);

    ? Enable the required timer interrupt

    * ICIE1 -> Timer/Counter 1, Input Capture Interrupt Enable

    * TIMSK1 |= (1 << ICIE1);

    ? Set mode of the timer

    * TCCR1A &= (~(1 << WGM10)) & (~(1 << WGM11));
    * TCCR1B &= (~(1 << WGM12)) & (~(1 << WGM13));

    ? set the prescaler

    * TCCR1B |= (1 << CS10) | (1 << CS12);
    * TCCR1B &= (~(1 << CS11));

    ? start the timer with initial value

    * TCNT1 = 0;

    ? select edge for capturing

    * ICES1 -> Input Capture Edge Select

    * ICES1 = 0 -> Falling edge
    * ICES1 = 1 -> Rising edge

    * TCCR1B |= (1 << ICES1);

    ? Implement the ISR function
    * ICR1 -> Stores the value of TCNT1 during the interrupt

    unsigned int captured;
    * ISR(TIMER1_CAPT_vect) {
        captured = ICR1;
    }

*/
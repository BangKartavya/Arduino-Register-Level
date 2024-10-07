/*
    ! Interrupts

    ? Software
    ? Hardware

    * Hardware Interrupts -> provided from external sources (eg external interrupt)

    * Software Interrupts -> provided from internal sources (ADC interrupt, TIMER interrupt, USART interrupt)

    ! External Interrupts

    ? SREG -> Interrupt status register
    * Bit 7 -> global interrupt enable bit

    ? EMISK -> External Interrupt mask register
    * Bit 0 -> INT1, Bit 1 -> INT2

    ? EICRA -> External Interrupt control register A
    * 4 bits -> ISC00, ISC01, ISC10, ISC11

    ! ISC00 and ISC01 -> sense control INT0
    ISC01           ISC00       Description
    0               0           Low level of INT0 Generates Interrupt
    0               1           Any Change in INT0 Generates Interrupt
    1               0           Falling Edge of INT0 Generates Interrupt
    1               1           Rising Edge of INT0 Generates Interrupt

    ! ISC10 and ISC11 -> sense control INT1
    ISC11           ISC10       Description
    0               0           Low level of INT1 Generates Interrupt
    0               1           Any Change in INT1 Generates Interrupt
    1               0           Falling Edge of INT1 Generates Interrupt
    1               1           Rising Edge of INT1 Generates Interrupt

    * ISR -> Interrupt Service Routine (function to execute when an interrupt is received)

    ? ISR(INT0_vect) {} -> for INT0
    ? ISR(INT1_vect) {} -> for INT1

*/
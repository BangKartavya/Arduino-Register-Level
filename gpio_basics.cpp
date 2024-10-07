/*
 * DDRx -> Data Direction Register
 * PORTx -> Data Register
 * PINx -> Input Pin Address Resgister
 */

/*
 * DDRB -> Data Direction Resgister for PORTB (8 bits DDB0 - DDB7)
 * DDRC -> Data Direction Resgister for PORTC (7 bits DDC0 - DDC6)
 * DDRD -> Data Direction Resgister for PORTD (8 bits DDD0 - DDD7)
 */

/*
 ! DDRx -> Values indicate whether the pin is input or output
 ? 0-> Input 1-> Output
*/

/*
  ? Methods for settings or clearing register bits

  * Individual Bits
  * 8 Bit Data

  ? Individual bits -> set or clear a particular bit witout disturbing the state of other bits

  ? 8 Bit data -> set or clear bits in a register if we want to provide values for all the bits in the register
*/

/*
  ! Individual Bits Method

  ? Setting zeroth bit of DDRB as output

  * DDRB = DDRB | (1 << DDB0); (all the values stay the same except DDB0 (which is set as 1))

  * DDRB |= (1 << DDB0); setting single bit

  * DDRB |= (1<< DDB0) | (1 << DDB1) setting multiple bits

  ? Setting zeroth bit of DDRB as input

  * DDRB = DDRB &(~(1 << DDB0) (all the values stay the same except DDB0 (which is set as 0))

  * DDRB &= (~(1 << DDB0)); clearing single bit

  * DDRB &= (~(1 << DDB0)) & (~(1 << DDB1)); clearing multiple bits

  ! 8 Bit Data Method

  ? Configure DDB0 - DDB3 -> Input DDB4 - DDB7 -> Output

  * DDRB = 0b11110000; (binary Data)
  * DDRB = 0xF0; (hexadecimal data)

  ? Configure DDB2,4,5 -> Input DDB0,1,3,6,7 -> Output

  * DDRB = 0x11001011;
  * DDRB = 0xCB;

*/

/*
  ! PORTx -> Value used to write or read the state of the pin (high/low) (if pin is configured output (DDBx -> 1))
  ? 0 -> Low 1 -> High

  ! PORTx -> Value used to enable or diable the pull-up of the pin (if pin is configured input (DDBx -> 0))
  ? 0 -> Pull Up Disabled 1 -> Pull Up Enabled

  * PORTB -> PB0 - PB7
  * PORTC -> PC0 - PC6
  * PORTD -> PD0 - PD7
*/

/*
  If pin is configured as OUTPUT
  ! Individual Method

  ? turn ON output pin PB0
  PORTB |= (1 << PB0);

  ? turn OFF output pin PB0
  PORTB &= (~(1 << PB0));

  ! 8-Bit Data Method

  ? turn ON PB4-PB7 pins

  PORTB = 0b11110000;
  PORTB = 0xF0;
*/

/*

  ! PINx -> Used for reading the status of the input pin (if the pin is configured as INPUT)


  * PINB -> PINB0 - PINB7
  * PINC -> PINC0 - PINC6
  * PINB -> PINC0 - PINB7

  ? If i want to read status PB0

  if(PINB & (1 << PINB0)) ... (when PINB0 is 1)
  else ... (when PINB0 is 0)
*/

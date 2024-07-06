void delay_ms(unsigned int ms) {
  for (unsigned int i = 0; i < ms; i++) {
      // Configure Timer1
      TCCR1A = 0;  // Clear Timer1 Control Register A
      TCCR1B = 0;  // Clear Timer1 Control Register B
      TCNT1 = 0;   // Clear Timer1 Counter

      // Set Timer1 to CTC mode and set prescaler to 64
      TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

      // Set compare match register for 1ms delay
      OCR1A = 249;

      // Wait for compare match flag to be set
      while (!(TIFR1 & (1 << OCF1A)));

      // Clear compare match flag
      TIFR1 |= (1 << OCF1A);
  }
}
// Assumes 16 MHz clock.
// Leave all but your selection commented out
// const unsigned int TOP = 0xFFFF; // 16-bit resolution.   244 Hz PWM
// const unsigned int TOP = 0x7FFF; // 15-bit resolution.   488 Hz PWM
// const unsigned int TOP = 0x3FFF; // 14-bit resolution.   976 Hz PWM
// const unsigned int TOP = 0x1FFF; // 13-bit resolution.  1953 Hz PWM
// const unsigned int TOP = 0x0FFF; // 12-bit resolution.  3906 Hz PWM
// const unsigned int TOP = 0x07FF; // 11-bit resolution.  7812 Hz PWM
const unsigned int TOP = 0x03FF; // 10-bit resolution. 15624 Hz PWM

void enablePin9() {
  pinMode(9, OUTPUT);
  TCCR1A |= _BV(COM1A1);
}

void enablePin10() {
  pinMode(10, OUTPUT);
  TCCR1A |= _BV(COM1B1);
}

inline void PWM9(unsigned int PWMValue) {
  OCR1A = constrain(PWMValue, 0, TOP);
}

inline void PWM10(unsigned int PWMValue) {
  OCR1B = constrain(PWMValue, 0, TOP);
}

void setup() { 
  // Clear Registers
  TCCR1A = 0;
  TCCR1B = 0;
  
  // Configure Fast PWM
  TCCR1A = _BV(WGM11);                 // Set WGM Low Bits
  TCCR1B = _BV(WGM13) | _BV(WGM12);    // Set WGM High Bits

  // Select Clock Scaling
  TCCR1B |= _BV(CS10); // Set no scaling

  // Clean Defaults
  OCR1A = 0; // Pin 9 PWM length
  OCR1B = 0; // Pin 10 PWM length
  ICR1 = TOP; // Greatest Bound (res)
  TCNT1 = 0; // Reset Clock

  // Enable Pins
  enablePin9();
  enablePin10();
}

void loop() {
  // USAGE: Call the function PWM9(value) [or PWM10] with the value you'd like to transmit over PWM
  //        The value will be constrained to the maximum of the resolution selected...
  //        Note, if set more than once before the clock can cycle, it will only broadcast the last value sent,
  //        or could broadcast a bad value. An example has been left below for reference, where 2 values are sent
  PWM9(1000);
  delay(1000);
  PWM9(0);
  delay(1000);
}

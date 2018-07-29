// check the 5V power supply

#define POWER_SUPPY       A6

#define RESISTOR_REF_5V_1 220
#define RESISTOR_REF_5V_2 1000

NIL_WORKING_AREA(waThreadPower, 0);

NIL_THREAD(ThreadPower, arg) {

  pinMode(POWER_SUPPY, INPUT);
  analogReference(INTERNAL); // internal reference is 1.1V on ATMEGA328p

  while (true) {
    setParameter(PARAM_POWER_5V, (double)analogRead(POWER_SUPPY) * 1000 / 1024 * 1.1 / RESISTOR_REF_5V_1 * (RESISTOR_REF_5V_1 + RESISTOR_REF_5V_2) );
    nilThdSleepMilliseconds(1000);
  }
}



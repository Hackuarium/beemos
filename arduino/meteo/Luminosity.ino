// luminosity thread

#define LUMINOSITY        A0
#define LUMINOSITY_POWER  5

NIL_WORKING_AREA(waThreadLuminosity, 0);

NIL_THREAD(ThreadLuminosity, arg) {

  pinMode(LUMINOSITY, INPUT);

  while (true) {
    pinMode(LUMINOSITY_POWER, OUTPUT);
    digitalWrite(LUMINOSITY_POWER, HIGH);
    nilThdSleepMilliseconds(5);
    setParameter(PARAM_LUMINOSITY, analogRead(LUMINOSITY) );
    pinMode(LUMINOSITY_POWER, INPUT);
    nilThdSleepMilliseconds(1000);
  }
}



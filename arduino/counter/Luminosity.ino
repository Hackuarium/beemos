// luminosity thread

#define LUMINOSITY  A6

NIL_WORKING_AREA(waThreadLuminosity, 0);

NIL_THREAD(ThreadLuminosity, arg) {
  pinMode(LUMINOSITY, INPUT_PULLUP);

  while (true) {
    setParameter(PARAM_LUMINOSITY, analogRead(LUMINOSITY) );
    nilThdSleepMilliseconds(1000);
  }
}



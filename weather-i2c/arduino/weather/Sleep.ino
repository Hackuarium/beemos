#ifdef PARAM_SLEEP_DELAY

#include <avr/sleep.h>

NIL_WORKING_AREA(waThreadSleep, 16);

NIL_THREAD(ThreadSleep, arg) {

  nilThdSleepMilliseconds(10000);

  uint32_t lastSleep = millis();

  while (true) {
    if (getParameter(PARAM_SLEEP_DELAY) > 0) {
      if ((getParameter(PARAM_SLEEP_DELAY) * 1000) < (millis() - lastSleep)) {
        lastSleep = millis();
        sleepNow();
      }
    }
    nilThdSleepMilliseconds(1000);
  }
}

void sleepNow () {

#ifdef WATCH_DOG
  wdt_disable();
#endif

  set_sleep_mode (SLEEP_MODE_PWR_DOWN);

  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS);

  uint8_t analogStatus = ADCSRA & (1 << ADEN);
  ADCSRA &= ~(1 << ADEN); //Disable ADC: allows to win 80µA

  sleep_mode ();            // here the device is put to sleep

#ifdef WATCH_DOG
  wdt_enable(WATCH_DOG);  //reactivate the watchdog
#endif

}

#endif


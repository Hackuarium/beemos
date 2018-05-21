// setting all threads on + defining threads order of priority.

#define MONITORING_LED 13

NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {
  nilThdSleepMilliseconds(1000);

  pinMode(MONITORING_LED, OUTPUT);

  #ifdef WATCH_DOG
    wdt_enable(WATCH_DOG);  //activate the watchdog
  #endif
  while (TRUE) {
    wdt_reset();//reset avoids automatic reboot
    digitalWrite(MONITORING_LED, HIGH);
    nilThdSleepMilliseconds(100);
    digitalWrite(MONITORING_LED, LOW);
    nilThdSleepMilliseconds(100);
  }
}


NIL_THREADS_TABLE_BEGIN()
// the order should be exact, Acquisition has the higher priority ...


#ifdef THR_SERIAL
NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))
#endif

#ifdef THR_LOGGER
NIL_THREADS_TABLE_ENTRY(NULL, ThreadLogger, NULL, waThreadLogger, sizeof(waThreadLogger))
#endif

NIL_THREADS_TABLE_ENTRY(NULL, ThreadLuminosity, NULL, waThreadLuminosity, sizeof(waThreadLuminosity))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadTemperature, NULL, waThreadTemperature, sizeof(waThreadTemperature))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadHumidity, NULL, waThreadHumidity, sizeof(waThreadHumidity))

#ifdef PARAM_SLEEP_DELAY
NIL_THREADS_TABLE_ENTRY(NULL, ThreadSleep, NULL, waThreadSleep, sizeof(waThreadSleep))
#endif

NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))


NIL_THREADS_TABLE_END()


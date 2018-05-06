// setting all threads on + defining threads order of priority.


NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {
  nilThdSleepMilliseconds(1000);
  wdt_enable(WDTO_8S);  //activate the watchdog
  while (TRUE) {
    wdt_reset();//reset avoids automatic reboot
    nilThdSleepMilliseconds(500);
  }
}


NIL_THREADS_TABLE_BEGIN()
// the order should be exact, Acquisition has the higher priority ...

NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadCounter, NULL, waThreadCounter, sizeof(waThreadCounter))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))


NIL_THREADS_TABLE_END()


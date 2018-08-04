// setting all threads on + defining threads order of priority.

#define MONITORING_LED 13

NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {
  nilThdSleepMilliseconds(1000);

  pinMode(MONITORING_LED, OUTPUT);

  while (TRUE) {
    digitalWrite(MONITORING_LED, HIGH);
    nilThdSleepMilliseconds(100);
    digitalWrite(MONITORING_LED, LOW);
    nilThdSleepMilliseconds(100);
  }
}


NIL_THREADS_TABLE_BEGIN()
// the order should be exact, Acquisition has the higher priority ...


NIL_THREADS_TABLE_ENTRY(NULL, ThreadGSM, NULL, waThreadGSM, sizeof(waThreadGSM))


NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))


NIL_THREADS_TABLE_END()


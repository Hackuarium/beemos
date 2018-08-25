
#include "libino/Si7021/Si7021.cpp"

Weather sensor;

NIL_WORKING_AREA(waThreadSi7021, 50);
NIL_THREAD(ThreadSi7021, arg) {
  nilThdSleepMilliseconds(1000);
  sensor.begin();

  while (true) {
    setParameter(PARAM_INT_HUMIDITY,sensor.getRH()*100);
    setParameter(PARAM_INT_TEMPERATURE,sensor.getTemp()*100);
    nilThdSleepMilliseconds(1000);
  }
}




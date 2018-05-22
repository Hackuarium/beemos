// This example shows how to copy parameters from a weather board
// locally

#ifdef THR_WEATHER

#define WEATHER_I2C_ADDRESS         55

#define WEATHER_TEMPERATURE_EXT     2
#define WEATHER_TEMPERATURE_IN      3
#define WEATHER_TEMPERATURE_BOARD   4
#define WEATHER_HUMIDITY            5
#define WEATHER_HUMIDITY_TEMP       6
#define WEATHER_LUMINOSITY          7
#define WEATHER_PRESSURE            8


NIL_WORKING_AREA(waThreadWeather, 160);

NIL_THREAD(ThreadWeather, arg) {

  nilThdSleepMilliseconds(1000);

  while (true) {
    wireWakeup(WEATHER_I2C_ADDRESS);
    nilThdSleepMilliseconds(5000);
    copyFromWeather();
    nilThdSleepMilliseconds(20000);
  }
}

void copyFromWeather() {
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_TEMPERATURE_EXT, PARAM_TEMPERATURE_EXT);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_TEMPERATURE_IN, PARAM_TEMPERATURE_IN);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_TEMPERATURE_BOARD, PARAM_TEMPERATURE_BOARD);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_HUMIDITY, PARAM_HUMIDITY);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_LUMINOSITY, PARAM_LUMINOSITY);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_PRESSURE, PARAM_PRESSURE);
}

#endif



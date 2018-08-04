// This example shows how to copy parameters from a weather board
// locally


#if defined(WEATHER_I2C_ADDRESS) || defined(SCALE_I2C_ADDRESS)

#ifdef WEATHER_I2C_ADDRESS
#define WEATHER_TEMPERATURE_EXT     2
#define WEATHER_TEMPERATURE_IN      3
#define WEATHER_TEMPERATURE_BOARD   4
#define WEATHER_HUMIDITY            5
#define WEATHER_HUMIDITY_TEMP       6
#define WEATHER_LUMINOSITY          7
#define WEATHER_PRESSURE            8
#endif

#ifdef SCALE_I2C_ADDRESS
#define SCALE_PARAM_WEIGHT                2
#define SCALE_PARAM_WEIGHT_G              3
#define SCALE_PARAM_WEIGHT_OFFSET         4
#define SCALE_PARAM_WEIGHT_FACTOR         5
#define SCALE_PARAM_WEIGHT_MIN            6
#define SCALE_PARAM_WEIGHT_MAX            7
#endif

NIL_WORKING_AREA(waThreadCopySlave, 140);

NIL_THREAD(ThreadCopySlave, arg) {

  nilThdSleepMilliseconds(1000);

  while (true) {
#ifdef WEATHER_I2C_ADDRESS
    wireWakeup(WEATHER_I2C_ADDRESS);
#endif
#ifdef SCALE_I2C_ADDRESS
    wireWakeup(SCALE_I2C_ADDRESS);
#endif
    nilThdSleepMilliseconds(5000);
    copyFromSlave();
    nilThdSleepMilliseconds(20000);
  }
}

void copyFromSlave() {
#ifdef WEATHER_I2C_ADDRESS
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_TEMPERATURE_EXT, PARAM_TEMPERATURE_EXT);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_TEMPERATURE_IN, PARAM_TEMPERATURE_IN);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_TEMPERATURE_BOARD, PARAM_TEMPERATURE_BOARD);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_HUMIDITY, PARAM_HUMIDITY);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_HUMIDITY_TEMP, PARAM_HUMIDITY_TEMP);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_LUMINOSITY, PARAM_LUMINOSITY);
  wireCopyParameter(WEATHER_I2C_ADDRESS, WEATHER_PRESSURE, PARAM_PRESSURE);
#endif

#ifdef SCALE_I2C_ADDRESS
  wireCopyParameter(SCALE_I2C_ADDRESS, SCALE_PARAM_WEIGHT, PARAM_WEIGHT);
  wireCopyParameter(SCALE_I2C_ADDRESS, SCALE_PARAM_WEIGHT_G, PARAM_WEIGHT_G);
  wireCopyParameter(SCALE_I2C_ADDRESS, SCALE_PARAM_WEIGHT_OFFSET, PARAM_WEIGHT_OFFSET);
  wireCopyParameter(SCALE_I2C_ADDRESS, SCALE_PARAM_WEIGHT_FACTOR, PARAM_WEIGHT_FACTOR);
#endif
}

#endif



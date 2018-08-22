// including libraries, defining main pins used and setting up general setup and loop.


#define MAX_PARAM 32

#define LOGGER_I2C_EEPROM  80  // I2C address of M24512 eeprom

#define SCALE_I2C_ADDRESS           16
#define WEATHER_I2C_ADDRESS         55
#define COUNTER_I2C_ADDRESS         59

#define THR_SERIAL    1

#define THR_WIRE_MASTER
// #define WIRE_MASTER_HOT_PLUG    1   // scan automatically the i2c port for new slaves and prevents SLEEP !!!

#define BATTERY               A6  // if battery we have also the temperature sensor
#define BATTERY_CHARGING      A5

#include "libino/hack.h"


void setup() {

  pinMode(9, OUTPUT); // turn on the memory
  digitalWrite(9, HIGH);

  start();
}

void loop() {}


// including libraries, defining main pins used and setting up general setup and loop.


#define MAX_PARAM 26   // If the MAX_PARAM change you need to change the pointer in the EEPROM

#define LOGGER_I2C_EEPROM  80  // I2C address of M24512 eeprom


#define WEATHER_I2C_ADDRESS         55

#define THR_SERIAL    1

#define THR_WIRE_MASTER
// #define WIRE_MASTER_HOT_PLUG    1   // scan automatically the i2c port for new slaves and prevents SLEEP !!!


#include "libino/hack.h"


void setup() {

  pinMode(9, OUTPUT); // turn on the memory
  digitalWrite(9, HIGH);

  start();
}

void loop() {}


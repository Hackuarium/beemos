// including libraries, defining main pins used and setting up general setup and loop.


#define MAX_PARAM 26   // If the MAX_PARAM change you need to change the pointer in the EEPROM


#define THR_SERIAL         1
// #define WIRE_SLAVE 55  // specify the address of the i2c slave
 #define THR_WIRE_MASTER


#include "lib/hack.h"


void setup() {
  start();
}

void loop() {}


// including libraries, defining main pins used and setting up general setup and loop.


#define MAX_PARAM 26   // If the MAX_PARAM change you need to change the pointer in the EEPROM


#define THR_SERIAL     1
#define THR_LOGGER     1

#define THR_WIRE_SLAVE  55        // specify the address of the i2c slave
#define WATCH_DOG       WDTO_8S   // enable watch dog

#include "libino/hack.h"


void setup() {
  start();
}

void loop() {}


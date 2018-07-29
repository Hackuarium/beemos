// including libraries, defining main pins used and setting up general setup and loop.


#define MAX_PARAM 16   // If the MAX_PARAM change you need to change the pointer in the EEPROM


#define THR_SERIAL            1
#define THR_LOGGER            1

#define THR_WIRE_SLAVE        16        // specify the address of the i2c slave
#define WIRE_SLAVE_COMMAND    1         // we have some specific wire commands
#define WATCH_DOG             WDTO_8S   // enable watch dog

#include "libino/hack.h"


void setup() {
  start();
}

void loop() {}


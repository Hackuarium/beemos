// including libraries, defining main pins used and setting up general setup and loop.

#define THR_WIRE_SLAVE 59         // specify the address of the i2c slave
#define WIRE_SLAVE_COMMAND    1   // we have some specific wire commands

// #define LOGGER 1

#define MAX_PARAM 26

#define THR_SERIAL    1

#include "libino/hack.h"

void setup() {
 start();
}

void loop() {}


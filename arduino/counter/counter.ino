// including libraries, defining main pins used and setting up general setup and loop.

#include <NilRTOS.h>
#include <avr/wdt.h> // watch dog for automatic reboot in case of crash
#include <TimeLib.h> // git clone https://github.com/PaulStoffregen/Time
#include "lib/Utility.h"


// #define WIRE_SLAVE 55  // specify the address of the i2c slave
#define TEMPERATURE   SCL

void setup() {
  delay(2000);
  Serial.begin(9600);
  setupParameters();
  checkParameters(); // setup automatically the default parameter after install boot loader
  nilSysBegin();
#ifdef WIRE_SLAVE
  startWireSlave();
#endif
}

void loop() {}


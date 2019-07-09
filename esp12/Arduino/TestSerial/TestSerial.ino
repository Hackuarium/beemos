#define MAX_PARAM 26

#include <TimeLib.h>
#include <Time.h>
#include "lib/params.h"
#include "lib/toHex.h"
#include "lib/eeprom.h"
#include "lib/Utility.h"
#include "lib/SerialUtilities.h"
#include "lib/Serial.h"


void setup() {
  // put your setup code here, to run once:
startSerial();
}

void loop() {
  // put your main code here, to run repeatedly:

}


void printSpecificHelp(Print* output) {}
void processSpecificCommand(char* data, char* paramValue, Print* output)  {}

// setting ATmega32U4 as I2C slave.

#ifdef WIRE_SLAVE

#include <Wire.h>

char command = 0x00;

void startWireSlave() {
  Wire.begin(WIRE_SLAVE);       // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}

void requestEvent() {
  int value = getParameter(command);
  Wire.write(value >> 0 & 255);
  Wire.write(value >> 8 & 255);
}

void receiveEvent() {
  while (Wire.available()) { // loop through all but the last
    command = Wire.read(); // receive byte as a character
  }
}

#endif



// setting ATmega32U4 as I2C slave.

#ifdef THR_WIRE_SLAVE

#include <Wire.h>

char command = 0x00;

void requestEvent() {
  int value = getParameter(command);
  Wire.write(value >> 8 & 255);
  Wire.write(value >> 0 & 255);
}

void receiveEvent() {
  if (Wire.available()) {
    command = Wire.read(); // receive byte as a character
  }
  if (Wire.available()) { // we need to set the value of a register
    int value = 0;
    while (Wire.available()) { // loop through all but the last 
      value <<= 8;
      value |= Wire.read();
    }
    setParameter(command, value);
  }
  
}

void startWireSlave() {
  Wire.begin(THR_WIRE_SLAVE);       // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}

#endif


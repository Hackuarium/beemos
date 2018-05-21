// setting ATmega32U4 as I2C slave.

#ifdef THR_WIRE_MASTER


#include <Wire.h>


#define WIRE_MAX_DEVICES 5
byte numberI2CDevices = 0;
byte wireDeviceID[WIRE_MAX_DEVICES];

void wireUpdateList();


NIL_WORKING_AREA(waThreadWireMaster, 250);
NIL_THREAD(ThreadWireMaster, arg) {

  nilThdSleepMilliseconds(1000);

  unsigned int wireEventStatus = 0;

  Wire.begin();

  while (true) {

    if (wireEventStatus % 25 == 0) {
     // wireUpdateList();
    }
    wireEventStatus++;

    nilThdSleepMilliseconds(200);
  }
}


int wireReadInt(uint8_t address) {
  uint8_t i = 0;
  int data = 0;
  Wire.requestFrom(address, (uint8_t)2);
  while (Wire.available()) {
    if (i++ > 2) return ERROR_VALUE; // security mechanism
    uint8_t oneByte = Wire.read();
    data <<= 8;
    data |= oneByte;
  }
  return data;
}

void wireSetRegister(uint8_t address, uint8_t registerAddress) {
  Wire.beginTransmission(address);
  Wire.write(registerAddress);
  Wire.endTransmission(); // Send data to I2C dev with option for a repeated start
}

int wireReadIntRegister(uint8_t address, uint8_t registerAddress) {
  wireSetRegister(address, regiwireWriteIntRegistersterAddress);
  return wireReadInt(address);
}

uint8_t wireWriteIntRegister(uint8_t address, uint8_t registerAddress, int value) {
  Wire.beginTransmission(address);
  Wire.write(registerAddress);
  if (value > 255 || value < 0) Wire.write(value >> 8);
  Wire.write(value & 255);
  return Wire.endTransmission(); // Send data to I2C dev with option for a repeated start
}

void wireInfo(Print* output) {
  output->println("I2C");

  for (byte i = 0; i < numberI2CDevices; i++) {
    output->print(i);
    output->print(F(": "));
    output->print(wireDeviceID[i]);
    output->print(F(" - "));
    output->println(wireDeviceID[i], BIN);
  }
}

void printWireDeviceParameter(Print* output, uint8_t wireID) {
  output->println(F("I2C device: "));
  output->println(wireID);
  for (byte i = 0; i < 26; i++) {
    output->print(i, HEX);
    output->print(F(" - "));
    output->println(wireReadIntRegister(wireID, i));
  }
}


void wireRemoveDevice(byte id) {
  for (byte i = id; i < numberI2CDevices - 1; i++) {
    wireDeviceID[i] = wireDeviceID[i + 1];
  }
  numberI2CDevices--;
}

void wireInsertDevice(byte id, byte newDevice) {
  //Serial.println(id);

  if (numberI2CDevices < WIRE_MAX_DEVICES) {
    for (byte i = id + 1; i < numberI2CDevices - 1; i++) {
      wireDeviceID[i] = wireDeviceID[i + 1];
    }
    wireDeviceID[id] = newDevice;
    numberI2CDevices++;
  }
}

boolean wireDeviceExists(byte id) {
  for (byte i = 0; i < numberI2CDevices; i++) {
    if (wireDeviceID[i] == id) return true;
  }
  return false;
}


void wireUpdateList() {
  // 16ms
  byte _data;
  byte currentPosition = 0;
  // I2C Module Scan, from_id ... to_id
  for (byte i = 0; i <= 127; i++)
  {
    Wire.beginTransmission(i);
    Wire.write(&_data, 0);
    // I2C Module found out!
    if (Wire.endTransmission() == 0)
    {
      // there is a device, we need to check if we should add or remove a previous device
      if (currentPosition < numberI2CDevices && wireDeviceID[currentPosition] == i) { // it is still the same device that is at the same position, nothing to do
        currentPosition++;
      }
      else if (currentPosition < numberI2CDevices && wireDeviceID[currentPosition] < i) { // some device(s) disappear, we need to delete them
        wireRemoveDevice(currentPosition);
        i--;
      }
      else if (currentPosition >= numberI2CDevices || wireDeviceID[currentPosition] > i) { // we need to add a device
        //Serial.print("add: ");        DEBUG POUR CONNAITRE L'ADRESSE DE L'I2C !!!!!!!!
        //Serial.println(i);
        wireInsertDevice(currentPosition, i);
        currentPosition++;
      }
      nilThdSleepMilliseconds(1);
    }
  }
  while (currentPosition < numberI2CDevices) {
    wireRemoveDevice(currentPosition);
  }
}

void printWireHelp(Print* output) {
  output->println(F("(il) List devices"));
  output->println(F("(ip) List parameters"));
}


void processWireCommand(char command, char* paramValue, Print* output) { // char and char* ??
  switch (command) {
    case 'p':
      if (paramValue[0] == '\0') {
        Serial.println(F("Missing device ID"));
      } else {
        printWireDeviceParameter(output, atoi(paramValue));
      }
      break;
    case 'l':
      wireInfo(output);
      break;
    case 'u':
      wireUpdateList();
      break;
    default:
      printWireHelp(output);
  }
}

#endif


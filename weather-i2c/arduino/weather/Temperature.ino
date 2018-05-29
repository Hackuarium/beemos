#include "lib/onewire/OneWire.cpp"

#define TEMPERATURE_EXT      A2
#define TEMPERATURE_IN       A3
#define TEMPERATURE_BOARD    A1
#define TEMPERATURE_POWER    10


OneWire  oneWire1(TEMPERATURE_EXT);
OneWire  oneWire2(TEMPERATURE_IN);
OneWire  oneWire3(TEMPERATURE_BOARD);

void getTemperature(OneWire &ow, int parameter);
void startTemperatureAcquisition(OneWire &ow);


NIL_WORKING_AREA(waThreadTemperature, 160);

NIL_THREAD(ThreadTemperature, arg) {

  nilThdSleepMilliseconds(1000);

  pinMode(TEMPERATURE_POWER, OUTPUT);

  while (true) {
    digitalWrite(TEMPERATURE_POWER, HIGH);
    nilThdSleepMilliseconds(5);
    startTemperatureAcquisition(oneWire1);
    startTemperatureAcquisition(oneWire2);
    startTemperatureAcquisition(oneWire3);
    nilThdSleepMilliseconds(1000);
    getTemperature(oneWire1, PARAM_TEMPERATURE_EXT);
    getTemperature(oneWire2, PARAM_TEMPERATURE_IN);
    getTemperature(oneWire3, PARAM_TEMPERATURE_BOARD);
     digitalWrite(TEMPERATURE_POWER, LOW);
    nilThdSleepMilliseconds(1000);
  }
}

void startTemperatureAcquisition(OneWire &ow) {
  ow.reset();
  ow.skip();
  ow.write(0x44, 1);
};

void getTemperature(OneWire &ow, int parameter) {
  byte data[12];
  // however this allows to check the version of the sensor if required
  float celsius;

  ow.reset();
  ow.skip();
  ow.write(0xBE);         // Read Scratchpad (??)

  for (byte i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ow.read();
  }

  if (OneWire::crc8(data, 8) == data[8]) {
    // Convert the data to actual temperature
    int16_t raw = (data[1] << 8) | data[0];
    celsius = (float)raw / 16.0;

    setParameter(parameter, celsius * 100);
  } else {
    setParameter(parameter, ERROR_VALUE);
  }
}





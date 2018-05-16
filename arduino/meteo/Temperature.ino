#include <OneWire.h>


#define TEMPERATURE_EXT      A2
#define TEMPERATURE_IN       A3
#define TEMPERATURE_BOARD    A1
#define TEMPERATURE_POWER    10


OneWire  oneWire1(TEMPERATURE_EXT);
OneWire  oneWire1(TEMPERATURE_IN);
OneWire  oneWire1(TEMPERATURE_BOARD);

NIL_WORKING_AREA(waThreadTemperature, 128);

NIL_THREAD(ThreadTemperature, arg) {

  nilThdSleepMilliseconds(1000);


  pinMode(TEMPERATURE_POWER, OUTPUT);
  digitalWrite(TEMPERATURE_POWER, HIGH);

  while (true) {

    getTemperature(oneWire1, PARAM_TEMPERATURE_EXT);
    getTemperature(oneWire2, PARAM_TEMPERATURE_IN);
    getTemperature(oneWire3, PARAM_TEMPERATURE_BOARD);
    nilThdSleepMilliseconds(1000);
  }
}





void getTemperature(OneWire &ds, int parameter) {
  byte data[12];
  byte addr[8];
  float celsius;
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);

  nilThdSleepMilliseconds(1000);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Read Scratchpad (??)

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }

  if (OneWire::crc8(data, 8) == data[8]) {
    // Convert the data to actual temperature
    int16_t raw = (data[1] << 8) | data[0];
    celsius = (float)raw / 16.0;

    setParameter(parameter, celsius * 100);
  }

}





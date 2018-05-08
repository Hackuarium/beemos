
#define TEMPERATURE   SCL

#ifdef TEMPERATURE

#include <OneWire.h>

NIL_WORKING_AREA(waThreadTemperature, 128);

NIL_THREAD(ThreadTemperature, arg) {
  OneWire  ds(TEMPERATURE);  // on pin 10 (a 4.7K resistor is necessary)
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  float celsius;
  ds.search(addr);


  while (true) {
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end

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

      setParameter(PARAM_TEMPERATURE, celsius * 100);
      nilThdSleepMilliseconds(5000);
    }
  }
}




#endif

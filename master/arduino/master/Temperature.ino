#include "libino/onewire/OneWire.cpp"

#define TEMPERATURE_1    7
#define TEMPERATURE_2    10
#define TEMPERATURE_3    11

OneWire oneWire1(TEMPERATURE_1);
OneWire oneWire2(TEMPERATURE_2);
OneWire oneWire3(TEMPERATURE_3);

void getTemperature(OneWire &ow, int parameter);
void startTemperatureAcquisition(OneWire &ow);

NIL_WORKING_AREA(waThreadTemperature, 80);

NIL_THREAD(ThreadTemperature, arg)
{

  nilThdSleepMilliseconds(1000);

  while (true)
  {
    nilThdSleepMilliseconds(5);
    startTemperatureAcquisition(oneWire1);
    startTemperatureAcquisition(oneWire2);
    startTemperatureAcquisition(oneWire3);
    nilThdSleepMilliseconds(1000);
    getTemperature(oneWire1, PARAM_INT_TEMPERATURE);
    getTemperature(oneWire2, PARAM_INT_TEMPERATURE_A);
    getTemperature(oneWire3, PARAM_INT_TEMPERATURE_B);
    nilThdSleepMilliseconds(1000);
  }
}

void startTemperatureAcquisition(OneWire &ow)
{
  ow.reset();
  ow.skip();
  ow.write(0x44, 1);
};

void getTemperature(OneWire &ow, int parameter)
{
  byte data[12];
  // however this allows to check the version of the sensor if required
  float celsius;

  ow.reset();
  ow.skip();
  ow.write(0xBE); // Read Scratchpad (??)

  for (byte i = 0; i < 9; i++)
  { // we need 9 bytes
    data[i] = ow.read();
  }


  if (OneWire::crc8(data, 8) == data[8])
  {
    // Convert the data to actual temperature
    int16_t raw = (data[1] << 8) | data[0];
    celsius = (float)raw / 16.0;

    setParameter(parameter, celsius * 100);
  } else {
    setParameter(parameter, ERROR_VALUE);
  }
}

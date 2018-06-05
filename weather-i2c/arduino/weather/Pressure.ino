 
#define SDA_PORT PORTB
#define SDA_PIN 1
#define SCL_PORT PORTB
#define SCL_PIN 0

#include "lib/ms5637/ms5637.cpp"
static ms5637 m_ms5637;


NIL_WORKING_AREA(waThreadPressure, 50);

NIL_THREAD(ThreadPressure, arg) {

  nilThdSleepMilliseconds(1000);

  m_ms5637.begin();
  m_ms5637.set_resolution(ms5637_resolution_osr_4096);


  while (true) {
    getPressureTemperature();
    nilThdSleepMilliseconds(2000);
  }
}

void getPressureTemperature() {
  ms5637_status status;
  float temperature;
  float pressure;
  boolean connected;

  connected = m_ms5637.is_connected();
  if (connected) {
    status = m_ms5637.read_temperature_and_pressure(&temperature, &pressure);
    setParameter(PARAM_PRESSURE, pressure * 10);
    setParameter(PARAM_PRESSURE_TEMP, temperature * 100);
  } else {
    setParameter(PARAM_PRESSURE, ERROR_VALUE);
    setParameter(PARAM_PRESSURE_TEMP, ERROR_VALUE);
  }

}


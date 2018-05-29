
#include "lib/ms5637.cpp"

static ms5637 m_ms5637;

void setup(void) {
  Serial.begin(9600);
  m_ms5637.begin();

  m_ms5637.set_resolution(ms5637_resolution_osr_4096);
}
void loop(void) {
  ms5637_status status;
  float temperature;
  float pressure;
  boolean connected;

  connected = m_ms5637.is_connected();
  if (connected) {
    status = m_ms5637.read_temperature_and_pressure(&temperature, &pressure);

    Serial.print("Temperature = ");
    Serial.print(temperature, 2);
    Serial.println("C");

    Serial.print("Pressure = ");
    Serial.print(pressure, 2);
    Serial.println("hPa");
  }

  delay(1000);
}

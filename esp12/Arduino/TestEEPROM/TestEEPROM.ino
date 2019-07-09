#include <EEPROM.h>


void setup() {
  EEPROM.begin(1024);
  Serial.begin(9600);
}

void loop() {
  for (int16_t i = 0; i < 100; i++) { 
    EEPROM.put(i * 2, i);
    EEPROM.commit();
  }
  for (int16_t i = 0; i < 100; i++) {
    int16_t j = 0;
    EEPROM.get(i * 2, j);
    Serial.println(j);
  }

  for (int32_t i = 0; i < 100; i++) {
    EEPROM.put(i * 4 + 500, i);
    EEPROM.commit();
  }
  
  for (int32_t i = 0; i < 100; i++) {
    int32_t j = 0;
    EEPROM.get(i * 4 + 500, j);
    Serial.println(j);
  }
  delay(10000);
}

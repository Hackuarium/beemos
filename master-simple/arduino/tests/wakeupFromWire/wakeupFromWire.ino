#include <Wire.h>

void setup() {
  pinMode(13, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  Wire.requestFrom(55, 1);
  byte value = Wire.read();
  Serial.println(value);
  
  digitalWrite(13, HIGH);
  delay(10000);
  digitalWrite(13, LOW);
}

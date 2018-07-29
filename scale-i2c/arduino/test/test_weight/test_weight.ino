#include "lib/HX711/HX711.cpp"
#define WEIGHT_DATA        A0
#define WEIGHT_CLK         A1

HX711 scale(WEIGHT_DATA, WEIGHT_CLK);

void setup() {
  delay(1000);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  Serial.println(scale.read());
  delay(250);
}

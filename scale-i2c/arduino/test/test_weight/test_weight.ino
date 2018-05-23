#include "HX711.h"
#define WEIGHT_DATA        22
#define WEIGHT_CLK         23

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

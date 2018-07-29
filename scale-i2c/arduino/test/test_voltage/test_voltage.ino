#define BATTERY A6

#define RESISTOR_REF_5V_1 220
#define RESISTOR_REF_5V_2 1000

// 2 resistors in serie: 220k and 1m
//

void setup() {
  pinMode(BATTERY, INPUT);
  analogReference(INTERNAL); // internal reference is 1.1V on ATMEGA328p
  Serial.begin(9600);

}

void loop() {
  double voltage = (double)analogRead(BATTERY) / 1024 * 1.1 / RESISTOR_REF_5V_1 * (RESISTOR_REF_5V_1 + RESISTOR_REF_5V_2);
  Serial.println( voltage );
  delay(1000);
}

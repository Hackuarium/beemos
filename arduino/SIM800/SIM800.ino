void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {
  //Read SIM800 output (if available) and print it in Arduino IDE Serial Monitor
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}

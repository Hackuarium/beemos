// check https://www.exploreembedded.com/wiki/Setting_up_GPRS_with_SIM800L

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(38400);
  Serial.begin(38400);
  delay(2000);
  Serial.println("Started");
}

void loop() {

  while (Serial.available()) {
    Serial1.print(Serial.read());
  }

  while (Serial1.available()) {
    Serial.print(Serial1.read());
  }

}

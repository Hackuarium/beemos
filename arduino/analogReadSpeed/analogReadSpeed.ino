void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  long start = millis();

  for (int i = 0; i < 10000; i++) {
    int value = analogRead(A1);
  }

  Serial.println(millis() - start);

}

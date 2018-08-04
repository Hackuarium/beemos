void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL); // internal reference is 2.56V
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
}

void loop() {
  Serial.print("A5 ");
  Serial.print(analogRead(A5));
  Serial.print("   A6 ");
  Serial.print(analogRead(A6));
  Serial.print(" ");
  Serial.println(((double)analogRead(A6)) / 1024 * 5.12);
  delay(1000);
}

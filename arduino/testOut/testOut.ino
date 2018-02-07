

byte out[] = {1, 0, 3, 5, 7, 6, 4, 2, 8, 9, 11, 13, 15, 14, 12, 10};
#define OUT0 A0
#define OUT1 A1
#define OUT2 A2
#define OUT3 A3


void setup() {
  pinMode(OUT0, OUTPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(13, OUTPUT);
}


// the loop function runs over and over again forever
void loop() {

  for (byte i = 0; i < 16; i++) {
    setOutput(i);
    delay(10);
  }

  switchBlink();
}

boolean blinkHigh = false;
void switchBlink() {
  if (blinkHigh) {
    blinkHigh = false;
    digitalWrite(13, LOW);
  } else {
    blinkHigh = true;
    digitalWrite(13, HIGH);
  }
}

void setOutput(byte i) {
  if (i & 0b0001) {
    digitalWrite(OUT0, HIGH);
  } else {
    digitalWrite(OUT0, LOW);
  }
  if (i & 0b010) {
    digitalWrite(OUT1, HIGH);
  } else {
    digitalWrite(OUT1, LOW);
  }
  if (i & 0b0100) {
    digitalWrite(OUT2, HIGH);
  } else {
    digitalWrite(OUT2, LOW);
  }
  if (i & 0b1000) {
    digitalWrite(OUT3, HIGH);
  } else {
    digitalWrite(OUT3, LOW);
  }
}



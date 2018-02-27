/*
     The purpose of this code is to test the beemos-counter board.
     The board has 16 infrared emitters/receptors controlled by 4
     analog pins via a multiplexer.
*/

// byte out[] = {1, 0, 3, 5, 7, 6, 4, 2, 8, 9, 11, 13, 15, 14, 12, 10};
byte out[] = {1, 0, 7, 2, 6, 3, 5, 4, 8, 9, 15, 10, 14, 11, 13, 12};
#define OUT0 A0
#define OUT1 A1
#define OUT2 A2
#define OUT3 A3

byte in[] = {6, 7, 0, 5, 1, 4, 2, 3, 8, 9, 14, 15, 12, 13, 10, 11};

#define IN0 5
#define IN1 9
#define IN2 8
#define IN3 6
#define MUX A4
int muxValue=0;

void setup() {
  pinMode(IN0, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(OUT0, OUTPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(MUX, INPUT);
  Serial.begin(9600);
  digitalWrite(10,LOW);
}


// the loop function runs over and over again forever
void loop() {
  // Iterating over infrared emitters
  for (byte i = 0; i < 16; i++) {
    setOutput(out[i]);
    delay(20);
    setInput(in[i]);
   
    muxValue = analogRead(MUX);
    delay(10);
    //Serial.println(muxValue);
    Serial.print("i=");
    Serial.print(i);
    Serial.print(" Val=");
    Serial.print(muxValue);
    Serial.print("  ");
  }
  Serial.println();

  switchBlink();
}

// blinking LED to ensure the loop is running
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

// Enable Output pins based on binary value of input i.
// This enables infrared emitter number i.
void setOutput(byte i) {
  if (i & 0b0001) {
    digitalWrite(OUT0, HIGH);
  } else {
    digitalWrite(OUT0, LOW);
  }
  if (i & 0b0010) {
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

void setInput(byte i) {
  if (i & 0b0001) {
    digitalWrite(IN0, HIGH);
  } else {
    digitalWrite(IN0, LOW);
  }
  if (i & 0b0010) {
    digitalWrite(IN1, HIGH);
  } else {
    digitalWrite(IN1, LOW);
  }
  if (i & 0b0100) {
    digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN2, LOW);
  }
  if (i & 0b1000) {
    digitalWrite(IN3, HIGH);
  } else {
    digitalWrite(IN3, LOW);
  }
}

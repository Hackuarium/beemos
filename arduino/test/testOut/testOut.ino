int muxValue = 0;


int current[16];


void setup() {
  Serial.begin(9600);
  initCounter();
  initMax();
}



// the loop function runs over and over again forever
void loop() {
  // Iterating over infrared emitters
  while (true) {


    updateCounter();
    printCounter();
    updateMax();


    delay(500);
  }


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


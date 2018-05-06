int muxValue = 0;


byte current[16];
byte gateStatus[] = {0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
  Serial.begin(9600);
  initCounter();
  initMax();
}



// the loop function runs over and over again forever
void loop() {
  // Iterating over infrared emitters
  byte counter = 0;
  while (true) {


    updateCounter();
    //   printCounter();
    updateMax();
    //   printMax();
    updateStatus();


    counter++;
    if (counter = 50) {
      printGateStatus();
      counter=0;
    }
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


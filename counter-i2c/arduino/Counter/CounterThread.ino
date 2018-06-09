#define MIN_MAX_RESET 6 // every 6 s we change min/max


byte current[16];
byte background[16];
byte difference[16];

byte out[] = {1, 0, 7, 2, 6, 3, 5, 4, 8, 9, 15, 10, 14, 11, 13, 12};
// byte out[] = {1, 0};
#define OUT0 A0
#define OUT1 A1
#define OUT2 A2
#define OUT3 A3

byte in[] = {6, 7, 0, 5, 1, 4, 2, 3, 8, 9, 14, 15, 12, 13, 10, 11};

#define IN0 5
#define IN1 9
#define IN2 8
#define IN3 6
#define IN_EN 10
#define MUX A4


NIL_WORKING_AREA(waThreadCounter, 120);
NIL_THREAD(ThreadCounter, arg) {
  initCounter();
  initBackground();
  while (true) {
    updateCounter();
    updateBackground();
    updateTotal();
  }
}


void initCounter() {
  pinMode(IN0, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(OUT0, OUTPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(MUX, INPUT_PULLUP);
  pinMode(IN_EN, OUTPUT);
  digitalWrite(IN_EN, LOW);
}


void updateCounter() {
  // this warming up is required in order to have the correct value for the first receiver
  for (byte i = 0; i < sizeof(out); i++) {
    setOutput(out[i]);
    setInput(in[i]);
    nilThdSleepMilliseconds(1);
  }
  for (byte i = 0; i < sizeof(out); i++) {
    setOutput(out[i]);
    setInput(in[i]);
    nilThdSleepMilliseconds(1);
    byte currentValue = analogRead(MUX) >> 2;
    difference[i] = (byte)abs(current[i] - currentValue);
    current[i] = currentValue;;
  }
  nilThdSleepMilliseconds(10);
}


void printCounter(Print* output) {
  for (byte k = 0; k < getParameter(PARAM_DEBUG_REPEAT); k++) {
    for (byte i = 0; i < sizeof(out); i++) {
      byte value = current[i];
      if (value < 10) output->print(" ");
      if (value < 100) output->print(" ");
      output->print(value);
      output->print(" ");
    }
    nilThdSleepMilliseconds(500);
    output->println();
    nilThdSleepMilliseconds(getParameter(PARAM_DEBUG_DELAY));
  }
}

/**
   We will show if we are over or under the threshold
*/
void printGateInfo(Print* output) {
  int diff1 = 0;
  int diff2 = 0;
  for (byte k = 0; k < getParameter(PARAM_DEBUG_REPEAT); k++) {
    for (byte i = 0; i < sizeof(out); i = i + 2) {
      diff1 = background[i] - current[i];
      diff2 = background[i + 1] - current[i + 1];
      if ((abs(diff1) >=  getParameter(PARAM_THRESHOLD)) || (abs(diff2) >=  getParameter(PARAM_THRESHOLD))) {
        output->print("Gate ");
        output->print(i / 2 + 1);
        output->print(": ");
        output->print("from bg ");
      }
      output->print(diff1);
      if (diff1 < 10) output->print(" ");
      output->print(" ");
      output->print(diff2);
      if (diff2 < 10) output->print(" ");
      output->println("");
    }
  }
  nilThdSleepMilliseconds(200);
  nilThdSleepMilliseconds(getParameter(PARAM_DEBUG_DELAY));
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





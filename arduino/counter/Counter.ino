#define MIN_MAX_RESET 6 // every 6 s we change min/max


byte current[16];

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
  initMax();
  while (true) {
    updateCounter();
    updateMax();
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
  for (byte i = 0; i < sizeof(out); i++) {
    setOutput(out[i]);
    setInput(in[i]);
    nilThdSleepMilliseconds(1);
    current[i] = analogRead(MUX) >> 2;
  }
}


void printCounter(Print* output) {
  for (byte k = 0; k < getParameter(PARAM_DEBUG_REPEAT); k++) {
    for (byte j = 0; j < 20; j++) {
      for (byte i = 0; i < sizeof(out); i++) {
        output->print(current[i], HEX);
        output->print(" ");
      }
      nilThdSleepMilliseconds(500);
      output->println();
    }
    output->println("-");
    nilThdSleepMilliseconds(getParameter(PARAM_DEBUG_DELAY));
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





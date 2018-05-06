
byte currentMax[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte maxHistory[16][5];
byte currentMaxSlot = 0;

void initMax() {
  for (byte i = 0; i < 16; i++) {
    for (byte j = 0; j < 5; j++) {
      maxHistory[i][j] = 0;
    }
  }
}


void updateMax() {
  byte newMaxSlot = millis() % (MIN_MAX_RESET * 1000 * 5) / (MIN_MAX_RESET * 1000);
  if (newMaxSlot != currentMaxSlot) {
    currentMaxSlot = newMaxSlot;
    for (byte i = 0; i < 16; i++) {
      maxHistory[i][currentMaxSlot] = 0;
    }
  }
  for (byte i = 0; i < 16; i++) {
    byte value = current[i];
    if (value > maxHistory[i][currentMaxSlot]) {
      maxHistory[i][currentMaxSlot] = value;
    }
  }
  for (byte i = 0; i < 16; i++) {
    currentMax[i] = 0;
    for (byte j = 0; j < 5; j++) {
      if (maxHistory[i][j] > currentMax[i]) {
        currentMax[i] = maxHistory[i][j];
      }
    }
  }
}


void printMax(Print * output) {

  for (byte i = 0; i < 16; i++) {
    output->print(i);
    output->print(" ");
    for (byte j = 0; j < 5; j++) {
      output->print(maxHistory[i][j], HEX);
      output->print(" ");
    }
    output->println(currentMax[i]);
  }


}

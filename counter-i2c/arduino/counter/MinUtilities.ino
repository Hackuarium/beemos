byte currentMin[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
byte minHistory[16][5];
byte currentMinSlot = 0;

void initMin() {
  for (byte i = 0; i < 16; i++) {
    for (byte j = 0; j < 5; j++) {
      minHistory[i][j] = 255;
    }
  }
}

void updateMin() {
  byte newMinSlot = millis() % (MIN_MAX_RESET * 1000 * 5) / (MIN_MAX_RESET * 1000);
  if (newMinSlot != currentMinSlot) {
    currentMinSlot = newMinSlot;
    for (byte i = 0; i < 16; i++) {
      minHistory[i][currentMinSlot] = 255;
    }
  }
  for (byte i = 0; i < 16; i++) {
    byte value = current[i];
    if (value < minHistory[i][currentMinSlot]) {
      minHistory[i][currentMinSlot] = value;
    }
  }
  for (byte i = 0; i < 16; i++) {
    currentMin[i] = 255;
    for (byte j = 0; j < 5; j++) {
      if (minHistory[i][j] < currentMin[i]) {
        currentMin[i] = minHistory[i][j];
      }
    }
  }
}

void printMin(Print * output) {
  for (byte i = 0; i < 16; i++) {
    output->print(i);
    output->print(" ");
    for (byte j = 0; j < 5; j++) {
      output->print(minHistory[i][j], HEX);
      output->print(" ");
    }
    output->println(currentMin[i]);
  }
}

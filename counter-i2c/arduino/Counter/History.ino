#define HISTORY_SIZE 15


byte history[16][HISTORY_SIZE];


byte currentHistorySlot = 0;

void initBackground() {
  for (byte i = 0; i < 16; i++) {
    for (byte j = 0; j < HISTORY_SIZE; j++) {
      history[i][j] = current[i];
    }
  }
}

byte getMedian(byte index) {
  byte arrayToSort[HISTORY_SIZE];
  byte numberNonZero = 0;
  for (byte i = 0; i < HISTORY_SIZE; i++) {
    arrayToSort[i] = history[index][i];
    if (arrayToSort[i] != 0)numberNonZero++;
  }
  for (byte i = 0; i < HISTORY_SIZE; i++) {
    for (byte j = i + 1; j < HISTORY_SIZE - 1; j++) {
      if (arrayToSort[j] > arrayToSort[i]) {
        byte tmp = arrayToSort[j];
        arrayToSort[j] = arrayToSort[i];
        arrayToSort[i] = tmp;
      }
    }
  }
  if (numberNonZero == 0) numberNonZero = 1;
  return arrayToSort[(numberNonZero - 1) / 2];
}

void updateBackground() {
  byte newHistorySlot = (millis() / 1000) % (MIN_MAX_RESET * HISTORY_SIZE) / MIN_MAX_RESET;
  for (byte i = 0; i < 16; i++) {
    history[i][newHistorySlot] = current[i];
  }

  for (byte i = 0; i < 16; i++) {
    background[i] = getMedian(i);
  }
}

void printBackground(Print * output) {
  for (byte i = 0; i < 16; i++) {
    output->print(i);
    output->print(" ");
    for (byte j = 0; j < HISTORY_SIZE; j++) {
      output->print(history[i][j], HEX);
      output->print(" ");
    }
    output->println(background[i]);
  }
}




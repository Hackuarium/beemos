#define THRESHOLD 20
#define THRESHOLD_RESET 10

long countIn[8] = {0, 0, 0, 0, 0, 0, 0, 0};
long countOut[8] = {0, 0, 0, 0, 0, 0, 0, 0};



void updateStatus() {
  for (byte gate = 0; gate < 8; gate++) {
    int inside = (int)currentMax[gate * 2] - (int) current[gate * 2];
    int outside = (int) currentMax[gate * 2 + 1] - (int) current[gate * 2 + 1];

    if (gateStatus[gate] == 0) {
      if (inside > THRESHOLD) {
        if (outside > THRESHOLD) { // both at the same time
          gateStatus[gate] = 3;
        } else { // from inside to ouside
          gateStatus[gate] = 1;
          countOut[gate]++;
        }
      } else {
        if (outside > THRESHOLD) { // from outside to inside
          gateStatus[gate] = 2;
          countIn[gate]++;
        }
      }
    } else {
      if ((inside < THRESHOLD_RESET) && (outside < THRESHOLD_RESET)) {
        gateStatus[gate] = 0;
      }
    }
  }
}

void printGateStatus() {
  for (byte i = 0; i < 8; i++) {
    Serial.print(i);
    Serial.print(" - out:");
    Serial.print(countOut[i]);
    Serial.print(" - in:");
    Serial.print(countIn[i]);
    Serial.print(" - ");
    switch (gateStatus[i]) {
      case 0:
        Serial.println("");
        break;
      case 1:
        Serial.println("outside");
        break;
      case 2:
        Serial.println("inside");
        break;
      case 3:
        Serial.println("both");
        break;

    }

  }
}




long countIn[8] = {0, 0, 0, 0, 0, 0, 0, 0};
long countOut[8] = {0, 0, 0, 0, 0, 0, 0, 0};
byte gateStatus[] = {0, 0, 0, 0, 0, 0, 0, 0};



void updateTotal() {
  for (byte gate = 0; gate < 8; gate++) {
    int inside = (int)currentMax[gate * 2] - (int) current[gate * 2];
    int outside = (int) currentMax[gate * 2 + 1] - (int) current[gate * 2 + 1];

    if (gateStatus[gate] == 0) {
      if (inside > getParameter(PARAM_THRESHOLD)) {
        if (outside > getParameter(PARAM_THRESHOLD)) { // both at the same time
          gateStatus[gate] = 3;
        } else { // from inside to ouside
          gateStatus[gate] = 1;
          countIn[gate]++;
        }
      } else {
        if (outside > getParameter(PARAM_THRESHOLD)) { // from outside to inside
          gateStatus[gate] = 2;
          countOut[gate]++;
        }
      }
    } else {
      if ((inside < getParameter(PARAM_THRESHOLD_RESET)) && (outside < getParameter(PARAM_THRESHOLD_RESET))) {
        gateStatus[gate] = 0;
      }
    }
  }
}

void printGateInfo() {
  for (byte gate = 0; gate < 8; gate++) {
    Serial.print(gate);
    Serial.print(" ");
    Serial.print(current[gate * 2]);
    Serial.print(" ");
    Serial.print(current[gate * 2 + 1]);

    //  Serial.print(" ");
    //  Serial.print(inside);
    //  Serial.print(" ");
    //  Serial.println(outside);
  }
}



void printTotal(Print* output) {
  for (byte k = 0; k < getParameter(PARAM_DEBUG_REPEAT); k++) {
    for (byte i = 0; i < 8; i++) {
      output->print(i);
      output->print(" - out:");
      output->print(countOut[i]);
      output->print(" - in:");
      output->print(countIn[i]);
      output->print(" - ");
      switch (gateStatus[i]) {
        case 0:
          output->println("");
          break;
        case 1:
          output->println("From outside");
          break;
        case 2:
          output->println("From inside");
          break;
        case 3:
          output->println("both");
          break;
      }
    }
    output->println("-");
    nilThdSleepMilliseconds(getParameter(PARAM_DEBUG_DELAY));
  }
}




byte gateStatus[] = {0, 0, 0, 0, 0, 0, 0, 0};

#define FIRST_PARAM_FOR_GATE 2

void updateTotal() {
  boolean debug = getParameter(PARAM_DEBUG_PRINT) == 1 ? true : false;
  for (byte gate = 0; gate < 8; gate++) {
    byte parameterID = gate * 2 + FIRST_PARAM_FOR_GATE;
    int inside = abs((int)background[gate * 2] - (int) current[gate * 2]);
    int outside = abs((int) background[gate * 2 + 1] - (int) current[gate * 2 + 1]);


    if (gateStatus[gate] == 0) {
      if (inside > getParameter(PARAM_THRESHOLD)) {
        if (outside > getParameter(PARAM_THRESHOLD)) { // both at the same time
          gateStatus[gate] = 3;
        } else { // from outside to inside
          gateStatus[gate] = 1;
          setParameter(parameterID, getParameter(parameterID) + 1);
          if (debug) {
            Serial.print("Gate ");
            Serial.print(gate + 1);
            Serial.println(": IN");
          }
        }
      } else {
        if (outside > getParameter(PARAM_THRESHOLD)) { // from inside to outside
          gateStatus[gate] = 2;
          setParameter(parameterID + 1, getParameter(parameterID + 1) + 1);
          if (debug) {
            Serial.print("Gate ");
            Serial.print(gate + 1);
            Serial.println(": OUT");
          }
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
    for (byte gate = 0; gate < 8; gate++) {
      byte parameterID = gate * 2 + FIRST_PARAM_FOR_GATE;
      output->print(gate);
      output->print(" - in:");
      output->print(getParameter(parameterID));
      output->print(" - out:");
      output->print(getParameter(parameterID + 1));
      output->print(" - ");
      switch (gateStatus[gate]) {
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


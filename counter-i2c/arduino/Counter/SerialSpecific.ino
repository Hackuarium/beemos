// testing serial monitoring commands.

void processSpecificCommand(char* data, char* paramValue, Print* output) {

  switch (data[0]) {
    case 'b':
      printBackground(output);
      break;
    case 'c':
      printCounter(output);
      break;
    case 'g':
      printGateInfo(output);
      break;
    case 'l':
      processLoggerCommand(data[1], paramValue, output);
      break;
    case 'r':
      resetCounter();
      break;
    case 't':
      printTotal(output);
      break;
  }
}

void printSpecificHelp(Print * output) {
  output->println(F("(b)ackground"));
  output->println(F("(c)ounter"));
  output->println(F("(g)ate debug bg"));
  output->println(F("(l)og"));
}


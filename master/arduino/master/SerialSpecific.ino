// testing serial monitoring commands.

void processSpecificCommand(char* data, char* paramValue, Print* output) {

  switch (data[0]) {
    case 'l':
      processLoggerCommand(data[1], paramValue, output);
      break;
  }
}

void printSpecificHelp(Print * output) {
  output->println(F("(l)og"));
}


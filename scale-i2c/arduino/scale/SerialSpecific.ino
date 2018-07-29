// testing serial monitoring commands.

void processSpecificCommand(char* data, char* paramValue, Print* output) {

  switch (data[0]) {
#ifdef THR_LOGGER
    case 'l':
      processLoggerCommand(data[1], paramValue, output);
      break;
#endif
    case 'w':
      processWeightCommand(data[1], paramValue, output);
      break;
  }
}

void printSpecificHelp(Print * output) {
#ifdef THR_LOGGER
  output->println(F("(l)og"));
#endif
  output->println(F("(w)eight"));
}


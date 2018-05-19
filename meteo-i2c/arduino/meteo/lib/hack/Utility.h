


void print2Digits(Print* output, int number) {
  // utility function for digital clock display: prints preceding colon and leading 0
  if(number < 10) output->print('0');
  output->print(number);
}

void epochToString(time_t time, Print* output) {
  // digital clock display of the time
  output->print(year(time)); 
  output->print("-");
  print2Digits(output,month(time));
  output->print("-");
  print2Digits(output,day(time));
  output->print(" ");
  print2Digits(output,hour(time));
  output->print(":");
  print2Digits(output,minute(time));
  output->print(":");
  print2Digits(output,second(time));
  output->print(" ");
}



void setupParameters() {
  //We copy all the values in the parameters table
  eeprom_read_block((void*)parameters, (const void*)EE_START_PARAM, MAX_PARAM * 2);
}

int getParameter(byte number) {
  return parameters[number];
}

void setParameterBit(byte number, byte bitToSet) {
  bitSet(parameters[number], bitToSet);
  // parameters[number]=parameters[number] | (1 << bitToSet);
}

void clearParameterBit(byte number, byte bitToClear) {
  bitClear(parameters[number], bitToClear);
  // parameters[number]=parameters[number] & ( ~ (1 << bitToClear));
}

byte getParameterBit(byte number, byte bitToRead) {
  return bitRead(parameters[number], bitToRead);
  // return (parameters[number] >> bitToRead ) & 1;
}

void setParameter(byte number, int value) {
  parameters[number] = value;
}

void incrementParameter(byte number) {
  parameters[number]++;
}

void saveParameters() {
  for (byte i = 0; i < MAX_PARAM; i++) {
    eeprom_write_word((uint16_t*) EE_START_PARAM + i, parameters[i]);
  }
}

/*
  This will take time, around 4 ms
  This will also use the EEPROM that is limited to 100000 writes
*/
void setAndSaveParameter(byte number, int value) {
  parameters[number] = value;
  //The address of the parameter is given by : EE_START_PARAM+number*2
  eeprom_write_word((uint16_t*) EE_START_PARAM + number, value);
}


void printParameter(Print* output, byte number) {
  output->print(number);
  output->print("-");
  if (number > 25) {
    output->print((char)(floor(number / 26) + 64));
  }
  else {
    output->print(" ");
  }
  output->print((char)(number - floor(number / 26) * 26 + 65));
  output->print(": ");
  output->println(parameters[number]);
}

void printParameters(Print* output) {
  for (int i = 0; i < MAX_PARAM; i++) {
    printParameter(output, i);
  }
}


uint8_t printCompactParameters(Print* output, byte number) {
  if (number > MAX_PARAM) {
    number = MAX_PARAM;
  }
  byte checkDigit = 0;

  // we first add epoch
  checkDigit ^= toHex(output, (long)now());
  for (int i = 0; i < number; i++) {
    int value = getParameter(i);
    checkDigit ^= toHex(output, value);
  }
  checkDigit ^= toHex(output, (int)getQualifier());
  toHex(output, checkDigit);
  output->println("");
}

uint8_t printCompactParameters(Print* output) {
  printCompactParameters(output, MAX_PARAM);
}

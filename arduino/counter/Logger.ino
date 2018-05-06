// part of the EEPROM is for the log
// we should be able to save and reload the log


#define DATA_SIZE 960
#define DATA_TYPE 0  // LONG

// log is saved in the format ID / in1 / out1 / ... / in8 / out8
// ID is a sequential number
// We expect to add an entry every hour

#define NUMBER_PARAMETERS_TO_LOG  17
#define LOG_ENTRY_LENGTH          NUMBER_PARAMETERS_TO_LOG*2
#define NUMBER_LOGS               28

#define FIRST_ADDRESS   1024-LOG_ENTRY_LENGTH*NUMBER_LOGS
#define LAST_ADDRESS   1023

void loggerInit() {
  // we need to reload the last ID
}

void writeLog() {
  int firstAddress = getFirstAddress(getParameter(PARAM_LOGID));
  setParameter(PARAM_LOGID, getParameter(PARAM_LOGID) + 1);
  for (byte i = 0; i < NUMBER_PARAMETERS_TO_LOG; i++) {
    eeprom_write_word((uint16_t*)  (firstAddress + i * 2), getParameter(i));
  }
}

void readLog(byte entryID) {
  int firstAddress = getFirstAddress(entryID);
  for (byte i = 0; i < NUMBER_PARAMETERS_TO_LOG; i++) {
    setParameter(i, eeprom_read_word((uint16_t*) (firstAddress + i * 2)));
  }
}

int getFirstAddress(int entryID) {
  return FIRST_ADDRESS + LOG_ENTRY_LENGTH * (entryID % NUMBER_LOGS);
}

void formatLog() {
  for (int i = FIRST_ADDRESS; i <= LAST_ADDRESS; i++) {
    eeprom_write_byte(i, 0);
  }
}

void printLog(Print* output) {
  for (byte i = 0; i < NUMBER_LOGS; i++) {
    output->print(i);
    output->print(" ");
    int firstAddress = getFirstAddress(i);
    for (byte j = 0; j < NUMBER_PARAMETERS_TO_LOG; j++) {
      output->print((int)eeprom_read_word((uint16_t*) (firstAddress + j * 2)));
      output->print(" ");
    }
    output->println("");
  }
}

NIL_WORKING_AREA(waThreadLogger, 0);
NIL_THREAD(ThreadLogger, arg) {
  nilThdSleepMilliseconds(1000);

  while (TRUE) {
    for (int i = 0; i < 3600; i++) { // sleep 1h

      writeLog();
    }
    nilThdSleepMilliseconds(1000);
  }
}




#ifdef LOGGER_I2C_EEPROM

/*
    Use the I2C bus with EEPROM 24LC64
    Sketch:    eeprom.pde
    Author: Internet
    Modified : David Lambelet
    Date: 13/08/2014
*/
#include <avr/interrupt.h>
#include <Wire.h> //I2C library


#define SIZE_MEMORY         65536       // M24512, 512 Kbits = 64Kbytes
#define MAX_MULTI_LOG       50          // only used to retrieve multilog

#define ENTRY_SIZE_LOGS     64          // Each log take 32 bytes
#define NB_PARAMETERS_LOGS  26
#define LOGGING_INTERVAL    15 * 60 // logging interval in seconds

#define NB_MAX_ENTRIES      (SIZE_MEMORY / ENTRY_SIZE_LOGS)  // parenthesis are required because it is substituted in the code
#define MAX_MULTI_LOG       1024          // only used to retrieve multilog

//#define DEBUG_FLAG 1


// on 4 bytes, define the log number and log local time
uint32_t nextEntryID = 0;


static byte Sensor_Acq = 0;


/********************
   Fonction for the Log
   // David Lambelet 30.08.2014
   // Modified Quentin Cabrol 2014.11
 **********************/

//default write log with event code 0 and parameter event 0
void writeLog() {
  writeLog(0x0000, 0x0000);
}

// The fonction log the parameters in the eeprom by block of 64bytes
// With a memory of 64kbytes, 1024 logs are possible
// the variable nextEntryID indicate the number of the log
void  writeLog (uint16_t event_number, uint16_t parameter_value) {

  protectThread();

  unsigned int logStartAddress = ENTRY_SIZE_LOGS * (nextEntryID % NB_MAX_ENTRIES);

  // LOGGING THE EPOCH
  i2c_eeprom_write_uint32(logStartAddress + 4, now());

  // LOGGING THE PARAMs
  // write to EEPROM 2 bytes per parameter
  for (int i = 0; i < NB_PARAMETERS_LOGS; i++) {
    i2c_eeprom_write_int(logStartAddress + (2 * i) + 8, getParameter(i));
  }


  // write to EEPROM 2 bytes for EVENT CODE, 2 bytes for EVENT PARAMETER
  i2c_eeprom_write_int(logStartAddress + ENTRY_SIZE_LOGS - 4, event_number);
  i2c_eeprom_write_int(logStartAddress * (nextEntryID % NB_MAX_ENTRIES) + ENTRY_SIZE_LOGS - 2, parameter_value);

  // LOGGING THE ID at the end so in case of crash this entry will be rewritten
  i2c_eeprom_write_uint32(logStartAddress, nextEntryID);

  unprotectThread();

  nextEntryID++;
}

// This fonction return the number of nextEntryID done
// The entry of the last log = nb nextEntryID-1;
// Have to be use to initialise the variable nextEntryID at the beginning
void find_lastEntry()
{
  nextEntryID = i2c_eeprom_read_uint32(0);
  uint32_t nextID;
  for (int i = 0; i < NB_MAX_ENTRIES; i++) {
    nextID = i2c_eeprom_read_uint32(ENTRY_SIZE_LOGS * i);
    if ((nextID > 0x0FFFFFFF) || (nextID < nextEntryID)) {
      return;
    }
    nextEntryID = nextID;
  }
  // very unexpected case, the last entryID is exactly at the last position of eeprom
}


uint32_t printLogN(Print* output, uint32_t entryN, bool relative ) {
  // Asking for an entry that is not yet on the card
  if (entryN >= nextEntryID || nextEntryID == 0) {
    return;
  }

  protectThread();

  // Are we asking for a log entry that is not on the card anymore ? Then we just start with the first that is on the card
  if ((nextEntryID >= NB_MAX_ENTRIES) && (entryN <= (nextEntryID - NB_MAX_ENTRIES))) {
    entryN = nextEntryID - NB_MAX_ENTRIES + 1;
  }

  uint32_t addressOfEntryN = entryN % NB_MAX_ENTRIES;
  byte checkDigit = 0;
  for (byte i = 0; i < ENTRY_SIZE_LOGS; i++) {
    byte oneByte = i2c_eeprom_read_byte(ENTRY_SIZE_LOGS * addressOfEntryN + i); //change to read byte
    checkDigit ^= toHex(output, oneByte);
  }
  checkDigit ^= toHex(output, (int)getQualifier());
  toHex(output, checkDigit);
  output->println("");
  unprotectThread();
  return entryN;

}

void printLastLog(Print* output) {
  printLogN(output, nextEntryID - 1, false);
}


//************************
// DEBUG UTILITIES
//************************


void print_logs_debug(Print* output) {
  protectThread();
  wdt_disable();
  int logStartAddress;
  for (int i = 0; i < NB_MAX_ENTRIES; i++) {
    logStartAddress = ENTRY_SIZE_LOGS * i;
    toHex(output, i);
    output->print(" ");

    toHex(output, (int)i2c_eeprom_read_int(logStartAddress)); // nextEntryID
    toHex(output, (int)i2c_eeprom_read_int(logStartAddress + 2));
    output->print(" ");

    toHex(output, (int)i2c_eeprom_read_int(logStartAddress + 4)); // time
    toHex(output, (int)i2c_eeprom_read_int(logStartAddress + 6)); // time
    output->print(" ");

    for (int i = 0; i < NB_PARAMETERS_LOGS; i++) {
      toHex(output, i2c_eeprom_read_int(logStartAddress + (2 * i) + 8)); // time
      output->print(" ");
    }

#ifndef MODE_MEMORY_SAVE
    toHex(output, i2c_eeprom_read_int(logStartAddress + ENTRY_SIZE_LOGS - 4)); // eventID
    output->print(" ");

    toHex(output, i2c_eeprom_read_int(logStartAddress + ENTRY_SIZE_LOGS - 2)); // event parameter
#endif
    output->println("");
  }
  unprotectThread();
  wdt_enable(WDTO_8S);
  wdt_reset();
}


/********************
   Fonction for the external I2C EEPROM, taken from Arduino website
 **********************/

void i2c_eeprom_write_byte(unsigned int eeaddress, byte data ) {
  int rdata = data;
  Wire.beginTransmission(LOGGER_I2C_EEPROM);
  Wire.write((byte)(eeaddress >> 8)); // MSB
  Wire.write((byte)(eeaddress & 0xFF)); // LSB
  Wire.write(rdata);
  Wire.endTransmission();
  nilThdSleepMilliseconds(5); // specifications required 5ms
}

byte i2c_eeprom_read_byte(unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(LOGGER_I2C_EEPROM);
  Wire.write((byte)(eeaddress >> 8)); // MSB
  Wire.write((byte)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(LOGGER_I2C_EEPROM, 1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}

void i2c_eeprom_write_int(unsigned int eeaddress, int data ) {
  Wire.beginTransmission(LOGGER_I2C_EEPROM);
  Wire.write((byte)(eeaddress >> 8)); // MSB
  Wire.write((byte)(eeaddress & 0xFF)); // LSB
  Wire.write((byte)((data >> 8) & 0xFF));
  Wire.write((byte)((data >> 0) & 0xFF));
  Wire.endTransmission();
  nilThdSleepMilliseconds(5); // specifications required 5ms
}

int i2c_eeprom_read_int(unsigned int eeaddress ) {
  Wire.beginTransmission(LOGGER_I2C_EEPROM);
  Wire.write((byte)(eeaddress >> 8)); // MSB
  Wire.write((byte)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(LOGGER_I2C_EEPROM, 2);
  return (Wire.read() << 8) + (Wire.read() << 0);
}

void i2c_eeprom_write_uint32(unsigned int eeaddress, uint32_t data ) {
  Wire.beginTransmission(LOGGER_I2C_EEPROM);
  Wire.write((byte)(eeaddress >> 8)); // MSB
  Wire.write((byte)(eeaddress & 0xFF)); // LSB
  Wire.write((byte)((data >> 24) & 0xFF));
  Wire.write((byte)((data >> 16) & 0xFF));
  Wire.write((byte)((data >> 8) & 0xFF));
  Wire.write((byte)((data >> 0) & 0xFF));;
  Wire.endTransmission();
  nilThdSleepMilliseconds(5); // specifications required 5ms
}

uint32_t i2c_eeprom_read_uint32(unsigned int eeaddress ) {
  Wire.beginTransmission(LOGGER_I2C_EEPROM);
  Wire.write((byte)(eeaddress >> 8)); // MSB
  Wire.write((byte)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(LOGGER_I2C_EEPROM, 4);
  return (((uint32_t)Wire.read()) << 24) + (((uint32_t)Wire.read()) << 16) + (((uint32_t)Wire.read()) << 8) + (((uint32_t)Wire.read()) << 0);
}


void formatLog(Print* output) {
  // We may write per block and internal Wire buffer is 32 bytes
  protectThread();
  wdt_disable();
  output->println(F("Formatting flash"));
  for (unsigned int i = 0; i < (SIZE_MEMORY / 16); i++) {
    Wire.beginTransmission(LOGGER_I2C_EEPROM);
    Wire.write((int)((i * 16) >> 8)); // MSB
    Wire.write((int)((i * 16) & 0xFF)); // LSB
    for (byte j = 0; j < 16; j++) {
      Wire.write(0xFF);
    }
    Wire.endTransmission();
    nilThdSleepMilliseconds(5); // no thread should work while formatting - specifications required 5ms
    if (!(i % 256)) {
      output->print( i * 16 );
      output->print(" / ");
      output->println(SIZE_MEMORY);
    }
  }
  output->println(F("Done"));
  wdt_enable(WDTO_8S);
  wdt_reset();
  nextEntryID = 0;
  unprotectThread();
  writeLog();
}


/*************************************
   I2C EEPROM THREAD
 **************************************/
NIL_WORKING_AREA(waThreadLogger, 100);
NIL_THREAD(ThreadLogger, arg) {

  nilThdSleepMilliseconds(5000);

  Wire.begin();

  // reading last entry and
  protectThread();
  find_lastEntry();
  //set time to last recorded
  setTime(i2c_eeprom_read_uint32( ENTRY_SIZE_LOGS * (nextEntryID % NB_MAX_ENTRIES) + 4));
  unprotectThread();

  writeLog(EVENT_ARDUINO_BOOT, 0x0000);

  while (TRUE) {
    for (int i = 0; i < LOGGING_INTERVAL; i++) {
      nilThdSleepMilliseconds(1000);
    }
    writeLog();
  }
}

void processLoggerCommand(char command, char* data, Print* output) {
  switch (command) {
    case 'd':
      print_logs_debug(output);
      break;
    case 'f':
      if (data[0] == '\0' || atoi(data) != 1234) {
        output->println(F("Format enter lf1234"));
      } else {
        formatLog(output);

      }
      break;
    case 'l':
      if (data[0] != '\0')
        printLogN(output, atol(data), false);
      else
        printLastLog(output);
      break;
    case 'm':
    case 'r':
      if (data[0] != '\0') {
        long currentValueLong = atol(data);
        int endValue = MAX_MULTI_LOG;
        if (currentValueLong >= nextEntryID) {
          endValue = 0;
        } else if (( nextEntryID - currentValueLong ) > NB_MAX_ENTRIES) {
          currentValueLong = nextEntryID - NB_MAX_ENTRIES;
        }
        if (( nextEntryID - currentValueLong ) < MAX_MULTI_LOG) {
          endValue = nextEntryID - currentValueLong;
        }
        for (int i = 0; i < endValue; i++) {
          printLogN(output, currentValueLong + i, (command == 'r'));
          nilThdSleepMilliseconds(25);
        }
      }
      else {
        output->println(nextEntryID - 1);
      }
      break;
    case 'w':
      writeLog();
      break;
    default:
      printLoggerHelp(output);
  }
}

void printLoggerHelp(Print * output) {
  output->println(F("Logger help"));
  output->println(F("(ld) Dump"));
  output->println(F("(lf) Format"));
  output->println(F("(ll) Current log"));
  output->println(F("(lm) Multiple logs"));
  output->println(F("(lr) Relative logs"));
  output->println(F("(lw) Write log"));
}

#endif




#include <EEPROM.h>

/* The qualifier represents the card ID and is stored just after the last
 * parameter */
uint16_t getQualifier() {
  uint16_t q;
  EEPROM.get(EE_QUALIFIER, q);
  return q;
  }

void setQualifier(uint16_t value) {
  EEPROM.put(EE_QUALIFIER, value);
EEPROM.commit();  
}

void setDataInt16(int16_t address, int16_t value) {
  EEPROM.put(address, value);
  EEPROM.commit();  
}

int16_t getDataInt16(int16_t address) {
 int16_t data;
 EEPROM.get(address, data);
 return data;
}


long getDataByte(int16_t address) {
 byte data;
 EEPROM.get(address, data);
 return data;
}

// code from http://www.arduino.cc/playground/Code/EepromUtil
void getStatusEEPROM(Print *output) {
  int bytesPerRow = 16;
  int i;
  int j;
  byte b;
  char buf[4];

  j = 0;

  // go from first to last eeprom address
  for (i = EEPROM_MIN_ADDR; i <= EEPROM_MAX_ADDR; i++) {
    if (j == 0) {
      sprintf(buf, "%03X", i);
      output->print(buf);
      output->print(F(": "));
    }

    // read current byte from eeprom
    b = getDataByte(i);
    sprintf(buf, "%02X ", b);
    j++;
    if (j == bytesPerRow) {
      j = 0;
      output->println(buf);
    } else {
      output->print(buf);
    }
  }
}

#include <avr/eeprom.h>

#define INT_MAX_VALUE       32767
#define INT_MIN_VALUE       -32768
#define LONG_MAX_VALUE      2147483647

// value that should not be taken into account
// in case of error the parameter is set to this value
#define ERROR_VALUE  -32768

#define EE_START_PARAM           0 // We save the parameter from byte 0 of EEPROM
#define EE_LAST_PARAM            (MAX_PARAM*2-1) // The last parameter is stored at byte 50-51

#define EE_QUALIFIER             (MAX_PARAM*2)

#define EEPROM_MIN_ADDR            0
#define EEPROM_MAX_ADDR          1023




int parameters[MAX_PARAM];
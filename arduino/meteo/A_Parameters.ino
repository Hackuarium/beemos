/*********************************************
   This file is used to declare the parameters
   table used by the program.

   We use the EEPROM for saving the parameters
   changed by the user during the functionment
   of the Bioreactor.

   The parameters are loaded during the boot.

   All important changes made on a parameter are saved
   in the EEPROM.
 *********************************************/


#define MAX_PARAM 26   // If the MAX_PARAM change you need to change the pointer in the EEPROM

#define PARAM_LOGID               0
#define PARAM_SECONDS             1 // number of secodns since the last log
#define PARAM_TEMPERATURE_EXT     2
#define PARAM_TEMPERATURE_IN      3
#define PARAM_TEMPERATURE_BOARD   4
#define PARAM_HUMIDITY            5
#define PARAM_HUMIDITY_TEMP       6
#define PARAM_LUMINOSITY          7
#define PARAM_PRESSURE            8


#define PARAM_LOGGING_INTERVAL    24    // minimal 300s to prevent desctruction of EEPROM. Should last 22 years with 300s

// you may write in EEPROM max 100'000 times
// 100'000 * 300 * 24 (number of line of log) / 365 / 86400

#define INT_MAX_VALUE       32767
#define LONG_MAX_VALUE      2147483647

void resetParameters() { // turn all parameters to 0
  setAndSaveParameter(PARAM_SECONDS, 0);
  setAndSaveParameter(PARAM_LOGGING_INTERVAL, 3600);


  formatLog();
  setQualifier(32767);
}

void checkParameters() {
  if (getParameter(PARAM_LOGGING_INTERVAL) < 0) {
    resetParameters();
  }
}


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


#define PARAM_LOGID               0
#define PARAM_SECONDS             1 // number of secodns since the last log
#define PARAM_WEIGHT              2
#define PARAM_WEIGHT_G            3
#define PARAM_WEIGHT_OFFSET       4
#define PARAM_WEIGHT_FACTOR       5
#define PARAM_WEIGHT_MIN          6
#define PARAM_WEIGHT_MAX          7

#define PARAM_POWER_5V            13
#define PARAM_LOGGING_INTERVAL    14    // minimal 300s to prevent desctruction of EEPROM. Should last 22 years with 300s
#define PARAM_SLEEP_DELAY         15

// you may write in EEPROM max 100'000 times
// 100'000 * 300 * 24 (number of line of log) / 365 / 86400


void resetParameters() { // turn all parameters to 0
  setAndSaveParameter(PARAM_SECONDS, 0);
  setAndSaveParameter(PARAM_LOGGING_INTERVAL, 3600);
  setAndSaveParameter(PARAM_SLEEP_DELAY, 10);

  setAndSaveParameter(PARAM_WEIGHT, PARAM_SLEEP_DELAY);
  setAndSaveParameter(PARAM_WEIGHT_G, ERROR_VALUE);
  setAndSaveParameter(PARAM_WEIGHT_OFFSET, ERROR_VALUE);
  setAndSaveParameter(PARAM_WEIGHT_FACTOR, ERROR_VALUE);
  setAndSaveParameter(PARAM_WEIGHT_MIN, ERROR_VALUE);
  setAndSaveParameter(PARAM_WEIGHT_MAX, ERROR_VALUE);
  setAndSaveParameter(PARAM_POWER_5V, ERROR_VALUE);

#ifdef THR_LOGGER
  formatLog();
#endif
  setQualifier(ERROR_VALUE);
}

void initParameters() {
  
}

void checkParameters() {
  if (getParameter(PARAM_LOGGING_INTERVAL) < 0) {
    resetParameters();
  }
}



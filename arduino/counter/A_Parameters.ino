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

#define PARAM_LOGID         0
#define PARAM_GATE1_IN      1
#define PARAM_GATE1_OUT     2
#define PARAM_GATE2_IN      3
#define PARAM_GATE2_OUT     4
#define PARAM_GATE3_IN      5
#define PARAM_GATE3_OUT     6
#define PARAM_GATE4_IN      7
#define PARAM_GATE4_OUT     8
#define PARAM_GATE5_IN      9
#define PARAM_GATE5_OUT     10
#define PARAM_GATE6_IN      11
#define PARAM_GATE6_OUT     12
#define PARAM_GATE7_IN      13
#define PARAM_GATE7_OUT     14
#define PARAM_GATE8_IN      15
#define PARAM_GATE8_OUT     16

#define PARAM_DEBUG_REPEAT  20
#define PARAM_DEBUG_DELAY   21


#define INT_MAX_VALUE       32767
#define LONG_MAX_VALUE      2147483647


void resetParameters() { // turn all parameters to 0

  setAndSaveParameter(PARAM_DEBUG_REPEAT, 20);
  setAndSaveParameter(PARAM_DEBUG_DELAY, 500);

  setQualifier(32767);
}

void checkParameters() {
  if (getParameter(PARAM_DEBUG_REPEAT) < 0) {
    resetParameters();
  }
}


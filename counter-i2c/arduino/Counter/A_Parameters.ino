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




#define PARAM_LOGID         0
#define PARAM_SECONDS       1 // number of secodns since the last log
#define PARAM_GATE1_IN      2
#define PARAM_GATE1_OUT     3
#define PARAM_GATE2_IN      4
#define PARAM_GATE2_OUT     5
#define PARAM_GATE3_IN      6
#define PARAM_GATE3_OUT     7
#define PARAM_GATE4_IN      8
#define PARAM_GATE4_OUT     9
#define PARAM_GATE5_IN      10
#define PARAM_GATE5_OUT     11
#define PARAM_GATE6_IN      12
#define PARAM_GATE6_OUT     13
#define PARAM_GATE7_IN      14
#define PARAM_GATE7_OUT     15
#define PARAM_GATE8_IN      16
#define PARAM_GATE8_OUT     17

#define PARAM_THRESHOLD           20
#define PARAM_THRESHOLD_RESET     21
#define PARAM_DEBUG_REPEAT        22
#define PARAM_DEBUG_DELAY         23
#define PARAM_LOGGING_INTERVAL    24    // minimal 300s to prevent desctruction of EEPROM. Should last 22 years with 300s
// disable if less than 300
#define PARAM_DEBUG_PRINT         25

#define PARAM_GATE1_BG_IN      26
#define PARAM_GATE1_BG_OUT     27
#define PARAM_GATE2_BG_IN      28
#define PARAM_GATE2_BG_OUT     29
#define PARAM_GATE3_BG_IN      30
#define PARAM_GATE3_BG_OUT     31
#define PARAM_GATE4_BG_IN      32
#define PARAM_GATE4_BG_OUT     33
#define PARAM_GATE5_BG_IN      34
#define PARAM_GATE5_BG_OUT     35
#define PARAM_GATE6_BG_IN      36
#define PARAM_GATE6_BG_OUT     37
#define PARAM_GATE7_BG_IN      38
#define PARAM_GATE7_BG_OUT     39
#define PARAM_GATE8_BG_IN      40
#define PARAM_GATE8_BG_OUT     41


void resetParameters() { // turn all parameters to 0
  for (byte i = 0; i < 18; i++) {
    setAndSaveParameter(i, 0);
  }
  setAndSaveParameter(PARAM_THRESHOLD, 5);
  setAndSaveParameter(PARAM_THRESHOLD_RESET, 2);
  setAndSaveParameter(PARAM_DEBUG_REPEAT, 50);
  setAndSaveParameter(PARAM_DEBUG_DELAY, 500);
  setAndSaveParameter(PARAM_LOGGING_INTERVAL, 0);
  setAndSaveParameter(PARAM_DEBUG_PRINT, 0);
#ifdef LOGGER
  formatLog();
#endif
  setQualifier(32767);
}

void initParameters() {}

void checkParameters() {
  if (getParameter(PARAM_DEBUG_REPEAT) < 0) {
    resetParameters();
  }
}


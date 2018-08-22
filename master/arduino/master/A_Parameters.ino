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

#define PARAM_EXT_TEMPERATURE     0
#define PARAM_EXT_HUMIDITY        1
#define PARAM_LUMINOSITY          2
#define PARAM_PRESSURE            3
#define PARAM_INT_TEMPERATURE     6
#define PARAM_INT_HUMIDITY        5
#define PARAM_INT_TEMPERATURE_A   6
#define PARAM_INT_TEMPERATURE_B   7
#define PARAM_WEIGHT_G            8
#define PARAM_BATTERY             9
#define PARAM_GATE1_IN            10
#define PARAM_GATE1_OUT           11
#define PARAM_GATE2_IN            12
#define PARAM_GATE2_OUT           13
#define PARAM_GATE3_IN            14
#define PARAM_GATE3_OUT           15
#define PARAM_GATE4_IN            16
#define PARAM_GATE4_OUT           17
#define PARAM_GATE5_IN            18
#define PARAM_GATE5_OUT           19
#define PARAM_GATE6_IN            20
#define PARAM_GATE6_OUT           21
#define PARAM_GATE7_IN            22
#define PARAM_GATE7_OUT           23
#define PARAM_GATE8_IN            24
#define PARAM_GATE8_OUT           25


#define PARAM_WEIGHT              26
#define PARAM_WEIGHT_OFFSET       27
#define PARAM_WEIGHT_FACTOR       28

#define PARAM_CHARGING            29
#define PARAM_LOGGING_INTERVAL    30    // minimal 300s to prevent desctruction of EEPROM. Should last 22 years with 300s

// you may write in EEPROM max 100'000 times
// 100'000 * 300 * 24 (number of line of log) / 365 / 86400

// Definition of all events to be logged
#define EVENT_ARDUINO_BOOT           1

void resetParameters() { // turn all parameters to 0
  setAndSaveParameter(PARAM_LOGGING_INTERVAL, 3600);

  for (byte i = 0; i < 26; i++) {
    setAndSaveParameter(i, ERROR_VALUE);
  }

//  formatLog(&Serial);
  setQualifier(32767);
}

// This will be executed once on boot
void initParameters() {}

void checkParameters() {
  if (getParameter(PARAM_LOGGING_INTERVAL) < 0) {
    resetParameters();
  }
}


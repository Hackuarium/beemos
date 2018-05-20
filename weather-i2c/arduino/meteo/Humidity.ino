#include "lib/dht/DHT_U.h"


#define DHTPIN            6
#define DHTTYPE           DHT22  
#define DHT_POWER         7

DHT_Unified dht(DHTPIN, DHTTYPE);

NIL_WORKING_AREA(waThreadHumidity, 128);

NIL_THREAD(ThreadHumidity, arg) {

  nilThdSleepMilliseconds(1000);

  pinMode(DHT_POWER, OUTPUT);
 

  while (true) {
    getHumidityTemperature();
    nilThdSleepMilliseconds(1000);
  }
}

void getHumidityTemperature() {
  digitalWrite(DHT_POWER, HIGH);
  dht.begin();
  nilThdSleepMilliseconds(2000); //  need 2s to get data.

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  
  if (isnan(event.temperature)) {
    setParameter(PARAM_HUMIDITY_TEMP ,ERROR_VALUE);
  } else {
    setParameter(PARAM_HUMIDITY_TEMP ,event.temperature*100);
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
      setParameter(PARAM_HUMIDITY ,ERROR_VALUE);
  } else {
     setParameter(PARAM_HUMIDITY ,event.relative_humidity*100);
  }
}



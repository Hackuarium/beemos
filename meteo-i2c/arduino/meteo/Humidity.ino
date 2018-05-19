#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            6
#define DHTTYPE           DHT22  
#define DHT_POWER         7

NIL_WORKING_AREA(waThreadHumidify, 128);

NIL_THREAD(ThreadHumidify, arg) {

  nilThdSleepMilliseconds(1000);
// dht.begin();

  pinMode(DHT_POWER, OUTPUT);
  digitalWrite(DHT_POWER, HIGH);

  while (true) {
    
    nilThdSleepMilliseconds(1000);
  }
}



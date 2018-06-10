// The library DHT was changed to be compatible with nilRTOS

#define nilThdSleepMilliseconds delay

#include "lib/dht/DHT_U.h"


#define DHTPIN            6         // Pin which is connected to the DHT sensor.


DHT_Unified dht(DHTPIN);

void setup() {
  pinMode(7, OUTPUT);

  Serial.begin(9600);

}

int before, after;

void loop() {
  digitalWrite(7, HIGH);
  dht.begin();
  getHumidityTemperature();
  Serial.println("");
  digitalWrite(7, LOW);
}


void getHumidityTemperature() {
  nilThdSleepMilliseconds(2000); //  need 2s to get data.

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  } else {
    Serial.print("  Temperature: ");
    Serial.print(event.temperature);
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  } else {
    Serial.print("  Humidity: ");
    Serial.print(event.relative_humidity);
  }
}


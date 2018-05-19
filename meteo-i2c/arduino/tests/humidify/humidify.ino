
#include "lib/DHT_U.h"



#define DHTPIN            6         // Pin which is connected to the DHT sensor.

#define DHTTYPE           DHT22     // DHT 22 (AM2302)


DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(7, OUTPUT);

  Serial.begin(9600);

}

int before, after;

void loop() {
  before = random(0, 10);
  after = random(0, 10);
  Serial.print("beforeOn: ");
  Serial.print(before);
  Serial.print("  afterOn: ");
  Serial.print(after);
  delay(before * 1000);
  digitalWrite(7, HIGH);
  dht.begin();
  delay(after * 1000);
  getHumidityTemperature();
   Serial.println("");
  digitalWrite(7, LOW);


}


void getHumidityTemperature() {
  delay(2000); //  need 2s to get data.

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


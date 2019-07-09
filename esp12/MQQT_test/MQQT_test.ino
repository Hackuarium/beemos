/*****

  All the resources for this project:
  https://randomnerdtutorials.com/

*****/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// #include "DHT.h"

//si7021
#include "SparkFun_Si7021_Breakout_Library.h"
#include <Wire.h>
float humidity = 0;
float tempSi = 0;
//Create Instance of SI7021 temp and humidity sensor
Weather sensor;

// Dallas
#include <OneWire.h>
OneWire  ds(2);  // on pin 2 (a 4.7K resistor is necessary)
float tempb = 0; // on board temperature
float temp1 = 0; // temperature sensor 1
float temp2 = 0; // temperature sensor 2
// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.1.223";  //"mqqt.beemos.org"

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient espClient;
PubSubClient client(espClient);

// DHT Sensor - GPIO 5 = D1 on ESP-12E NodeMCU board
//const int DHTPin = 5;

// Lamp - LED - GPIO 4 = D2 on ESP-12E NodeMCU board
//const int lamp = 4;

// Initialize DHT sensor.
//DHT dht(DHTPin, DHTTYPE);

// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic room/lamp, you check if the message is either on or off. Turns the lamp GPIO according to the message
  if (topic == "room/lamp") {
    Serial.print("Changing Room lamp to ");
    if (messageTemp == "on") {
      //digitalWrite(lamp, HIGH);
      Serial.print("On");
    }
    else if (messageTemp == "off") {
      // digitalWrite(lamp, LOW);
      Serial.print("Off");
    }
  }
  Serial.println();
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    /*
      YOU MIGHT NEED TO CHANGE THIS LINE, IF YOU'RE HAVING PROBLEMS WITH MQTT MULTIPLE CONNECTIONS
      To change the ESP device ID, you will have to give a new name to the ESP8266.
      Here's how it looks:
       if (client.connect("ESP8266Client")) {
      You can do it like this:
       if (client.connect("ESP1_Office")) {
      Then, for the other ESP:
       if (client.connect("ESP2_Garage")) {
      That should solve your MQTT multiple connections problem
    */
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("room/lamp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs

void setup() {
  //pinMode(lamp, OUTPUT);
  //dht.begin();

  Serial.begin(9600);
  setup_wifi();
  pinMode(A0, INPUT); // to get battery value
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //Initialize the I2C sensors and ping them
  sensor.begin();
}

// For this project, you don't need to change anything in the loop function. Basically it ensures that you ESP is connected to your broker
void loop() {

  Serial.println("***********************START*******************************"); // indicates each start of loop
  for (byte j = 0; j < 3; j++) {
    byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius, fahrenheit;

    // ds.search(addr);

    if ( !ds.search(addr)) {
      Serial.println("No more addresses.");
      Serial.println();
      ds.reset_search();
      delay(250);
      return;
    }

    Serial.print("ROM =");
    for ( i = 0; i < 8; i++) {
      Serial.write(' ');
      Serial.print(addr[i], HEX);
    }

    if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
    }
    Serial.println();

    // the first ROM byte indicates which chip
    //  switch (addr[0]) {
    //    case 0x10:
    //      Serial.println("  Chip = DS18S20");  // or old DS1820
    //      type_s = 1;
    //      break;
    //    case 0x28:
    //      Serial.println("  Chip = DS18B20");
    //      type_s = 0;
    //      break;
    //    case 0x22:
    //      Serial.println("  Chip = DS1822");
    //      type_s = 0;
    //      break;
    //    default:
    //      Serial.println("Device is not a DS18x20 family device.");
    //      return;
    //  }

    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end

    delay(1000);     // maybe 750ms is enough, maybe not
    // we might do a ds.depower() here, but the reset will take care of it.

    present = ds.reset();
    ds.select(addr);
    ds.write(0xBE);         // Read Scratchpad

    //Serial.print("  Data = ");
    //Serial.print(present, HEX);
    //  Serial.print(" ");
    for ( i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
      // Serial.print(data[i], HEX);
      // Serial.print(" ");
    }
    //  Serial.print(" CRC=");
    //  Serial.print(OneWire::crc8(data, 8), HEX);
    //  Serial.println();

    // Convert the data to actual temperature
    // because the result is a 16 bit signed integer, it should
    // be stored to an "int16_t" type, which is always 16 bits
    // even when compiled on a 32 bit processor.
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s) {
      raw = raw << 3; // 9 bit resolution default
      if (data[7] == 0x10) {
        // "count remain" gives full 12 bit resolution
        raw = (raw & 0xFFF0) + 12 - data[6];
      }
    } else {
      byte cfg = (data[4] & 0x60);
      // at lower res, the low bits are undefined, so let's zero them
      if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
      else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
      else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
      //// default is 12 bit resolution, 750 ms conversion time
    }
    celsius = (float)raw / 16.0;
    //fahrenheit = celsius * 1.8 + 32.0;
    switch (j) {
      case 0:
        temp2 = celsius;
        break;
      case 1:
        temp1 = celsius;
        break;
      case 2:
        tempb = celsius;
    }
    Serial.print("  Temperature = ");
    Serial.print(celsius);
    Serial.println("°C ");
    //Serial.print(fahrenheit);
    //Serial.println(" Fahrenheit");
  }
  //Get readings from Si7021
  getWeather();
  printInfo();
  Serial.println("***********************END*******************************"); // indicates each start of loop
  delay(1000);

  ///////////////////////////////////////
  if (!client.connected()) {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  // Publishes new values every 5 seconds
  if (now - lastMeasure > 5000) {
    lastMeasure = now;
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float battLevel = ((double)analogRead(A0)) / 1024 * 4.70;
    // convertion to string float
    char battLevelX[4];
    dtostrf(battLevel, 4, 2, battLevelX);
    // Publishes battLevel values
    client.publish("Mboard/batteryV", battLevelX);
    // publish temperatures / humidity
    char tempbX[3];
    dtostrf(tempb, 3, 1, tempbX);
    // Publishes tempB values
    client.publish("Mboard/tempB", tempbX);
    char temp1X[4];
    dtostrf(temp1, 4, 1, temp1X);
    // Publishes temp1 values
    client.publish("internal/temp1", temp1X);
    char temp2X[4];
    dtostrf(temp2, 4, 1, temp2X);
    // Publishes temp2 values
    client.publish("internal/temp2", temp2X);
    char tempSiX[3];
    dtostrf(tempSi, 3, 1, tempSiX);
    // Publishes tempSi values
    client.publish("internal/tempSi", tempSiX);
    char humidityX[3];
    dtostrf(humidity, 3, 1, humidityX);
    // Publishes tempSi humidity values
    client.publish("internal/humidity", humidityX);

    Serial.print("Battery voltage: ");
    Serial.println(battLevel);
    Serial.print("Master board temperature: ");
    Serial.println(tempb);
    Serial.print("Temperature1: ");
    Serial.println(temp1);
    Serial.print("Temperature2: ");
    Serial.println(temp2);
    Serial.print("Si temperature: ");
    Serial.println(tempSi);
    Serial.print("Si humidity: ");
    Serial.println(humidity);
  }
}


void getWeather()
{
  // Measure Relative Humidity from the HTU21D or Si7021
  humidity = sensor.getRH();

  // Measure Temperature from the HTU21D or Si7021
  tempSi = sensor.getTemp();
  // Temperature is measured every time RH is requested.
  // It is faster, therefore, to read it from previous RH
  // measurement with getTemp() instead with readTemp()
}
//---------------------------------------------------------------
void printInfo()
{
  //This function prints the weather data out to the default Serial Port
  Serial.print(" Si7021 Temp:");
  Serial.print(tempSi);
  Serial.print("°C, ");

  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.println("%\n");
}

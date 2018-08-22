
#include <Wire.h>

// I2C address of the M24512, 0x50(80)
#define M24512_ADDR 0x50



void setup() {


  Wire.begin();

  Serial.begin(9600);

  // set memory power pin
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH); // power on memory
  delay(100);

}

uint32_t address = 0;
uint8_t data = 0;
uint8_t dataRead = 0;

void loop() {
  address++;
  data++;

  Wire.beginTransmission(M24512_ADDR);
  // Select write address register
  Wire.write(address >> 8);
  Wire.write(address & 255);
  // Write the data
  Wire.write(data);
  // End I2C transmission
  Wire.endTransmission();

  delay(10); // some delay is necessary !!!!!!!
  address = address & 65535;

  Wire.beginTransmission(M24512_ADDR);
  Wire.write(address >> 8);
  Wire.write(address & 255);
  Wire.endTransmission();
  // Request 1 byte of data
  Wire.requestFrom(M24512_ADDR, 1);

  // Read 1 byte of data
  if (Wire.available() == 1) {
    dataRead = Wire.read();
  }

  // Output data to serial monitor
  Serial.print("Address: ");
  Serial.print(address);
  Serial.print(" - Write: ");
  Serial.print(data);
  Serial.print(" - Read: ");
  Serial.println(dataRead);
  delay(10);
}


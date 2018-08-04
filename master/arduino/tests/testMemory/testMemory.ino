
#include <Wire.h>

// I2C address of the M24512, 0x50(80)
#define M24512_ADDR 0x50



void setup() {

  
  Wire.begin();
 
  Serial.begin(9600);

  // set memory power pin
  pinMode(9, OUTPUT);


}

uint8_t data;

void loop() {
  digitalWrite(9, HIGH); // power on memory
  delay(100);
  
  Wire.beginTransmission(M24512_ADDR);
  // Select write address register
  Wire.write(0x00);
  Wire.write(0x01);
  // Write the data
  Wire.write(0x30);
  // End I2C transmission
  Wire.endTransmission();
  delay(300);


  // Request 1 byte of data
  Wire.requestFrom(M24512_ADDR, 1);

  // Read 1 byte of data
  if (Wire.available() == 1) {
    data = Wire.read();
  }

  // Output data to serial monitor
  Serial.print("Input data : ");
  Serial.println(data);
  delay(1000);
}


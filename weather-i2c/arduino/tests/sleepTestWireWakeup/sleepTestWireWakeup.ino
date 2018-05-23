#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include <Wire.h>

void requestEvent() {
  Wire.write(random(0,255));
}

void receiveEvent() {
  while (Wire.available()) { // loop through all but the last
    Wire.read(); // receive byte as a character
  }
}

void startWireSlave() {
  Wire.begin(55);       // join i2c bus with address #55
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}

// Enters the arduino into sleep mode.
void enterSleep(void) {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS);

  uint8_t analogStatus = ADCSRA & (1 << ADEN);
  ADCSRA &= ~(1 << ADEN); //Disable ADC: allows to win 80µA

  // Now enter sleep mode.
  sleep_mode();

  ADCSRA |= analogStatus;
}

void setup() {
  pinMode(2, INPUT_PULLUP); // INT.0 should not flip when sleeping
  pinMode(3, INPUT_PULLUP); // INT.1 should not flip when sleeping
  startWireSlave();
  delay(5000);
}
void loop() {
  enterSleep();
  delay(5);
}

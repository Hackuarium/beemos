

In use: 6 to 8 mA

Without sensors: 6.37 mA

In sleep mode it consume 100µA


It is possible to wake up the slave based on the i2C address. In order to go to sleep the I2C line has to be set to LOW

## Testing consumption of Master / Slave

One `Master Simple` is connect to a `weather-i2c` board in order to show the sleep mode and the possibility for wake-up.

The ATmega328 has various sleep mode:
* idle
* ADC noise reduction
* extended standby
* standby
* power-save
* power-down

It is really the last mode that is the more interesting and allow to reduce dramatically the power consumption. From this mode there are various wake-up procedure and among them:
* external level interrupt on INT.0 or INT.1 (D2 and D3)
* watchdog interrupt
* 2-wire serial interface address match
* brown-out reset
* pin change interrupt

In order case we are interested to have I2C slaves that can go to sleep while still listening to their I2C address and wake-up when it match.

Like that we can have a board that consume nearly nothing, is waken up by a master, make some processing, returns the values to the master and go back to sleep.

This is what we would like to achieve with the weather station. We wake-up the  

### Code for weather-i2c

```
#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include <Wire.h>

void requestEvent() {}

void receiveEvent() {}

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

  ADCSRA &= ~(1 << ADEN); //Disable ADC: allows to win 80µA

  sleep_enable();

  // Now enter sleep mode.
  sleep_mode();

  // First thing to do is disable sleep.
  sleep_disable();
}

void setup() {
  pinMode(2, INPUT_PULLUP); // INT.0 should not flip when sleeping
  pinMode(3, INPUT_PULLUP); // INT.1 should not flip when sleeping
  startWireSlave();
  delay(5000);
}
void loop() {
  enterSleep();
  delay(5000);
}
```

### Code for master-simple

```
#include <Wire.h>

void setup() {
  pinMode(13, OUTPUT);
  Wire.begin();
}

void loop() {
  delay(15000);
  Wire.requestFrom(55, 0);
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);
}
```

We show here that we can wake-up the slave based on the address match.

* Consumption in sleep mode: 20µA
* Consumtpion awake: 3.8mA


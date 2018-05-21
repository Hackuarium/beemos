

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

We should therefore also prevent the other interrupts to happen like the brown-out, watchdog and pin change. You may check [this page](https://sites.google.com/site/qeewiki/books/avr-guide/external-interrupts-on-the-atmega328) for a nice explanation of interrupts. The PCINT (pin change interrupt) is managed by the register PCICR. By default (after reset) it is not enabled).

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

  // Now enter sleep mode.
  sleep_mode();

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

You can disable plenty of other things but we could not see any difference in power consumption:
```
  ACSR = (1 << ACD); //Disable the analog comparator
  DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins
  DIDR1 = (1 << AIN1D) | (1 << AIN0D); //Disable digital input buffer on AIN1/0

  power_twi_disable();
  power_spi_disable();
  power_usart0_disable(); //Needed for serial.print
  power_timer0_disable(); //Needed for delay and millis()
  power_timer1_disable();
  power_timer2_disable(); //Needed for asynchronous 32kHz operation
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

## Retrieving data from sleeping wire slave

A wire slave is able to listen to its address and wake up- But what about retrieving information from the sleeping slave ?

In those sketch we show that just after waking up it can actually already send back the information. This allows therefore to keep the slave awake a very short time like in this small example, 2ms.

### Code for master-simple

```
#include <Wire.h>

void setup() {
  pinMode(13, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  Wire.requestFrom(55, 1);
  byte value = Wire.read();
  Serial.println(value);
  
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}
```

### Code for weather-i2c

```
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
  delay(2);
}
```

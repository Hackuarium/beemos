#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

// Blink Before sleeping
#define LED_PIN (13)

// This variable is made volatile because it is changed inside
// an interrupt function
volatile int f_wdt = 1;

// Watchdog Interrupt Service. This is executed when watchdog timed out.
ISR(WDT_vect) {
  if (f_wdt == 0) {
    // here we can implement a counter the can set the f_wdt to true if
    // the watchdog cycle needs to run longer than the maximum of eight
    // seconds.
    f_wdt = 1;
  }
}

// Enters the arduino into sleep mode.
void enterSleep(void)
{
  // There are five different sleep modes in order of power saving:
  // SLEEP_MODE_IDLE - the lowest power saving mode
  // SLEEP_MODE_ADC
  // SLEEP_MODE_PWR_SAVE
  // SLEEP_MODE_STANDBY
  // SLEEP_MODE_PWR_DOWN - the highest power saving mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  power_all_disable();

  sleep_enable();

  // Now enter sleep mode.
  sleep_mode();

  // The program will continue from here after the WDT timeout

  // First thing to do is disable sleep.
  sleep_disable();

  // Re-enable the peripherals.
  power_all_enable();
}

// Setup the Watch Dog Timer (WDT)
void setupWatchDogTimer() {
  // The MCU Status Register (MCUSR) is used to tell the cause of the last
  // reset, such as brown-out reset, watchdog reset, etc.
  // NOTE: for security reasons, there is a timed sequence for clearing the
  // WDE and changing the time-out configuration. If you don't use this
  // sequence properly, you'll get unexpected results.

  // Clear the reset flag on the MCUSR, the WDRF bit (bit 3).
  MCUSR &= ~(1 << WDRF);

  // Configure the Watchdog timer Control Register (WDTCSR)
  // The WDTCSR is used for configuring the time-out, mode of operation, etc

  // In order to change WDE or the pre-scaler, we need to set WDCE (This will
  // allow updates for 4 clock cycles).

  // Set the WDCE bit (bit 4) and the WDE bit (bit 3) of the WDTCSR. The WDCE
  // bit must be set in order to change WDE or the watchdog pre-scalers.
  // Setting the WDCE bit will allow updates to the pre-scalers and WDE for 4
  // clock cycles then it will be reset by hardware.
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  /**
      Setting the watchdog pre-scaler value with VCC = 5.0V and 16mHZ
      WDP3 WDP2 WDP1 WDP0 | Number of WDT | Typical Time-out at Oscillator Cycles
      0    0    0    0    |   2K cycles   | 16 ms
      0    0    0    1    |   4K cycles   | 32 ms
      0    0    1    0    |   8K cycles   | 64 ms
      0    0    1    1    |  16K cycles   | 0.125 s
      0    1    0    0    |  32K cycles   | 0.25 s
      0    1    0    1    |  64K cycles   | 0.5 s
      0    1    1    1    |  256K cycles  | 2.0 s
      1    0    0    0    |  512K cycles  | 4.0 s
      1    0    0    1    | 1024K cycles  | 8.0 s
  */

  WDTCSR  = (1 << WDP3) | (0 << WDP2) | (0 << WDP1) | (1 << WDP0);
  // Enable the WD interrupt (note: no reset).
  WDTCSR |= _BV(WDIE);

  Serial.println(WDTCSR);
  delay(100);

}

// Setup for the serial comms and the other things
void setup() {
  delay(5000);
  Serial.begin(9600);
  Serial.println("Initialising...");
  delay(100);
  pinMode(LED_PIN, OUTPUT);
 // setupWatchDogTimer();
  Serial.println("Initialisation complete."); delay(1000);
}

// main loop
void loop() {
  // Wait until the watchdog have triggered a wake up.
  if (f_wdt != 1) {
    return;
  }


  delay(2000);



  // clear the flag so we can run above code again after the MCU wake up
  f_wdt = 0;

  // Re-enter sleep mode.
  enterSleep();

}

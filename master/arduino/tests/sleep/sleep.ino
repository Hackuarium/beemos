#include <avr/sleep.h>
#include <avr/wdt.h>

const byte LED = 13;

// watchdog interrupt
ISR (WDT_vect)
{
  wdt_disable();  // disable watchdog
}  // end of WDT_vect

void setup () {
  delay (8000);
  pinMode (LED, OUTPUT);
}

void loop () {  
  digitalWrite (LED, HIGH);
  delay (50);
  digitalWrite (LED, LOW);

  // disable ADC
  byte adconfig = ADCSRA;
  ADCSRA = 0;

  // clear various "reset" flags
  // MCUSR = 0;
  // allow changes, disable reset
  WDTCSR = 1 << WDCE | 1 << WDE;
  // set interrupt mode and an interval
  WDTCSR = 1 << WDIE | 1 << WDP3 | 1 << WDP0;    // set WDIE, and 8 second delay
  wdt_reset();  // pat the dog

  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  ADCSRA = adconfig;
} // end of loop

#include <avr/boot.h>;

void setup() {
  
}

void loop() {
  
    Serial.begin(9600);

    cli();
    uint8_t lowBits      = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
    uint8_t highBits     = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
    uint8_t extendedBits = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
    uint8_t lockBits     = boot_lock_fuse_bits_get(GET_LOCK_BITS);
    sei();

    Serial.print("Low:  0x");
    Serial.println(lowBits, HEX);
    Serial.print("High: 0x");
    Serial.println(highBits, HEX);
    Serial.print("Ext:  0x");
    Serial.println(extendedBits, HEX);
    Serial.print("Lock: 0x");
    Serial.println(lockBits, HEX);
    delay(1000);
}


# ATmega328 pin map

| Pin    | Map to        | Function | Remarks
| ------ | ------------- | -------- | -------
| D0     | PD0(RXD)      | RX       |
| D1     | PD1(TXD)      | TX       |
| D2     | PD2(INT0)     |          | Interrupt allows wake up
| D3     | PD3(INT1)     |          | Interrupt allows wake up
| D4     | PD4(XCK/T0)   |          |
| D5     | PD5(T1)       | LDR PWR  | Counter
| D6     | PD6(AIN0)     | DHT22    |
| D7     | PD7(AIN1)     | DHT22 PWR|
| D8     | PB0(ICP)      | SCL MAST |
| D9     | PB1(OC1A)     | SDA MAST | PWM
| D10    | PB2(SS/OC1B)  | TEMP PWR | PWM
| D11    | PB3(MOSI/OC2) | MOSI     |
| D12    | PB4(MISO)     | MISO     |
| D13    | PB5(SCK)      | SCK      |
| D14 A0 | PC0(ADC0)     | LDR      | ADC
| D15 A1 | PC1(ADC1)     | TEMP 1   | ADC
| D16 A2 | PC2/ADC2)     | TEMP 2   | ADC
| D17 A3 | PC3(ADC3)     | TEMP 3   | ADC
| D18 A4 | PC4(ADC4/SDA) | SDA SLAV |
| D19 A5 | PC5(ADC5/SCL) | SCL SLAV |
| D20 A6 | ADC6          | I2C A0   | ADC only input
| D21 A7 | ADC7          | I2C A1   | ADC only input

Remarks
* RX, TX used for serial communication over USB (debug)
* SDA, SCL: I2C communication with master
* MOSI, MISO, SCK: boot loader

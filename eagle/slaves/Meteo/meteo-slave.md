
# ATmega328 pin map

| Pin    | Map to        | Function | Remarks
| ------ | ------------- | -------- | -------
| D0     | PD0(RXD)      | RX       |
| D1     | PD1(TXD)      | TX       |
| D2     | PD2(INT0)     |          | Interrupt allows wake up
| D3     | PD3(INT1)     |          | Interrupt allows wake up
| D4     | PD4(XCK/T0)   |          |
| D5     | PD5(T1)       | DHT-22   | Counter
| D6     | PD6(AIN0)     | DS18B20  |
| D7     | PD7(AIN1)     |          |
| D8     | PB0(ICP)      |          |
| D9     | PB1(OC1A)     |          | PWM
| D10    | PB2(SS/OC1B)  |          | PWM
| D11    | PB3(MOSI/OC2) | MOSI     |
| D12    | PB4(MISO)     | MISO     |
| D13    | PB5(SCK)      | SCK      |
| D14 A0 | PC0(ADC0)     |          | ADC
| D15 A1 | PC1(ADC1)     | PHOTOCLL | ADC
| D16 A2 | PC2/ADC2)     |          | ADC
| D17 A3 | PC3(ADC3)     |          | ADC
| D18 A4 | PC4(ADC4/SDA) | SDA      |
| D19 A5 | PC5(ADC5/SCL) | SCL      |
| D20 A6 | ADC6          |          | ADC only input
| D21 A7 | ADC7          |          | ADC only input

Remarks
* RX, TX used for serial communication over USB (debug)
* SDA, SCL: I2C communication with master
* MOSI, MISO, SCK: boot loader

# LCD 16x2 slave
# ATmega328 pin map

| Pin    | Map to        | Function | Remarks
| ------ | ------------- | -------- | -------
| D0     | PD0(RXD)      | RX       |
| D1     | PD1(TXD)      | TX       |
| D2     | PD2(INT0)     | Rot A    | Interrupt allows wake up
| D3     | PD3(INT1)     | Rot Int  | Interrupt allows wake up
| D4     | PD4(XCK/T0)   | Rot B    |
| D5     | PD5(T1)       | LCD E    | Counter
| D6     | PD6(AIN0)     | LCD DB4  |
| D7     | PD7(AIN1)     | LCD DB5  |
| D8     | PB0(ICP)      | LCD DB6  |
| D9     | PB1(OC1A)     | LCD DB7  | PWM
| D10    | PB2(SS/OC1B)  | LCD A    | PWM
| D11    | PB3(MOSI/OC2) | MOSI     |
| D12    | PB4(MISO)     | MISO     |
| D13    | PB5(SCK)      | SCK      |
| D14 A0 | PC0(ADC0)     | LCD VDD  | ADC
| D15 A1 | PC1(ADC1)     |          | ADC
| D16 A2 | PC2/ADC2)     |          | ADC
| D17 A3 | PC3(ADC3)     |          | ADC
| D18 A4 | PC4(ADC4/SDA) | SDA      |
| D19 A5 | PC5(ADC5/SCL) | SCL      |
w

Remarks
* RX, TX used for serial communication over USB (debug)
* SDA, SCL: I2C communication with master
* MOSI, MISO, SCK: boot loader
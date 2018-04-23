# Smart Slaves

A smart slave is an I2C slave that can be connected to a master board.
The slave will be usually be powered by the master board as well and may
receive 12V as well as anything between 3.6 and 6V. The idea is that
the slave will not get a regulated current and it could come from a 
solar panel, a battery or a regulated power source.

Each slave will have a specific base I2C address that can be tuned
using the A0 and A1 jumper. By default it is the base address and you
may add repectively 1 or 2 by soldering A0 and A1.

The I2C bus should be free of any other devices. If some companents
are using the I2C bus a software I2C library should be installed.

## Power consumption

The slave should be able to reach in sleep mode less than 25 µA. This
means that all the devices should be powered from the CPU in order to
completely cut off the current.

## Debugging

A slave must have currently a crystal in order to work with external
clock at 8MHz. This is not the default behaviour of the ATMEGA328 that
works on the internal clock. However it seems that the internal clock 
is not precise enough (up to 5% error ?) and therefore USART communication
may be very difficult.

USART communication (RX and TX) is mainly used for development and this part
could be removed later.

This is also the reason for the presence of the FTDI port.

We could get rid of the FTDI and 8MHz crystal if we don't need Serial communication
and we don't need to debug the board anymore (i.e. for production).

## Logo

The logo of Hackuarium is present on the layer 200 and 201 in eagle. You may try
to move it by hidding all the other layers.

## CAM processing

Before submitting the PCB for manufacturing like for https://www.pcbway.com you need to 
generate the Gerber files.

The CAM processor for eagle starting 8.6 is present in this folder. They changed
completely the format but what is cool is that you can now directly export the ZIP file.
You may remove from the silk layer 200 or 201 if the logo of hackuarium really does not
fit.
Don't forget to test the generated gerber by uploading it on https://gerber-viewer.easyeda.com/



# ATmega328 pin map

| Pin    | Map to        | Function | Remarks
| ------ | ------------- | -------- | -------
| D0     | PD0(RXD)      | RX       |
| D1     | PD1(TXD)      | TX       |
| D2     | PD2(INT0)     |          | Interrupt allows wake up
| D3     | PD3(INT1)     |          | Interrupt allows wake up
| D4     | PD4(XCK/T0)   |          |
| D5     | PD5(T1)       |          | Counter
| D6     | PD6(AIN0)     |          |
| D7     | PD7(AIN1)     |          |
| D8     | PB0(ICP)      |          |
| D9     | PB1(OC1A)     |          | PWM
| D10    | PB2(SS/OC1B)  |          | PWM
| D11    | PB3(MOSI/OC2) | MOSI     |
| D12    | PB4(MISO)     | MISO     |
| D13    | PB5(SCK)      | SCK      |
| D14 A0 | PC0(ADC0)     |          | ADC
| D15 A1 | PC1(ADC1)     |          | ADC
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
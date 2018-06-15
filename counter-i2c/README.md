<p align="center">
<a href="https://hackuarium.github.io/beemos/">
<img border="0" alt="beemos" src="https://github.com/Hackuarium/beemos/raw/master/common/images/logoBeeMoS.svg" width="100">
</a>
</p>

# Bee-counter i2c
Using an Arduino based microcontroller, infrared (= IR) reflectance sensors are used to detect if a bee is present under the sensor, thereby modifying the reflected IR signal read by the microcontroller. Each gate consists of two IR reflectance sensors, each capable of emitting and receiving an IR signal. This allows to determine whether the bee is entering or exiting the hive by looking at which of the two sensors reacted first to the presence of the bee below it.

## Components
* x1 Microprocessor Atmel 32u4 (similar to Arduino Leonardo boards), 8Mhz, 3.3V
* x16 QRE1113 IR reflectance sensors (x2 per gate)
* x1 74HC154W demultiplexer used to switch on the IR led of one of the 16 IR reflectance sensors
* x1 74HC4067 multiplexer used to read the value from one of the IR reflectance sensors (the one which has the IR led on)

## Performances
Scanning all 16 IR sensors: 3ms
Current consumption: 27 mA

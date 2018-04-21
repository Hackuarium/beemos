# Open beehive (under development)
The BeeMoS project is an open source bee hive monitoring system developed at the open science lab Hackuarium, Renens, Switzerland. 

# Objective: 
Build and program an open source bee monitoring system consisting of the following components:

* Counter: count how many bees enter and exit from a hive during a given time. 
* Balance: Tracks changes in the hive's weight over time.
* Meteo station: Measures environmental variables including temperature, humidity, light and atmospheric pressure.
* Master board: Serves as an interface to communicate with other beemos components and sends the information.

# Principle:

## Counter: 
Using an Arduino based microcontroller, infrared (= IR) reflectance sensors are used to detect if a bee is present under the sensor, thereby modifying the reflected IR signal read by the microcontroller. Each gate consists of two IR reflectance sensors, each capable of emitting and receiving an IR signal. This allows to determine whether the bee is entering or exiting the hive by looking at which of the two sensors reacted first to the presence of the bee below it.

## Balance:

## Meteo station:

## Master board:
Communicates with all other devices over I2C and sends the data to a remote server using a SIM card module.

# Further details
* x1 Microprocessor Atmel 32u4 (similar to Arduino Leonardo boards), 8Mhz, 3.3V
* x16 QRE1113 IR reflectance sensors (x2 per gate)
* x1 74HC154W demultiplexer used to switch on the IR led of one of the 16 IR reflectance sensors
* x1 74HC4067 multiplexer used to read the value from one of the IR reflectance sensors (the one which has the IR led on)

# State of the project
We have ordered PCBs and now need to solder all elements, program the board and - if all goes well - test them in the field. We are working on parallel on a laser cut enclosure which includes 8 individual gates that the bees will use to enter/exit the hive and an upper compartment for the hive.

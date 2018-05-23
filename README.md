View this project on [CADLAB.io](https://cadlab.io/project/1029). 

# Open beehive (under development)
The BeeMoS project is an open source bee hive monitoring system developed at the open science lab Hackuarium, Renens, Switzerland. 

# Objectives: 
Build and program an open source bee monitoring system capable of the following objectives:

- [x] Track the activity of the hives to study the behaviour of bees and monitor their health. 
- [ ] Track changes in the hive's weight over time to detect sudden and gradual changes (honey production,  swarming, ...).
- [ ] Measures environmental variables including temperature, humidity, light and atmospheric pressure and study their effect on the bees.
- [ ] Send the data to a remote server for analysis, visualization or to notify the user if something unusual happens.

# Modules:
To achieve the above objective, the project follows a modular design with different hardware components.

**Counter**: Counts bees entering and exiting the hive over time using infrared sensors.

**Scale**: Weighs the hive periodically using 4 load cells..

**Meteo station**: Monitors temperature, humidity and luminosity outside the hives.

**Master boardi**: Communicates with all other devices over I2C and sends the data to a remote server using a SIM card module. Also tracks temperature inside the hive.


# State of the project
We have ordered PCBs, all elements of one board were soldered and a Arduino code was written to count entering/exiting bees and make logs for all gates using multithreading. We also built a first prototype for a laser cut enclosure which includes 8 individual gates that the bees will use to enter/exit the hive and an upper compartment for the board. We are getting close to test our first prototype in the field.

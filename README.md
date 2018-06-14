<p align="center">
  <img width="400" height="400" src="common/images/logoBeeMoS.png">
  
# BeeMoS - honey Bee Monitoring System 
# (under development)
</p>
The BeeMoS project is an open source bee hive monitoring system developed at the open science lab Hackuarium, Renens, Switzerland. 

# Objectives 
Build and program an open source bee monitoring system capable of the following objectives:

- [x] Track the activity of the hives to study the behaviour of bees and monitor their health. 
- [ ] Track changes in the hive's weight over time to detect sudden and gradual changes (swarming, honey production ...).
- [ ] Measures environmental variables including temperature, humidity, light and atmospheric pressure and study their effect on the bees.
- [ ] Send the data to a remote server for analysis, visualization or to notify the user if something unusual happens.

# Modules
To achieve the above objectives, the project follows a modular design with different hardware components.

**Counter**: Counts bees entering and exiting the hive over time using infrared sensors.

**Scale**: Weighs the hive periodically using 4 load cells.

**Weather station**: Monitors temperature, humidity and luminosity outside the hives.

**Master board**: Communicates with all other devices over I2C and sends the data to a remote server using a SIM card module. Also tracks temperature inside the hive.


# State of the project
We have designed and ordered the PCBs for the bee counter, weather station, scale and master boards. All elements of one board were soldered for the weather station and for the bee counter. We are waiting for the PCBs from the scale and master boards to arrive in the next few days. The Arduino code was written to count entering/exiting bees and make logs for all gates using multithreading. We also built a laser cut wooden enclosure which contains the bee counter PCB. It includes 8 individual gates that the bees use to enter/exit the hive and an upper compartment for the board so that sensor are on top of entering bees.  A few field trials were launched to assess the accuracy of the bee counter (more on that soon) but we still need to fix some things in the hardware and software to get it working.
The weather station board was also assembled and programmed. It can now show temperature, humidity, atmospheric pressure and relative light intensity. 
The next steps will be to get the bee counter to work and solder elements to the scale and master boards before programming them.

# Further resources 

All codes, PCB board and schematic files and documentation can be found on the [BeeMoS github repository](https://github.com/Hackuarium/beemos) (in english only)

View this project on [CADLAB.io](https://cadlab.io/project/1029)

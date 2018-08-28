Bee-counter i2c
<p align="right">
<a href="https://hackuarium.github.io/beemos/">
<img border="0" alt="beemos" src="https://github.com/Hackuarium/beemos/raw/master/common/images/logoBeeMoS.png" width="100">
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
Current consumption: 27mA


## The box
The box consists in a laser cut wooden enclosure, which contains the bee counter PCB. It includes 8 individual gates that the bees use to enter/exit the hive and an upper compartment for the board so that sensor are on top of entering bees. 


## Parameters
There are 26 parameters:
* 0 - the log ID
* 1 - the number of seconds since the last log
* 2-17 - parameters for the 16 IR reflectance sensors
* 18 - the luminosity
* 19 - the temperature (it is possible to connect a temperature sensor to the board)
* 20 - the threshold of absorbance to reach to conclude there is a bee crossing the gate
* 21 - the threshold of absorbance to conclude that the event is finished
* 22 - the duration of the gate monitoring
* 23 - the delay between two successive displays 
* 24 - the time interval between two logs
* 25 - a boolean to enable the debug mode


## Menu and commands
Here is the actual menu, accessible by typing "h" + enter.

* (h)elp
* (s)ettings
* (u)tilities
* (b)ackground 
* (c)ounter
* (g)ate debug bg  
* (l)og

"Settings" gives acces to the current values of the settings. To change the value of a setting, just type the letter of the setting (A-Z) and the new value of the setting in the chat box and press enter.
"Gate debug mode" activates the real-time monitoring system. Each time a bee pass through a tunnel, the time, the number of the gate, the absorbance values of the two sensors and the number of bees outside is displayed. 


## Experiments
In order to assume the precision of the bee counter, we set an experiment as follows:
We built inside a transparent tupperware two hermetic compartiments, one with sugared water, the other one with pollen. The bees can only pass from one compartment to another through the box containing the tunnels with the IR reflectance sensors. With a camera, we filmed the tupperware to then compare the results of the gate monitoring debug system with the footage of the camera.

![Alt text](/docs/BeeCounter/Images/tupperwareDesign.jpg?raw=true "Tupperware Design")

![Alt text](/docs/BeeCounter/Images/tupperwareExperimentSetup.jpg?raw=true "Tupperware Experiment Setup")

## Results
The monitoring system seems to be functionnal. Every bee passing through is counted and in the right sense (IN or OUT).
There is still some problems yet to be fixed:
* The bees have the tendancy to poke their head through the tunnel without crossing it, thus triggering the sensors even when they don't cross the box. One possible solution to be tested is to extend a little the lenght of the tunnel.
* As the sensors are placed on one side of the box, they are easily triggered by quick changes in brightness (for example a hand moving over the tupperware). This problem should be solved when the box will be placed inside a hive, because the side with the sensors will be facing the inside of the hive, thus preventing such rapid changes.



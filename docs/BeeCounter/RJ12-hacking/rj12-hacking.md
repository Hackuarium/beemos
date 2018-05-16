# Connector for luminosity, temperature and power supply


The default connector as the following pin out

* +12V (not connected)
* SCL (PWM)
* SDA (I/O)
* A6 (GND)
* +5V
* GND

There is the possiblity to have an internal pullup so that if we connect a LDR between the ground and A6 it should be possible to measure the light intensity.

We can also connect a one-wire temperature probe DS18B20 connected to SCL. We will also have to connect a 4.7kΩ between +5V and SCL.

Finally we can connect the power supply between the +5V and the GND. The power supply may be anything between 3.7 and 6V.

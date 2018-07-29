<p align="right">
<a href="https://hackuarium.github.io/beemos/">
<img border="0" alt="beemos" src="https://github.com/Hackuarium/beemos/raw/master/common/images/logoBeeMoS.png" width="100">
</a>
</p>

# Meteo station I2C

The goal of this project is to create a small board that contains many sensors and that can be used as a meteo station. This board is controlled by the master board and acts as an I2C slave. The board is in sleep mode by default and is only waked up by the master board when it requires data.

## Hardware components


The following components are present on the board:

Microcontroller: ATmega328

Sensors:
* DHT-22 humidity sensor
* DS18B20 for temperature
* Photoresistor for light

Connectors:
* 2X RJ12 to connect other boards via I2C
* 2X 3.5mm jack to eventually connect additional sensors.

## I2C commands

This device appears like a I2C slave at the address XXX and allows the following commands

## Performances
* Consumption in sleep mode: 20µA
* Consumtpion awake: 3.8mA

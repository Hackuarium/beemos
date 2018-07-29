<p align="right">
<a href="https://hackuarium.github.io/beemos/">
<img border="0" alt="beemos" src="https://github.com/Hackuarium/beemos/raw/master/common/images/logoBeeMoS.png" width="100">
</a>
</p>

# Scale

The purpose of this board is to measure the weight of the hive periodically. This allows to detect honey production and swarming.

## Hardware components

The following components are present on the board:

Microcontroller: ATmega328

Sensors:

- HX711 Amplifier
- 4X load sensors SEN-10245 (confirm REF)

Connectors:

- 2X RJ12 to connect other boards via I2C

## I2C commands

This device appears like a I2C slave at the address XXX and allows the following commands

## Performances

- Consumption in sleep mode:
- Consumtpion awake:

## Making

Version 1.0.0 has 2 small bugs. A small cable has to be soldered as show in the following picture and the resistor in the red circle should be 220k instead of 1m.

<img src="docs/board100.jpg" />

If you want to solder a loading cell you may use the following color cabling

<img src="docs/loadcell.jpg" />

Final global view:

<img src="docs/full.jpg" />

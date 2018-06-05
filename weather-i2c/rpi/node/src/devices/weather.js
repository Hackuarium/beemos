'use strict';

module.exports = {
    name: 'Weather i2c device',
    type: 'Weather',
    description: '',
    url: '',
    numberParameters: 26,
    numberLogParameters: 10,
    parameters: [
        {
            label: 'A',
            name: 'Log ID',
            description: 'Sequential ID',
            factor: 1,
            unit: '',
            writable: false
        },
        {
            label: 'B',
            name: 'Seconds',
            description: 'Number of seconds since the last log',
            factor: 1,
            unit: 's',
            writable: false
        },
        {
            label: 'C',
            name: 'T° probe 1',
            description: 'Temperature from external probe 1',
            factor: 100,
            unit: '°C',
            writable: false
        },
        {
            label: 'D',
            name: 'T° probe "',
            description: 'Temperature from external probe 2',
            factor: 100,
            unit: '°C',
            writable: false
        },
        {
            label: 'E',
            name: 'T° PCB probe',
            description: 'Temperature from PCB probe',
            factor: 100,
            unit: '°C',
            writable: false
        },
        {
            label: 'F',
            name: 'Humidifty',
            description: 'Humidity',
            factor: 100,
            unit: '%',
            writable: false
        },
        {
            label: 'G',
            name: 'T° PCB probe',
            description: 'Temperature from humidity sensor',
            factor: 100,
            unit: '°C',
            writable: false
        },
        {
            label: 'H',
            name: 'Luminosity',
            description: 'Luminosity',
            factor: 1,
            unit: '',
            writable: false
        },
        {
            label: 'I',
            name: 'Pressure',
            description: 'Atmospheric pressure',
            factor: 100,
            unit: 'hPa',
            writable: false
        },
    ],
    events: []
};


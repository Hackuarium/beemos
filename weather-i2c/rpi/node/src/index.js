
const I2C = require('i2c-bus');
const delay = require('delay'); // for delays (async)

const Device = require('./Device');

var i2c;

loopForEver();

async function loopForEver() {
    // connecting on I2C bus 1
    try {
        i2c = I2C.openSync(1); // Synchronous open (not a promise). Returns a new Bus object.
    } catch (e) {
        debug('i2c bus error', e.toString());
    }

    // initializing
    // eslint-disable-next-line
    await start().catch((e) => console.log(e));
}


function scan() {
    let devices = i2c.scanSync();
    console.log(devices);
}

async function start() {

    let device = new Device(i2c, 55);

    device.wakeup();

    console.log(device.readInt(5));
    
    device.writeInt(20, -12345);
    console.log(device.readInt(20));
}


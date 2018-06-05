'use strict';

const delay = require('delay');

function Device(bus, address) {
    this.bus=bus;
    this.address=address;
}

Device.prototype.readInt = function readInt (register) {
    let buffer=new Buffer(2);
    this.bus.sendByteSync(this.address, register);
    this.bus.i2cReadSync(this.address, 2, buffer);
    return buffer.readIntBE(0, 2);
}

Device.prototype.writeInt = function writeInt(register, value) {
    let buffer=new Buffer(3);
    buffer.writeInt8(register);
    buffer.writeInt16BE(value, 1);
    this.bus.i2cWriteSync(this.address, 3, buffer);
}

Device.prototype.wakeup = async function wakeup() {
    try {
        this.bus.sendByteSync(this.address, 0);
    } catch(e) {
        console.log('Try to wake up');
        await delay(1);
    }
}

module.exports=Device;
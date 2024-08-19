#!/usr/bin/env node

var raw = require('./raw');
var device = raw.get_device();

var alive = false;

function read_data(data) {
    alive = true;
    // Data is a buffer
    var percent = data.readInt8(1);
    var voltage = data.readInt8(2);
    voltage = (voltage << 8) | data.readInt8(3);

    console.log("Percent:", percent, "Voltage:", voltage);
    device.close();
}

function print_error(err) {
    console.log("Error:", err);
}

if(process.argv[2]) {
    var type = process.argv[2];
    console.log("Driver Type:", type);
    HID.setDriverType(type);
}


var res = raw.send_data(device, [0xC0]);

device.on("data", read_data);
device.on("error", print_error)
// Set a timeout to close the device if no response is received
setTimeout(function() {
    if(!alive) {
        console.error("Took too long to get response!");
        device.close();
    }
}, 2000);

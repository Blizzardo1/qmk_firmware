#!/usr/bin/env node

const debug = false;
var HID = require('node-hid');

exports.send_data = function (device, data) {
    data.splice(0, 0, 0x00);
    for(var i = data.length; i < 32; i++) {
        data.push(0x00);
    }
    device.write(data);
    console.log("Sent", data.length, "bytes");
}

exports.get_device = function() {
    for(var hid of HID.devices()) {
        if(hid.path.match(/VID_3434/) && hid.usage == 0x61) {
            if(debug) {
                console.log("Device:", hid);
            }
            return  new HID.HID(hid.path);
        }
    }
}

exports.get_device_async = async function() {
    for(var hid of await HID.devicesAsync()) {
        if(hid.path.match(/VID_3434/) && hid.usage == 0x61) {
            if(debug) {
                console.log("Device:", hid);
            }
            return HID.HIDAsync.open(hid.path);
        }
    }
}

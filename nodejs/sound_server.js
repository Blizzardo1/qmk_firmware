#!/usr/bin/env node

var raw = require('./raw');

var device = null;

function listen() {
    console.log("Listening for data");
    device.on("data", function (data) {
        console.log("Received", data.length, "bytes");
        console.log(data);
        // Startup Sound
        if (data[0] == 0xA0) {
            // Play an audio file
            // "E:\Users\Adonis\Music\Youtube Stuff\98 Media\WO_START.WAV"
            var exec = require('child_process').exec;
            var cmd = 'start "" "E:\\Users\\Adonis\\Music\\Youtube Stuff\\98 Media\\WO_START.WAV"';
            exec(cmd, function (error, stdout, stderr) {
                console.error("Error:", error);
                console.error("Stdout:", stdout);
                console.error("Stderr:", stderr);
            });
            device.close();
        }
    });

    device.on("error", function (err) {
        console.error("Error:", err);
    });
}

setTimeout(function () {
    console.log("Looking for device");
    while (device == null) {
        device = raw.get_device();
    }
    console.log("Device found");
    listen();
}, 5000);

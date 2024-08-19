#!/usr/bin/env node

var raw = require('./raw');
const readline = require('readline');

var device = null;
var alive = true;

async function listen() {
    console.log("Listening for data");
    device.on("data", function (data) {
        console.log("Received", data.length, "bytes");
        var array = Uint8Array.from(data);
        var command = array[0];

        // KENOBI_CMD_GET_LOCK_STATUS
        if (command == 0xC2) {
            // Grab the lock status
            response = array[1];
            switch (response) {
                case 0x00:
                    response = "Locked";
                    break;
                case 0x01:
                    response = "Pending";
                    break;
                case 0x02:
                    response = "Unlocked";
                    break;
                default:
                    response = "Unknown";
                    break;
            }
            console.log("Lock Status: " + response);
        }
    });

    device.on("error", function (err) {
        console.error("Error:", err);
    });
    // wait here until we decide to kill the server
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    rl.question('Press any key to stop the server...', (answer) => {
        alive = false;
        rl.close();
    });

    while (alive == true) {
        await new Promise(resolve => setTimeout(resolve, 1000)).then(() => {
            // console.log("Waiting...");
        });
    }
    device.close();
    console.log("Device closed");
}



setTimeout(async function () {
    console.log("Looking for device");
    while (device == null) {
        device = await raw.get_device_async();
    }
    console.log("Device found");
    await listen();
}, 5000);

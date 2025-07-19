# esp32-WEMOS-SX1262-LoRa-Receiver

This project contains a LoRa SX1262 based receiver built for the WEMOS ESP32 18650 micro USB development board. It is intended to work with the `ha-relay-controller` project which provides a LoRa controller and receiver for the Heltec LoRa V3.2 board. The radio protocol is identical so this firmware can be paired with the controller from that project while using different hardware.

The receiver listens for LoRa commands, drives a relay on GPIO32 and periodically reports status information including battery level. Basic configuration values such as transmit power and status update frequency are stored using the ESP32 `Preferences` API so they persist across reboots.

The code is written for the Arduino framework and built with [PlatformIO](https://platformio.org/). It depends on the [RadioLib](https://github.com/jgromes/RadioLib) library. To build and upload use:

```bash
pio run -t upload
```

Adjust the upload options as needed for your environment.

# monkey-mesh
Experiments around Mesh Networks (mainly Meshtastic)

This repository's main goal is to serve as sketchbook on several experimentation around Meshtastic and its integration and stre tching to different scenarios (i.e. Automation, Monitoring, Storytelling)

It all stems from [a thought](https://www.reddit.com/r/meshtastic/comments/1d07e7j/meshtastic_thermal_printer_ticker_tape_node/) I had a year ago: how to save and somehow record these ephemeral-ethereal messages in our absence?

Attach a printer to a meshtastic radio and see the messages coming one after another, a real physical representation of the conversations.

This project was an excuse to see how far a meshtastic radio could be integrated into a more distributed and complex system. 

A number of things can be built from here, including-in addition to the printer from which we start-a small bot capable of operating some field operations, or even a very simple BBS (Bulletin board system) based on microntrollers. 

Here are some examples I've found useful in this path. 

### What we need: 
- a meshtastic radio (I am using a XIAO ESP32S3 & Wio-SX1262 Kit for Meshtastic & LoRa
- a second radio from which to send data (equated technically with a cell phone)
- a microcontroller (in early experiments I used a Xiao SAMD21, and then used another ESP32S3)
- a voltage converter
- a switch
- two [Xiao Grove Shields](https://wiki.seeedstudio.com/Grove-Shield-for-Seeeduino-XIAO-embedded-battery-management-chip/) (for purely educational purposes-I'm getting old. 

### Software side, we use:
- meshtastic web flasher
- meshtastic console
- Arduino IDE
- Meshtastic's Protobuf library for Arduino



## 1) Xiao ESP32SE Serial ports


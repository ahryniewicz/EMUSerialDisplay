# EMUSerialDisplay
ECUSerialDisplay Arduino project allows for creating a car dashboard display, that could present Ecumaster EMU data provided over serial protocol on 1.28" round display (GC9A01 driver).
It is based on https://github.com/GTO2013/EMUSerial library to get EMU data and TFT_eSPI library to present it on GC9A01 1.28" display.
Custom design dashboard allows for presenting MAP and AFR data plus 3 different paramaters as a "display set". Number of display sets is configurable, the same as 3 of parameters on a set.
Additionaly project handles DFRobot EC11 rotary encoder, that allows of controlling brightnes and switching between display sets.

Currently project supports/consists of hardware listed below:
- ESP32 DevkitV1
- Display:
  - Waveshare 19192
- DFRobot EC11
- GX16 5-PIN connector

After assembling it looks like this:
![device](https://github.com/ahryniewicz/EMUSerialDisplay/assets/27493069/55a9f474-5a23-4e2d-8578-241cbd152e2f)

# Example realisation for MX5 NBFL
![mx5_nbfl](https://github.com/ahryniewicz/EMUSerialDisplay/assets/27493069/198ce48b-f850-4c7f-9770-4d03bdd32399)

# Would you like to support me
If you find my project useful, consider support me on:

https://buycoffee.to/adamhryniewicz

https://www.buymeacoffee.com/adamhryniewicz

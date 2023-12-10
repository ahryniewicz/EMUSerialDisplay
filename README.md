# EMUSerialDisplay
ECUSerialDisplay Arduino project allows for creating a car dashboard display, that could present Ecumaster EMU data provided over serial protocol on 1.28" round display (GC9A01 driver).
It is based on https://github.com/GTO2013/EMUSerial library to get EMU data and TFT_eSPI library to present it on GC9A01 1.28" display.
Custom design dashboard allows for presenting MAP and AFR data plus 3 different paramaters as a "display set". Number of display sets is configurable, the same as 3 of parameters on a set.
Additionaly project handles DFRobot EC11 rotary encoder, that allows of controlling brightnes and switching between display sets.

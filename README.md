# RotorEmulator
A very simple ESP32 based emulator for Yeasu G-800/1000/2800 rotators.\
Emulates the 6-pin Mini-DIN external control plug at the back of the rotator controller.\
This is helpful for testing devices that make use of the external control plug to control the rotator.

## Caveat
With a standard ESP32, speed control input voltage must not exceed 3.3 V.
Similarly, position output voltage is limited to a maximum of 3.3 V.
Additional electronics are needed to correctly mimic the real rotators input and output voltages.

## Build
Build with PlatformIO.

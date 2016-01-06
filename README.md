# attiny_rc_switch
On/Off Switch for RC models driven by PWM signal. Based on ATtiny85, 12V capable.

This small device allows to turn on/off different devices on RC devices: airplanes, quadcopter drones, cars. 
It uses one RC PWM channel as input and provides power (up to 1.5A with proper radiator) when channel pulse length is above 1700us.
Excellent to switch LED strips. 

# Hardware

* AVR ATtiny x5 series microcontroller. Compiled code takes slightly above 2kB, so will fit into ATtiny45 and ATtiny85. When smoothing is removed, code will fit into ATtiny25
* 4.7kOhm resistor
* BD139 or similar NPN bipolar transistor

![diagram](attiny_rc_switch.png)

# Requirements

* Arduino IDE 1.6.6. Should work on older releases, but never tested
* ATtiny45/85 board definitions. Tested with [damellis/attiny](https://github.com/damellis/attiny)
* Uses 8MHz internal osciallator 
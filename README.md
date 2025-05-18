# ATtiny RC Switch

![3D PCB](res/attiny_rc_switch.png)

Order the PCB [here](https://oshpark.com/shared_projects/kK0Np74q)

On/Off Switch for RC models driven by PWM signal. Based on ATtiny85, 12V capable. Original project is located [here](https://github.com/DzikuVx/attiny_rc_switch).

This small device allows to turn on/off different devices on RC devices: airplanes, quadcopter drones, cars. 
It uses one RC PWM channel as input and provides power on output pins when channel pulse length is above 1700us.
Excellent to switch LED strips. Output current is up to 500mA.

## Hardware

![PCB Top](res/attiny_rc_switch_pcb_top.png)
![PCB Bottom](res/attiny_rc_switch_pcb_bottom.png)

* AVR ATtiny x5 series microcontroller. Compiled code takes slightly above 2kB, so will fit into ATtiny45 and ATtiny85. When smoothing is removed, code will fit into ATtiny25

### BOM

| Label |Part No    | Name     | Quantity | Subtotal | Link   |
|-------|-----------|----------|----------|----------|--------|
| U1 | ATTINY85-20SU | ATtiny85 Microcontroller | 1 | $1.50 | [DigiKey](https://www.digikey.com/en/products/detail/microchip-technology/ATTINY85-20SU/735470) |
| U2 | IRLML2502TRPBF | N-Channel MOSFET, 20V, 4.2A SOT-23 | 1 | $0.43 | [DigiKey](https://www.digikey.com/en/products/detail/infineon-technologies/IRLML2502TRPBF/812502) |
| D1 | LTST-C190KRKT | Red LED, SMD 0603, Clear | 1 | $0.14 | [DigiKey](https://www.digikey.com/en/products/detail/liteon/LTST-C190KRKT/386817) |
| R1,R2 | CRGCQ0603F470R | 470 Ohm Resistor, SMD 0603, 1/10W | 2 | $0.20 | [DigiKey](https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGCQ0603F470R/8576286) |
| C1 | CC0603KRX7R7BB104 | 0.1uF Capacitor, SMD 0603, 16V | 1 | $0.08 | [DigiKey](https://www.digikey.com/en/products/detail/yageo/CC0603KRX7R7BB104/302822) |
|  |  |  | Total | $2.35 |  |

### Schematic

![diagram](res/attiny_rc_switch_schematic.png)

## Notes

* Arduino IDE 1.6.6. Should work on older releases, but never tested

* ATtiny45/85 board definitions. Tested with [damellis/attiny](https://github.com/damellis/attiny)

* Uses 8MHz internal osciallator 

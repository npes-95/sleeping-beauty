# Real Time Embedded Systems Project: Sleep Monitoring Alarm System

Code, schematics and supporting documentation for a smart alarm system that will monitor the user's sleep cycle in order to wake them at the optimal time. This system is implemented using a Raspberry Pi, bed mounted sensors and a smartphone GUI.

## Motivation for the project

Sleeping is an essential part of everybody’s life. However, how often do you wake up feeling tired and wishing to press the snooze button and go back to sleep? Making the waking up process more pleasant became possible with the discoveries in human physiology and technology.

Even though we perceive sleep as a singular state of a human activity, on a physiological level there are four distinctive stages of sleep (in a single sleep cycle):
- **Stage 1**: drowsiness and very light sleep *(@10 min)*;
- **Stage 2**: light sleep: slowing heart rate, blood pressure, and decreased body temperature, falling into a deeper sleep *(@20 min)*;
- **Stage 3**: deep sleep, the heart rate, breathing, and blood pressure drop even further, the body becomes immobile *(@40 min)*;
- **Stage 4**: rapid eye movement (also known as REM), the stage when we dream.

At the end of stage 4 and stage 1 it is the easiest for one to wake up. However, if you are in stage 3 or 4 when your alarm rings, your waking up experience is likely to be extremely unpleasant. 

Between the sleep cycles (when it is the easiest to wake up) a person usually changes their position (which, surprisingly, happens when the person is awake, though chances are high he/she would not remember that later), and then they immediately fall back asleep.

*This concept, obviously, is not new. There are similar devices on the market, tracking the movement of the person / heart rate / breathing in order to detect the sleep stage for the most pleasant wake up experience. However, such alarms on the market exist in a form of phone apps, which require a substantial subscription fee (£4/month or £25/year, depending on the app).*

**The aim of this project is to design a smart alarm system by using various sensors (microphone, accelerometer, pressure sensor).**

## Overall System Diagram

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/media/smart_alarm_schematics.png)

## Components

- Raspberry Pi 3 Model B (1x)
[[Specifications](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)]
[[Pin Out](https://pinout.xyz/)]

- LM2937 v3.3 Voltage Regulator (x1)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/Regulator.pdf)]

- MCP3008 10-Bit A/D Converter (x1)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/MCP3008.pdf)]

- USB-A Female Connector (x4)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/USB-A.pdf)]

- I2S Output Digital Microphone (x1)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/Microphone.PDF)]

- Adafruit LIS3DH Triple-Axis Accelerometer (x1)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/Accelerometer.pdf)]

- Dual Operational Amplifier LF353 (x2)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/LF353.pdf)]

- FSR 400 Pressure Sensor (x4)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/Pressure.pdf)]

- 2 Pin Terminal Block (x6)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/Terminal.pdf)]

- 4 Pin Terminal Block (x1)
[[Datasheet](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/Datasheets/Terminal.pdf)]

- 100kΩ Resistor (x5)

- 54Ω Resistor (x2)

- 0.1μF Farad Capacitor (x2)

- 10μF Farad Capactitor (x1)

- 200pF Farad Capactitor (x1)



## Main Board

The main board consists of:

- 40 Pin Female Connector used to connect Raspberry Pi (Pi Connector)
- Voltage Regulator (LM2937/TO220)
- ADC (MCP3008-I/P)
- Microphone (SPH0645LM4H-B)
- 2 Pin Terminal Block used as Power Supply Rail for the Pressure Board (5V Power)
- USB-A Female Connector used as SPI Rail for communication with the Pressure Sensors (SPI Rail)
- USB-A Female Connector used as I2C Rail for communication with the Accelerometer (I2C Rail)

The picture below illustrates the schematic of the main board:

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/schematic/Main%20Schematic.PNG)

The extra components (resistors, capacitors) are added using instructions from the datasheets. Also, it is important to note the Raspberry Pi is stacked on the top of the PCB upside down (pins are pointing down). Therefore, pin 2 of Raspberry Pi is indicated as pin 1 on the schematic. The PCB design of the main board is indicated below:

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/pcb/Main%20PCB.PNG)

## Pressure Board

The pressure board consists of:

- 2 Pin Terminal Block used as Power Supply Rail (5V Power)
- 2 Pin Terminal Blocks used to connect Pressure Sensors (x4)(PS1, PS2, PS3, PS4)
- USB-A Female Connector used as SPI Rail for communication with Raspberry Pi (SPI Rail)
- Dual Operational Amplifier used as Buffer to increase signal strength (x2)(U1A + U1B, U2A + U2B)

The picture below illustrates the schematic of the pressure board:

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/schematic/Pressure%20Schematic.PNG)

The PCB design of the pressure board is indicated below:

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/pcb/Pressure%20PCB.PNG)

## Accelerometer Board

The accelerometer board consists of:

- 4 Pin Terminal Block used to Adafruit accelerometer (Accelerometer)
- USB-A Female Connector used as I2C Rail for communication with Raspberry Pi (I2C Rail)

The picture below illustrates the schematic of the accelerometer board:

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/schematic/Accelerometer%20Schematic.PNG)

The PCB design of the accelerometer board is indicated below:

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/hardware/pcb/Accelerometer.PNG)

## Project specifications:

- [ ] **Responsiveness of the application**

- [x] **Latency permitted between physical event and output** <br />
1 second (not scientifically justified, but an educated guess).

- [ ] **Sampling rate** <br />
The sampling rate of the components used is the following:
- ADC: 50 – 200 kHz
- Microphone: 32 – 64 kHz
- Accelerometer: 1 Hz – 5 kHz <br />
Due to the specifications of the project, the lowest sampling rate limit was chosen for the ADC and the microphone, while the suitable sampling rate for the accelerometer will have to be decided upon once tested.

- [x] **Bus protocol** <br />
A number of sensors is used for this project. The following bus protocols are used for the following sensors:
- Microphone: I2S
- Accelerometer: I2C -> [Check out our I2C demo!](https://youtu.be/kbwUbBWLsfQ)
- Pressure sensors: SPI -> [Check out our SPI demo!](https://youtu.be/tLUy4hVlnH0)<br />
Reason: avoids having to use chip select.

- [x] **Number of channels** <br />
Six: four pressure sensors, one accelerometer, one microphone.

- [x] **Kernel or userspace** <br />
Userspace: soft real time system, sampling rate requirements low enough.

- [ ] **Data flow from hardware to GUI**

- [ ] **Buffering of data**

- [ ] **Latency introduced by buffering**

- [ ] **Postprocessing of data**

- [ ] **Threads**

- [ ] **GUI implementation** <br />
The GUI of choice at the moment is a phone app, but this option is still to be considered, and if it does not work, then create a webpage.

- [ ] **Structure of the software in classes**

- [x] **Team structure** <br />
From the beginning everyone seemed to be equally involved in the project, willing to contribute as much as they can. If the eagerness persists and the project progresses effectively, no need to give out specific roles to the team members. If it turns out in the future that this is not working effectively, the roles and the contributions would have to be reconsidered.

- [x] **Time allocation** <br />
The time for hardware design coincided with final year project deadlines (for the presentation specifically). Hence, it took 3 weeks to sort out the hardware. 4 more weeks are allocated to software development, and then 2 weeks for debugging.

- [ ] **Version control software**

- [x] **Release strategy / publication / publicity** <br />
Our team is actively involved in various social media:
- [Instagram](https://www.instagram.com/sleeping.beauty.uofg/)
- [Twitter](https://twitter.com/SleepBeauty2018)
- [Youtube](https://www.youtube.com/channel/UCnenRGqD6ltJDOzgHJ9lT9g)

- [ ] **Success of the application**

### Team members
- **Erika Bondareva**
- **Nicholas Smith**
- **Lukas Zitinskas**

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

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/media/diagram_renewed.png)

## Project specifications:

- [ ] **Responsiveness of the application** <br />

- [x] **Latency permitted between physical event and output** <br />
10 seconds (not scientifically justified, but an educated guess).

- [] **Sampling rate** <br />
The sampling rate of the components used is the following:
- ADC: 50 – 200 kHz
- Accelerometer: 1 Hz – 5 kHz <br />
Due to the specifications of the project, the lowest sampling rate limit was chosen for the ADC and the microphone, while the suitable sampling rate for the accelerometer will have to be decided upon once tested.

- [x] **Bus protocol** <br />
A number of sensors is used for this project. The following bus protocols are used for the following sensors:
- Accelerometer: I2C -> [Check out our I2C demo!](https://youtu.be/kbwUbBWLsfQ)
- Pressure sensors: SPI -> [Check out our SPI demo!](https://youtu.be/tLUy4hVlnH0)<br />
Reason: avoids having to use chip select.

- [x] **Number of channels** <br />
**Five:** four pressure sensors, one accelerometer.

- [x] **Kernel or userspace** <br />
**Userspace:** soft real time system, sampling rate requirements low enough.

- [x] **Data flow from hardware to GUI** <br />
In this project the data flow is rather from GUI to hardware, and is presented in the flowchart below.

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/media/RTEP_flowchart_App_Server_RPi.png)

Raspberry Pi asks the server every 1 minute what is the alarm status (whether the alarm is set and alarm time), and upon the time reaching half an hour before the alarm time set by the user, Raspberry Pi tracks the motion of the person. As soon as the person moves, the alarm is triggered.

- [ ] **Buffering of data** <br />
For effective processing of data, the data is sampled for 5 seconds, after which it is analysed using a peak detection algorithm (further discussed under *Postprocessing of data*.

- [x] **Latency introduced by buffering** <br />
**5 seconds,** since the data is sampled for 5 seconds.

- [ ] **Postprocessing of data** <br />
Peak detection algorithm

- [ ] **Threads** <br />


- [x] **GUI implementation** <br />
The GUI of choice is a phone app (iOS). The app was created  in Swift, using XCode. It is not availbale on the App Store, but the code for the current version is available [here](https://github.com/npes-95/sleeping-beauty/tree/master/app), and you can see what it looks like in our [demo video](). 

The original plan was to make the app and the RPi communicate via Bluetooth. Due to the implementation complexity, the alternative solution was to make the app talk to the server, and RPi requests the alarm details from the server (no direct communication between the phone app and the RPi.

- [ ] **Structure of the software in classes** <br />

- [x] **Team structure** <br />
From the beginning everyone seemed to be equally involved in the project, willing to contribute as much as they can. The following team roles were  assigned:
- Erika Bondareva: phone app + server.
- Nicholas Smith: RPi code + testing.
- Lukas Zitinskas: hardware.

- [x] **Time allocation** <br />
The time for hardware design coincided with final year project deadlines (for the presentation specifically). Hence, it took 3 weeks to sort out the hardware. 4 more weeks are allocated to software development, and then 2 weeks for debugging. The time alloction has worked out successfully.

- [x] **Version control software** <br />
GitHub was used as the version control software, used via command line.

- [x] **Release strategy / publication / publicity** <br />
Our team has its own Twitter and Yotube pages:
- [Twitter](https://twitter.com/SleepBeauty2018)
- [Youtube](https://www.youtube.com/channel/UCnenRGqD6ltJDOzgHJ9lT9g)

- [x] **Success of the application** <br />
**IT WORKED!**
Watch out video demo [here]()

### Team members
- **Erika Bondareva**
- **Nicholas Smith**
- **Lukas Zitinskas**

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

## Project schematics

![alt text](https://imgur.com/NQQ8QSq.png)

## Project specifications:

- [ ] **Resopnsiveness of the application**

- [x] **Latency permitted between physical event and output**
1 second (not scientifically justified, but an educated guess).

- [ ] **Sampling rate**
The sampling rate of the components used is the following:
- ADC: 50 – 200 kHz
- Microphone: 32 – 64 kHz
- Accelerometer: 1 Hz – 5 kHz
Due to the specifications of the project, the lowest sampling rate limit was chosen for the ADC and the microphone, while the suitable sampling rate for the accelerometer will have to be decided upon once tested.

- [x] **Bus protocol**
A number of sensors is used for this project. The following bus protocols are used for the following sensors:
- Microphone: I2S
- Accelerometer: I2C
- Pressure sensors: SPI
Reason: avoids having to use chip select.

- [x] **Number of channels**
Six: four pressure sensors, one accelerometer, one microphone.

- [x] **Kernel or userspace**
Userspace: soft real time system, sampling rate requirements low enough.

- [ ] **Data flow from hardware to GUI**

- [ ] **Buffering of data**

- [ ] **Latency introduced by buffering**

- [ ] **Postprocessing of data**

- [ ] **Threads**

- [ ] **GUI implementation**
The GUI of choice at the moment is a phone app, but this option is still to be considered, and if it does not work, then create a webpage.

- [ ] **Structure of the software in classes**

- [x] **Team structure**
From the beginning everyone seemed to be equally involved in the project, willing to contribute as much as they can. If the eagerness persists and the project progresses effectively, no need to give out specific roles to the team members. If it turns out in the future that this is not working effectively, the roles and the contributions would have to be reconsidered.

- [x] **Time allocation**
The time for hardware design coincided with final year project deadlines (for the presentation specifically). Hence, it took 3 weeks to sort out the hardware. 4 more weeks are allocated to software development, and then 2 weeks for debugging.

- [ ] **Version control software**

- [ ] **Release strategy / publication / publicity**

- [ ] **Success of the application**

### Team members
- **Erika Bondareva**
- **Nicholas Smith**
- **Lukas Zitinskas**

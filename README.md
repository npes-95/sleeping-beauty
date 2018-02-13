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

Erika Bondareva, Nicholas Smith, Lukas Zitinskas.

# Real Time Embedded Systems Project: Sleep Monitoring Alarm System

Code, schematics and supporting documentation for a smart alarm system that will monitor the user's sleep cycle in order to wake them at the optimal time. This system is implemented using a Raspberry Pi, bed mounted sensors and a smartphone GUI.

## Installation

1. Clone repository onto Raspberry Pi.
2. Install WiringPi library.
3. Run compiler script using ```sh compile_sleeping_beauty```
4. Connect hardware to appropriate pins.
5. Set alarm time via iOS app.
6. Start the application using ```./main```

## Motivation for the project

Sleeping is an essential part of everybody’s life. However, how often do you wake up feeling tired and wishing to press the snooze button and go back to sleep? Making the waking up process more pleasant became possible with the discoveries in human physiology and technology.

Even though we perceive sleep as a singular state of a human activity, on a physiological level there are four distinctive stages of sleep (in a single sleep cycle):

- **Stage 1:** drowsiness and very light sleep *(~10 min)*;
- **Stage 2:** light sleep: slowing heart rate, blood pressure, and decreased body temperature, falling into a deeper sleep *(~20 min)*;
- **Stage 3:** deep sleep, the heart rate, breathing, and blood pressure drop even further, the body becomes immobile *(~40 min)*;
- **Stage 4:** rapid eye movement (also known as REM), the stage when we dream.

When transitioning from one sleep cycle to another, a person typically changes their position. In fact, they are actually awake during this transition, though they will not remember later, as they almost immediately fall back asleep. This transition time is actually the optimum time for a person to wake up.  Tracking a person's movement during their sleep could therefore inform a smart alarm system when the most appropriate time to ring would be.

This concept is not new, as many apps promise to offer users a better alarm experience, typically for a subscription fee (£4/month or £25/year, depending on the app). These apps however only use the sensors available in the user's smartphone, which are somewhat inadequate for detecting changes in sleep cycle. We hope to improve on the apps by incorporating pressure sensors and an accelerometer sensors into a mattress and process their data in real time in order to more accurately detect changes in a user's sleep cycle via movement, and wake them up at the most appropriate time.

## System 

![alt text](https://github.com/npes-95/sleeping-beauty/blob/master/media/diagram_renewed_2.png)

Detailed descriptions of both the hardware and software used for this project can be found on the [Sleeping Beauty Wiki](https://github.com/npes-95/sleeping-beauty/wiki).

## Team members

- Erika Bondareva
- Nicholas Smith
- Lukas Zitinskas

Connect with us on social media, like [Twitter](https://twitter.com/SleepBeauty2018) and [Youtube](https://www.youtube.com/channel/UCnenRGqD6ltJDOzgHJ9lT9g).

## Acknowledgements

The team would like to thank Nick Bailey for his help with the peak detection algorithm.

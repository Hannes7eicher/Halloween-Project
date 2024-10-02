---
title: 'Arduino UNO R4 WiFi Halloween Pumpkin'
description: 'Learn how to build a scary pumpkin for Halloween'
author: 'Hannes Siebeneicher'
hardware:
  - hardware/02.hero/boards/uno-r4-wifi
software:
  - web-editor
  - arduinio-cloud
---

## Description

In this article, you will learn how to build an interactive scary pumpkin right in time for Halloween. The only thing you need are an UNO R4 WiFi, a small breadboard, a mini MP3 player, and a speaker. With these components and some code we provide later on, you will be able to control the pumpkin remotely, change the color of the eyes, and trigger an evil laughter.

## Hardware & Software Needed

- [Arduino UNO R4 WiFi](https://store.arduino.cc/products/arduino-uno-r4-wifi)
- [Small Breadboard](https://store.arduino.cc/products/arduino-small-breadboard?queryID=046b9d8c7014a634301007432ca00f1e)
- [DFRobot mp3 player](https://store.arduino.cc/products/dfplayer-a-mini-mp3-player?queryID=undefined)
- [Speaker](https://store.arduino.cc/products/stereo-enclosed-speaker-3w-8%CF%89?queryID=undefined)
- [Jumper Wire](https://store.arduino.cc/products/40-colored-male-female-jumper-wires?queryID=046b9d8c7014a634301007432ca00f1e)

## Step by Step

### Introduction

In this project, we will be assembling a Halloween-themed pumpkin capable of playing an evil laughter sound. This project uses an Arduino UNO R4 WiFi and a DFPlayer Mini MP3 player to bring the spooky atmosphere alive.

### Components Needed

- Arduino UNO R4 WiFi
- Small Breadboard
- DFPlayer Mini MP3 Player
- Speaker
- Jumper Wires

### Placeholder Circuit Image

![Circuit Diagram](image_placeholder_url)

### Code

Insert the code example provided below into your Arduino IDE.

```cpp
#include "DFRobotDFPlayerMini.h"

// Use hardware serial interface (Serial1)
#define MP3_SERIAL Serial1

// Create the Player object
DFRobotDFPlayerMini player;

void setup() 
{
  Serial.begin(9600);    // For debug output
  MP3_SERIAL.begin(9600); // DFPlayer Mini expected baud rate
  
  if (player.begin(MP3_SERIAL)) 
  {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(5);  // 30 is very loud
  } 
  else 
  {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() 
{
  Serial.print("Playing #1 \t");
  player.play(1);
  delay(5000);
}
```

### Summary

After completing the steps, you now have a functioning Halloween pumpkin that plays spooky sounds controlled via the Arduino UNO R4 WiFi. This interactive setup can be operated remotely, providing excellent festive decor with customizable eye colors and sound triggers.

## Code Example

The code example for this tutorial:

```cpp
#include "DFRobotDFPlayerMini.h"

// Use hardware serial interface (Serial1)
#define MP3_SERIAL Serial1

// Create the Player object
DFRobotDFPlayerMini player;

void setup() 
{
  Serial.begin(9600);    // For debug output
  MP3_SERIAL.begin(9600); // DFPlayer Mini expected baud rate
  
  if (player.begin(MP3_SERIAL)) 
  {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(5);  // 30 is very loud
  } 
  else 
  {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() 
{
  Serial.print("Playing #1 \t");
  player.play(1);
  delay(5000);
}
```

#### Important Aspects of the Code

- Inclusion of DFRobotDFPlayerMini library to control the MP3 player.
- Setup function initializes serial communication and player settings.
- Loop function controls the playback of the MP3 file.

## Summary

This tutorial guides you through building a spooky Halloween pumpkin setup using an Arduino UNO R4 WiFi. You'll learn how to assemble the hardware, connect the components, and use provided code to control both the light and sound effects, creating a delightfully eerie decoration.
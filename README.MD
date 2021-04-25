# ESP32 Employee Control

RFID Tag Control and data transfer using MQTT to the Tago.io Cloud

## Table of Contents
- [ESP32 Employee Control](#esp32-employee-control)
  - [Introduction](#introduction)
  - [Components](#components)
  - [Libraries Used for the Project](#libraries-used-for-the-project)
  - [Project Tree](#project-tree)
  - [Support Links checked during the project](#support-links-checked-during-the-project)

## Introduction

The purpose of this project was to create an integration between the RFID sensor using an ESP32 and Tago.io and show which RFID tag is being read in a dashboard. Code was created using vscode

## Components

1. MFRC522: RFID Chip used to read and write tags. Uses SPI protocol as an interface.
2. 220 Ohm Resistor: Used with the PCB button
3. Jumper Wires: Jumper Wires to connect the components external to the ESP32.
4. ESP32 MCU: Microcontroller used in this project
5. PCB Button: PCB Button to generate "RECORD MODE" in ESP32 and record new cards to the internal memory of the Microcontroller.

## Libraries Used for the Project

> | Library        | Purpose           | Link  |
> | :------------- |:-------------| :-----|
> | ArduinoJSON | Used to format data in the MQTT payload as JSON. Required to send data to the Tago.io MQTT Server| [Link Here](https://arduinojson.org)|
> | Pubsubclient | MQTT Library to connect and subscribe to MQTT Servers | [Link Here](https://pubsubclient.knolleary.net) | 
> | Mifare | Used for communicating with the MFRC522 RFID Module | [Link Here](https://www.arduino.cc/reference/en/libraries/mfrc522/)|
> | SPI | Necessary for communicating with the MFRC522 using SPI Protocol | [Link Here](https://www.arduino.cc/en/reference/SPI) |
> | Wifi | Necessary to create a wifi connection using the built-in function in the ESP32 | [Link Here](https://www.arduino.cc/en/Reference/WiFi) |

## Project Tree

>| File        | Description       
>| :------------- |:-------------| 
>| main.cpp | Main Logic of the Program |
>| connections.h | Functions to connect to Wifi, MQTT and MQTT Publish to Tago.io|
>| credentials_example.h | Used to unify password and configuration data for the connections. **Replace with your connection data**| 
> | rifidfunctions.h | Used to generate communication with the RFID Module |
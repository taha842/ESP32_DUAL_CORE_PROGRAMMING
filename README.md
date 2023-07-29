# ESP32 Dual-Core Programming

This repository contains example code for programming the ESP32's dual-core capabilities. The ESP32 microcontroller comes with two cores, which can execute tasks independently. This can be especially useful for multitasking or handling time-sensitive operations while keeping other tasks running in parallel.

## Contents

- [Introduction](#introduction)
- [Setup](#setup)
- [Code](#code)

## Introduction

The ESP32 is a powerful microcontroller with Wi-Fi and Bluetooth capabilities. It features two cores that allow developers to run tasks concurrently, taking advantage of the dual-core architecture. This repository provides sample code and tutorials to get started with ESP32 dual-core programming.

## Setup

To use the code in this repository, you'll need the following:

- ESP32 development board
- Arduino IDE or PlatformIO with ESP32 support installed
- USB cable to connect the ESP32 board to your computer

## Code

#include <Arduino.h>

TaskHandle_t Task1Handle;
TaskHandle_t Task2Handle;

void Task1(void *pvParameters) {
  while (1) {
    Serial.println("Task 1 is running on Core 1");
    delay(1000);
  }
}

void Task2(void *pvParameters) {
  while (1) {
    Serial.println("Task 2 is running on Core 0");
    delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Allow time for the serial monitor to open

  // Create Task 1 on Core 1
  xTaskCreatePinnedToCore(
    Task1,          // Function that implements the task
    "Task1",        // Task name
    10000,          // Stack size (bytes)
    NULL,           // Parameter to pass to the task
    1,              // Task priority
    &Task1Handle,   // Task handle
    1               // Core to run the task on (Core 1)
  );

  // Create Task 2 on Core 0
  xTaskCreatePinnedToCore(
    Task2,          // Function that implements the task
    "Task2",        // Task name
    10000,          // Stack size (bytes)
    NULL,           // Parameter to pass to the task
    1,              // Task priority
    &Task2Handle,   // Task handle
    0               // Core to run the task on (Core 0)
  );
}

void loop() {
  // Your main code on Core 0 goes here (if needed).
  // This loop is essentially empty since we are using the dual-core functionality.
  // Any tasks running on Core 0 are managed separately from the loop function.
}


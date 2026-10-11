# STM32 BCM Simulator

A bare-metal automotive Body Control Module (BCM) simulator built with STM32, CAN bus, and OLED dashboard.

The project simulates several basic vehicle functions and allows two STM32 nodes to communicate through a CAN bus using TJA1050 CAN transceivers.

---

## Overview

This project is a personal embedded systems project designed to simulate a simplified automotive BCM architecture.

The system is built around two STM32 Blue Pill boards communicating through a CAN bus.

One STM32 acts as a vehicle/BCM node that reads inputs and controls vehicle functions, while the other STM32 receives CAN messages and displays the vehicle state on an SSD1306 OLED dashboard.

### Main technologies

- STM32F103C8T6
- Embedded C
- STM32 HAL
- STM32CubeMX
- STM32CubeIDE
- CAN Bus
- TJA1050 CAN Transceiver
- SPI
- SSD1306 OLED
- ADC
- Timer
- GPIO
- Bare-metal architecture

---

## Features

### Vehicle functions

- Ignition ON/OFF
- Driving Mode
  - ECO
  - SPORT
- Vehicle speed simulation
- Brake state
- Cruise Control
- Turn Signal
  - Left
  - Right
  - Hazard
- OLED dashboard

### CAN communication

Vehicle states are transmitted through CAN only when their values change.

For example:

```c
if (speed == lastSpeed)
    return;
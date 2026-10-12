# Automotive Body Control Module (BCM) — STM32

An embedded automotive Body Control Module (BCM) project developed using the STM32F103C8T6 microcontroller. This repository demonstrates the evolution of an embedded control system from a Bare-Metal implementation to a FreeRTOS-based architecture.

The project focuses on modular embedded software design, peripheral drivers, event-driven processing, task communication, and CAN bus integration.

## Project Overview

The project is organized into two versions to demonstrate different approaches to embedded system development.

| Version | Architecture | Description |
|---|---|---|
| BCM V1 | Bare Metal | Super-loop architecture with modular drivers and application logic |
| BCM V2 | FreeRTOS | Multi-task architecture using queues and event-driven processing |

## Hardware

- **Microcontroller:** STM32F103C8T6 (Blue Pill)
- **Debugger/Programmer:** ST-LINK V2
- **Communication:** CAN bus, UART
- **Display:** SSD1306 OLED (I2C/SPI driver)
- **Inputs:** Push buttons
- **Outputs:** LEDs

## Software and Tools

- C
- STM32 HAL
- CMSIS
- FreeRTOS
- STM32CubeIDE

## Repository Structure

```text
Automotive-BCM-STM32/
├── BCM_v1_BareMetal/
│   └── Bare-Metal implementation
│
├── BCM_v2_FreeRTOS/
│   └── FreeRTOS implementation
│
└── README.md
```

Each version is maintained as a separate project, allowing its architecture and implementation to be studied independently.

## BCM V1 — Bare Metal

The first version implements the BCM application using a super-loop architecture without an RTOS.

### Key Features

- Ignition ON/OFF control
- ECO/SPORT driving mode selection
- Button input handling and debouncing
- Modular application and driver layers
- SSD1306 OLED display driver
- Peripheral integration using STM32

### Architecture

The application is separated into logical modules to improve maintainability and reusability.

```text
Application
    |
    v
BCM Logic
    |
    v
Services
    |
    v
Drivers
    |
    v
STM32 HAL / CMSIS
    |
    v
Hardware
```

## BCM V2 — FreeRTOS

The second version refactors the system into a task-based architecture using FreeRTOS.

The main objective is to separate input acquisition, BCM decision-making, CAN communication, and hardware output handling into independent software components.

### Key Features

- FreeRTOS task-based architecture
- Inter-task communication using queues
- Event-driven BCM state management
- Ignition state control
- ECO/SPORT driving mode selection
- CAN frame reception and vehicle speed processing
- Modular input, BCM logic, CAN, and output components

### System Architecture

```text
          InputTask
              |
              | BCM events
              v
        bcmEventQueue
              |
              v
           BCMTask
              |
              | Output commands
              v
        bcmOutputQueue
              |
              v
          OutputTask


            CANTask
              |
              | CAN frame reception
              v
       Vehicle Speed Event
              |
              v
        bcmEventQueue
```

### FreeRTOS Tasks

| Task | Responsibility |
|---|---|
| `InputTask` | Reads button states and generates BCM events |
| `BCMTask` | Processes events and updates BCM application states |
| `CANTask` | Receives CAN frames and processes vehicle speed data |
| `OutputTask` | Processes output commands and controls hardware outputs |

### Event and Queue Processing

The BCM application uses queues to decouple input acquisition from application logic and output control.

For example, when the ignition button is pressed:

1. `InputTask` detects the button press.
2. An ignition event is sent to `bcmEventQueue`.
3. `BCMTask` receives the event and toggles the ignition state.
4. The BCM generates an output command.
5. `OutputTask` receives the command and updates the corresponding LED.

The CAN task follows a similar pattern by converting received vehicle speed frames into BCM events.

### Driving Modes

The system supports two driving modes:

| Mode | Maximum Speed Target |
|---|---:|
| ECO | 45 km/h |
| SPORT | 70 km/h |

These values represent application-level targets for the project. Actual vehicle speed limiting and safety-critical control are outside the scope of the current prototype.

## Learning Objectives

Through this project, I aim to develop practical experience in:

- Embedded C programming and STM32 peripheral control
- Register-level concepts and hardware abstraction
- Modular firmware architecture
- Finite state machines and event-driven design
- Real-time task scheduling with FreeRTOS
- Queue-based inter-task communication
- CAN bus communication and message parsing
- Firmware debugging and version control

## Project Status

The project is under active development. BCM V1 provides the Bare-Metal baseline, while BCM V2 is being developed to introduce RTOS-based task separation and communication.

Planned improvements include:

- Expanding CAN message handling
- Improving error handling 
- Adding system testing and documentation




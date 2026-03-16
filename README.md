<div align="center">

# 🌌 Autonomous Navigator V3.0
**The Pinnacle of Micromouse Intelligence**

[![GitHub stars](https://img.shields.io/github/stars/gowthamnow/Autonomous-Navigator-with-Algorythms?style=flat-square&color=blue)](https://github.com/gowthamnow/Autonomous-Navigator-with-Algorythms)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://opensource.org/licenses/MIT)
[![Status: Production Ready](https://img.shields.io/badge/Status-Production_Ready-brightgreen?style=flat-square)](#)
[![Algorithm: Flood Fill](https://img.shields.io/badge/Algorithm-Flood_Fill-orange?style=flat-square)](#)

*An advanced, 32-bit autonomous robotics platform engineered to solve 16x16 mazes with devastating speed and sub-millimeter precision. Powered by STM32, fused Time-of-Flight telemetry, and dynamic PID orchestration.*

<br/>

![Robofest 2024 Winning Run](Winning_Photos/ROBOFEST_WINNING/1021%20-%20Robofest.png)
**🏆 Undisputed Champion – Robofest 2024 Regional Finals**

</div>

---

## ⚡ Core Capabilities

| 🧠 True Autonomy | 🏎️ Ballistic Speed | 🎯 Absolute Precision |
| :--- | :--- | :--- |
| **Real-Time Mapping**: The `Flood Fill` engine recalculates the optimal path across 256 cells in under 2 milliseconds. | **Zero to Top Speed**: Weighing just 142g, the dual GA12-N20 gearboxes deliver instant torque for explosive straightaways. | **Laser Telemetry**: A fusion of five VL-series ToF sensors provides 360° environmental mapping unaffected by surface coloration. |

---

## 🧬 Architectural Masterpiece

The system architecture is decoupled into distinct sensory, logic, and actuation planes, mirroring advanced avionics systems.

```mermaid
graph TD
    subgraph PERCEPTION ["👁️ Sensory Fusion Layer"]
        A((VL53L0X Front))
        B((VL6180X Left/Right))
        C((VL6180X Diagonals))
    end
    
    subgraph COGNITION ["🧠 Logic & Pathing Layer"]
        D{STM32 Cortex-M3}
        E[Linear PD Controller]
        F[16x16 Flood Fill Core]
    end
    
    subgraph ACTUATION ["🦾 Kinematics Layer"]
        G[TB6612FNG Dual H-Bridge]
        H((Left DC Drive))
        I((Right DC Drive))
    end

    A & B & C -- 400kHz I2C --> D
    D <--> F
    D --> E
    E -- Fast PWM --> G
    G --> H & I
    H & I -- Optical Encoders --> D
```

---

## 🦾 Hardware Evolution

Greatness is iterated. The Autonomous Navigator is the result of relentless refinement across three distinct hardware generations.

<details open>
<summary><b>🔹 Generation 3: "The SMT Edge" (Current Pro Version)</b></summary>
<br>
The ultimate competitive form. Transitioned entirely to 0603 Surface Mount Technology (SMT) for radical weight reduction. Integrated motor drive planes and edge-mounted ToF topology.

| Top Chassis View | Raw PCB Design |
| :---: | :---: |
| <img src="Pictures/Bot_view1.jpeg" height="250" alt="Generation 3 SMT Bot"> | <img src="Pictures/fab_Board.jpeg" height="250" alt="Generation 3 PCB"> |
</details>

<details open>
<summary><b>🔹 Generation 2: "The Double Layer"</b></summary>
<br>
The breakthrough. Introduced professional 2-layer FR4 routing with top-layer ground planes for superior EMI rejection.

| Assembled Robot | Board Layout |
| :---: | :---: |
| <img src="Pictures/ASSEMBLED_ROBO.HEIC" height="250" alt="Generation 2 Robot"> | <img src="Pictures/double_layer_layout.png" height="250" alt="Generation 2 PCB Layout"> |
</details>

<details open>
<summary><b>🔹 Generation 1: "The Debut" (Single Layer)</b></summary>
<br>
The proof of concept. A manually etched, single-layer board relying on through-hole components to validate the foundational Flood Fill C++ algorithms.

<div align="center">
  <img src="Pictures/SINGLE_LAYER.HEIC" height="250" alt="Generation 1 Single Layer PCB">
</div>
</details>

---

## 🛠️ The Technology Stack

### 1. The Cortex: STM32 Bluepill (ARM Cortex-M3)
<img align="right" src="Pictures/stm32_bluepill.png" width="150" alt="STM32">
The beating heart of the robot. Operating at 72 MHz, it easily outpaces standard 8-bit microcontrollers, allowing for complex floating-point PID math and multi-bus I2C polling without skipping a single beat of the 10ms control loop.

### 2. The Muscle: TB6612FNG Driver
A highly efficient dual H-Bridge. It channels up to 1.2A of continuous current to the gearboxes with 95% efficiency, utilizing a Phase/Enable logic structure that drastically simplifies code logic.

### 3. The Eyes: STMicroelectronics Time-of-Flight
Unlike archaic IR sensors, the **VL53L0X** and **VL6180X** measure the actual time it takes for a photon to bounce off a wall at the speed of light. This guarantees flawless ranging regardless of whether the maze walls are painted matte black or glossy white.

---

## 💻 The Code Base (A Look Inside the Logic)

The firmware is broken out into granular modules for extreme maintainability.

> 💡 **Algorithm Insight:** The `Flood Fill` algorithm conceptually "floods" the maze from the center outwards. Each cell is assigned a "Manhattan Distance" to the goal. The robot simply rolls downhill, always choosing the adjacent cell with the lowest numerical value.

| Module | Purpose | Advanced Mechanics Implemented |
| :--- | :--- | :--- |
| `Algo.ino` | **The Mastermind** | Houses the 256-cell bitmask array and the `cellForward()` dead-reckoning state machine. |
| `PID.ino` | **The Stabilizer** | Executes the Proportional-Derivative math `(P*Error) + (D*$\Delta$Error)` to keep the robot dead-center in the 180mm corridors without oscillating. |
| `Motor.ino` | **The Actuator** | Abstracts digital PIN calls into high-level commands like `leftBrake()`, utilizing back-EMF to abruptly halt the robot. |
| `Turns.ino` | **The Navigator** | The dispatcher that prioritizes right-hand exploration but defers to the BFS map during the final Speed Run. |
| `Sensor.ino`| **The Interrogator**| Handles the complex I2C Time-Division Multiplexing required to poll 5 separate laser sensors without bus collision. |

---

## 🚀 Assembly & Deployment

We believe in open engineering. To replicate this platform:

1.  **Fabrication**: Send the `PCB_SMD_DESIGN_FILES` to JLCPCB or PCBWay.
2.  **Assembly**: We recommend strict adherence to impedance control for the I2C traces. Solder all 0.1μF decoupling capacitors as close to their respective ICs as geometrically possible.
3.  **Toolchain**:
    - Install **Arduino IDE**.
    - Add the **STM32 Core** via the Boards Manager.
    - Install the `QueueArray.h` and Adafruit `VL53L0X`/`VL6180X` libraries.
4.  **Flashing**: Connect an ST-Link V2. Select "Generic STM32F103C series" and upload `Algo.ino`.

---

## 📊 Analytics & Performance

> *"It doesn't just solve mazes; it dominates them."*

The following statistics were recorded during the **Robofest 2024 Finals**:
*   **Mapping Run**: `42s` (Zero wall collisions).
*   **Golden Speed Run**: `18s` (Max velocity tracking, multi-cell lookahead engaged).
*   **Sensor Jitter**: `< 2mm` variance under intense stage lighting.

---

<div align="center">
  <b>Designed, Engineered, and Open-Sourced by Gowtham.</b><br>
  Released under the <a href="https://opensource.org/licenses/MIT">MIT License</a>.
</div>

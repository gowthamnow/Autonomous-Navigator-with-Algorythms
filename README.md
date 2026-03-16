# 🤖 Autonomous Navigator: Advanced Micromouse & Maze Solver

[![GitHub stars](https://img.shields.io/github/stars/gowthamnow/Autonomous-Navigator-with-Algorythms?style=social)](https://github.com/gowthamnow/Autonomous-Navigator-with-Algorythms)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Autonomous Navigator** is a high-performance, precision-engineered Micromouse robot designed to solve complex mazes using the legendary **Flood Fill Algorithm**. This repository showcases the evolution of the project through three distinct iterations of hardware design, control theory integration, and competitive success.

---

## 🏆 Achievement: Robofest Winner
The Autonomous Navigator secured a top position at **Robofest**, demonstrating exceptional speed and algorithmic efficiency in solving the competition maze.

<div align="center">
  <img src="Winning_Photos/ROBOFEST_WINNING/1021 - Robofest.png" width="600" style="border-radius: 10px; border: 3px solid #FFD700;">
  <p><i>Winner's Podium at Robofest</i></p>
</div>

---

## 🏎️ Hardware Evolution: Three Generations

This project has evolved through three hardware versions, each optimizing for size, reliability, and manufacturing complexity.

### 1. SMT Version (Advanced)
The flagship version featuring high-density Surface Mount Technology for a compact footprint and superior performance.
- **Key Features**: STM32 Onboard, compact power regulation, high-speed signal integrity.
- **Files**: `PCB_SMD_DESIGN_FILES/`

<div align="center">
  <table style="border-collapse: collapse; border: none;">
    <tr>
      <td align="center"><img src="Pictures/3D_VIEW.png" width="350"><br><b>3D Render</b></td>
      <td align="center"><img src="Pictures/Bot_view1.jpeg" width="350"><br><b>Assembled SMT Bot</b></td>
    </tr>
  </table>
</div>

### 2. Double Layer Version (Standard)
A robust version designed for standard PCB manufacturing, balancing complexity and reliability.
- **Key Features**: Dual-side routing, optimized component placement for weight distribution.
- **Files**: `SINGLE_DOUBLE_LAYER_PCB_DESIGN/DOUBLE_LAYER/`

<div align="center">
  <img src="Pictures/double_layer_layout.png" width="500" style="border-radius: 8px;">
  <p><i>Double Layer PCB Layout</i></p>
</div>

### 3. Single Layer Version (Prototyping)
An accessible version designed for rapid prototyping and home fabrication.
- **Key Features**: Single-side routing, easy to solder, ideal for educational purposes.
- **Files**: `SINGLE_DOUBLE_LAYER_PCB_DESIGN/SINGLE_LAYER/`

<div align="center">
  <img src="Pictures/fab_Board.jpeg" width="400" style="border-radius: 8px;">
  <p><i>Single Layer Fabrication Board</i></p>
</div>

---

## 🧠 Algorithmic Core

### 1. The Algorithm: Flood Fill
The robot solves the maze by mapping a "potential flow" from any cell to the center.
- **Dynamic Updates**: Detects walls using ToF sensors and updates the `cells[16][16]` array in real-time.
- **Path Optimization**: Recalculates the shortest path after every cell movement.

### 2. Control Theory: PD Regulation
- **Wall Following**: Uses a Proportional-Derivative (PD) controller to stay centered.
- **Stability**: High-speed correction leads to smooth navigation and sharp turns.

### 3. Perception: ToF Sensor Fusion
- **Sensors**: 3x VL53L0X (Long Range) + 2x VL6180X (Short Range).
- **Precision**: Millimeter-level accuracy for perfect alignment.

---

## 📺 Project in Action (Videos)

Experience the robot solving mazes and testing sensors:

1. 🥇 **[Winning Maze Run (Shortest Time)](Event_Working_Video/Ultrasonic%202%20Winner%20maze%20solving%20in%20shortest%20time.mp4)**
2. 🔍 **[ToF Sensor Performance 1](Event_Working_Video/ToF%20Sensor%201.mp4)**
3. 📉 **[ToF Sensor Performance 3](Event_Working_Video/ToF%20Sensor%203.mp4)**
4. 📍 **[Sensor Calibration at KCT](Event_Working_Video/TOF%20Sensor%204%20at%20KCT%20(1).mp4)**
5. ⚡ **[Ultrasonic Sensor Test at Bannari](Event_Working_Video/Ultrasonic%20Sensor%20at%20Bannari.mp4)**

---

## 📂 Repository Structure

```text
├── CODE/                        # Arduino/C++ Firmware (Flood Fill, PID, Sensors)
├── PCB_SMD_DESIGN_FILES/         # Altium/SMD PCB Files (SMT Version)
├── SINGLE_DOUBLE_LAYER_PCB_DESIGN/ # DipTrace/PCB Files (Single/Double Layers)
├── Event_Working_Video/          # Full test runs and competition videos
├── Winning_Photos/               # Robofest and Event awards
└── Pictures/                    # Hardware renders and bot photos
```

---

## 🚀 Getting Started

1. **Firmware**: Open `CODE/Algo.ino` in Arduino IDE. Ensure STM32 core is installed.
2. **Hardware**: Choose your version (SMT, Single, or Double) from the respective design folders.
3. **Calibrate**: Use `Sensor.ino` to calibrate your ToF sensors for the specific maze environment.
4. **Deploy**: Upload and watch the bot solve the maze!

---

## 🤝 Developed By
**Gowtham** - Robotics & Embedded Systems Enthusiast
[Portfolio/GitHub](https://github.com/gowthamnow)

---
*Autonomous Navigator - Pushing the boundaries of micromouse robotics.*

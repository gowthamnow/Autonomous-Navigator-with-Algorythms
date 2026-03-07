# 🤖 Autonomous Navigator: Advanced Micromouse

[![GitHub stars](https://img.shields.io/github/stars/gowthamnow/Autonomous-Navigator-with-Algorythms?style=social)](https://github.com/gowthamnow/Autonomous-Navigator-with-Algorythms)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Autonomous Navigator** is a high-performance, precision-engineered Micromouse robot designed to solve complex 16x16 mazes using the legendary **Flood Fill Algorithm**. Featuring an STM32-based custom PCB and a suite of Time-of-Flight sensors, it represents the intersection of robotics, control theory, and efficient pathfinding.

---

## 📸 Project Gallery

<div align="center">
  <table style="border-collapse: collapse; border: none;">
    <tr>
      <td align="center" style="padding: 10px;">
        <b>Fabricated Hardware</b><br>
        <img src="Pictures/fab_Board.jpeg" width="350" height="250" style="object-fit: cover; border-radius: 8px; border: 2px solid #333;">
      </td>
      <td align="center" style="padding: 10px;">
        <b>Fully Assembled Bot</b><br>
        <img src="Pictures/Bot_view1.jpeg" width="350" height="250" style="object-fit: cover; border-radius: 8px; border: 2px solid #333;">
      </td>
    </tr>
    <tr>
      <td align="center" style="padding: 10px;">
        <b>Bottom Chassis View</b><br>
        <img src="Pictures/Bot_View2.jpeg" width="350" height="250" style="object-fit: cover; border-radius: 8px; border: 2px solid #333;">
      </td>
      <td align="center" style="padding: 10px;">
        <b>PCB Routing Layout</b><br>
        <img src="Pictures/Layout.png" width="350" height="250" style="object-fit: cover; border-radius: 8px; border: 2px solid #333;">
      </td>
    </tr>
    <tr>
      <td align="center" colspan="2" style="padding: 10px;">
        <b>Isometric 3D Design</b><br>
        <img src="Pictures/3D_VIEW.png" width="350" height="250" style="object-fit: cover; border-radius: 8px; border: 2px solid #333;">
      </td>
    </tr>
  </table>
</div>

---

## 🧠 How It Works: Deep Dive

### 1. The Algorithm: Flood Fill
The robot solves the maze by mapping a "potential flow" from any cell to the center.
- **Grid Mapping**: Maintains a 16x16 coordinate system.
- **Dynamic Updates**: As the robot explores, it detects walls using sensors and updates the `cells[16][16]` array.
- **Path Calculation**: The `floodFill3()` function recalculates the shortest distance to the goal after every cell movement, ensuring the robot always takes the most efficient path.

### 2. Control Theory: PD Regulation
Navigation isn't just about logic; it's about hardware stability.
- **Error Correction**: Uses a Proportional-Derivative (PD) controller to maintain a perfectly centered position between walls.
- **High-Speed Stability**: The `wallPid()` function adjusts motor PWM values in real-time to correct drift, enabling the bot to run at high velocities without crashing.

### 3. Perception: ToF Sensor Fusion
The bot "sees" using infrared Time-of-Flight sensors (VL53L0X & VL6180X).
- **Multi-Directional Awareness**: Sensors are placed at the front, left, and right to provide 180-degree spatial awareness.
- **Precision Scanning**: Millimeter-level accuracy allows for perfect alignment before making sharp, 90-degree turns.

---

## 🛠️ Hardware Specifications

| Component | Specification |
| :--- | :--- |
| **Microcontroller** | STM32 (ARM Cortex-M) |
| **Sensors** | 3x VL53L0X (Long Range), 2x VL6180X (Short Range) |
| **Motors** | High-RPM Micro Gear Motors with Magnetic Encoders |
| **PCB Design** | Multi-layer custom Altium design in `PCB_DESIGN_FILES` |

---

## 📂 Repository Roadmap

### 💻 [Firmware (CODE)](CODE/)
- **[Algo.ino](CODE/Algo.ino)**: The brain of the bot. Contains coordinate tracking and Flood Fill logic.
- **[PID.ino](CODE/PID.ino)**: Mathematics of movement. Implements the PD loop for wall following.
- **[Sensor.ino](CODE/Sensor.ino)**: Hardware abstraction layer for the I2C ToF sensors.
- **[Turns.ino](CODE/Turns.ino)**: High-level state machine for maze-solving decisions.

### 📐 [Hardware (PCB_DESIGN_FILES)](PCB_DESIGN_FILES/)
- **STM32 ONBOARD.PcbDoc**: The physical layout, optimized for high-speed signal integrity and compact form factor.
- **Sheet1.SchDoc**: Electrical schematic showing power regulation and sensor interfacing.

---

## 🚀 Getting Started

1. **Hardware Assembly**: Order the PCB using the files in `PCB_DESIGN_FILES`.
2. **Setup IDE**: Use Arduino IDE with the STM32 core installed.
3. **Calibrate Sensors**: Run a baseline test to ensure the ToF sensors are reading correctly via Serial.
4. **Deploy**: Upload the firmware and watch the bot solve the maze!

---

## 🤝 Developed By
**Gowtham** - Robotics & Embedded Systems Enthusiast
[Check out my other projects!](https://github.com/gowthamnow)

---
*Autonomous Navigator - Pushing the boundaries of micromouse robotics.*

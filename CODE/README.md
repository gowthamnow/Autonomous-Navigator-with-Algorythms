# 🤖 Autonomous Navigator with Algorithms

An efficient and intelligent **maze solver robot** that uses a combination of **ToF sensors**, **encoder motors**, and **PID control**, powered by the **TB6612FNG motor driver**. It solves mazes using the **Flood Fill Algorithm**, optimized to find the **shortest path in real time**.

---

## 🧠 Project Summary

This robot is designed to **navigate mazes autonomously** using a sensor-driven approach combined with advanced pathfinding algorithms. It can detect walls, calculate optimal routes, and dynamically adjust its movements based on encoder feedback and precise PID tuning.

---

## 🚀 Features

- ✅ **Time-of-Flight (ToF) Sensors** for accurate wall distance measurement  
- ✅ **Flood Fill Algorithm** with **modified shortest path optimization**  
- ✅ **PID Controller** for real-time direction & speed correction  
- ✅ **TB6612FNG Dual H-Bridge Motor Driver** for precise control  
- ✅ **Encoder-based Motors** for tracking distance and rotation  
- ✅ Efficient memory map for maze grid solving  
- ✅ Customizable for micromouse competitions and AI robotics

---

## 🧰 Hardware Used

| Component               | Description |
|------------------------|-------------|
| **Arduino/ESP32**      | Microcontroller |
| **VL53L0X ToF Sensors**| Wall detection (front, left, right) |
| **TB6612FNG Driver**   | Dual motor controller |
| **Encoder DC Motors**  | Accurate movement + feedback |
| **Li-ion Battery Pack**| Power source |
| **Chassis & Wheels**   | Robot base |

---

## 📦 Software Stack

- **C/C++ (Arduino IDE)** – Real-time motor and sensor control
- **PID Algorithm** – Smooth navigation and wall-following
- **Flood Fill Algorithm** – Solving unknown maze grids
- **EEPROM Mapping** – Memory-based maze exploration
- Optional future: Python/ROS for simulation and GUI visualization

---

## 📐 Flood Fill Algorithm (Modified)

- Robot explores the maze by assigning **distance weights** to each cell.
- Walls are detected and updated using **ToF sensors**.
- After the initial run, the robot calculates the **shortest path** to the goal.
- A **modified flood fill** is used:
  - Less memory
  - Adaptive re-mapping
  - Early exit if a shorter sub-path is found
  - Optional diagonal bias or cost-based reweighting

---

## 🔄 PID Tuning Details

| Parameter | Role |
|----------|------|
| **P**    | Immediate reaction to wall distance error |
| **I**    | Compensates accumulated drift |
| **D**    | Smooths sudden deviation |

PID tuning ensures:
- Wall hugging
- Center alignment
- Minimal overshoot in tight turns

---

## 🧪 How It Works

1. **Initialization**: Map grid created (e.g., 16x16 or 8x8)
2. **Sensor Input**: ToF sensors detect walls in 3 directions
3. **PID Controller**: Adjusts motor speed for smooth steering
4. **Flood Fill**: Updates cell values to find goal
5. **Shortest Path Run**: Executes final path from start to goal
6. **Encoder Feedback**: Ensures accurate cell-to-cell motion

---

## 🛠️ Setup Instructions

1. Wire TB6612FNG to motors and microcontroller (A1, A2, B1, B2, PWM, STBY)
2. Connect VL53L0X sensors via I2C (different addresses)
3. Tune PID values in Arduino
4. Upload `navigator.ino` (provide sample code if needed)
5. Place robot in maze and run!

---

## 📷 Images & Videos

*Coming Soon — 3D models and real test runs with actual maze.*

---

## 📈 Future Work

- Implement A* pathfinding for even more optimized routing
- Add BLE for remote commands
- Integrate with ROS for simulation
- Upgrade to AI-based SLAM

---

## 👨‍💻 Developed By

> Team Vision — Experts in Embedded Systems, Robotics, and AI Innovation  
> Specializing in C/C++ for real-time systems, PCB and hardware design, and resilient AI development.

---

## 📄 License

MIT License – Free to modify and expand for educational and competitive use.


# Secure-Door 📡
Smart Door Alert System (Home Security Project)

# 🔐 Smart Door Alert System with Ultrasonic Sensor (Arduino)

## 📌 Overview

The **Smart Door Alert System** is a home security project built with **Arduino** that uses an **ultrasonic sensor** to detect how close someone is to your door or window. It uses **LEDs**, a **buzzer**, and a **flashing light** to provide a visual and audible alert when someone approaches.

This system acts **before** an intruder tries to open the door or knock, making it useful for **early intrusion detection**.

---

## 🚦 Features

- 🟢 **Green LED** – Safe (No one near)
- 🟡 **Yellow LED + slow buzzer** – Someone approaching
- 🔴 **Red LED + flashing light + fast buzzer** – Someone very close
- 🚨 **Dynamic alerts based on distance**
- 📉 **Distance smoothing logic** to improve accuracy
- 🖥️ **Serial Monitor output** for debugging

---

## 🧰 Hardware Requirements

| Component           | Quantity | Description                            |
|--------------------|----------|----------------------------------------|
| Arduino UNO/Nano   | 1        | Microcontroller                        |
| Ultrasonic Sensor (HC-SR04) | 1  | Measures distance                     |
| LED (Green)         | 1        | Safe status                            |
| LED (Yellow)        | 1        | Warning status                         |
| LED (Red)           | 1        | Danger status                          |
| Flashing LED        | 1        | Extra visual alert                     |
| Buzzer              | 1        | Sound alert                            |
| Resistors (220Ω)    | 4        | For LEDs                               |
| Jumper Wires        | —        | For connections                        |
| Breadboard          | 1        | Prototype layout                       |

---

## 📐 Circuit Connections

| Component      | Arduino Pin |
|----------------|-------------|
| HC-SR04 Trig   | D9          |
| HC-SR04 Echo   | D8          |
| Green LED      | D2          |
| Yellow LED     | D3          |
| Red LED        | D4          |
| Flashing LED   | D5          |
| Buzzer         | D6          |

Connect LEDs in series with 220Ω resistors to GND.

---

## ⚙️ How the Code Works

1. The **HC-SR04 ultrasonic sensor** measures distance using the `Trig` and `Echo` pins.
2. A **moving average** is calculated over 5 readings for **distance smoothing**.
3. Based on the **average distance**, different alert levels are triggered:

   | Distance (cm)    | Alert State                     |
   |------------------|----------------------------------|
   | > 100 cm         | Green LED ON (Safe)              |
   | 50–100 cm        | Yellow LED ON, slow buzzer       |
   | 30 cm or less    | Red LED + Flashing LED + fast buzzer |

4. If no echo is received or reading is invalid (e.g. out of sensor range), it skips that reading.

---

## 🧠 Logic Flow

```text
Start → Measure Distance →
    If > 100 cm → Green ON
    If 50–100 cm → Yellow ON + Slow Buzzer
    If ≤ 30 cm → Red ON + Flash LED + Fast Buzzer


🚀 Getting Started
Upload the code to your Arduino board.
Build the circuit as shown in the circuit diagram.
Open the Serial Monitor (Ctrl+Shift+M) at 9600 baud.
Place your hand in front of the ultrasonic sensor and observe LED and buzzer behavior.



📦 Code Summary
Uses pulseIn() to measure ultrasonic echo time.
Calculates distance using sound speed:
distance = duration * 0.0343 / 2;
Implements smoothing via a simple moving average.
Uses delay() to control buzzer beeping speed and flash LED timing.



🧩 Customization Ideas
Adjust distance thresholds for finer detection.
Replace the flashing LED with a strobe light or camera trigger.
Add a GSM module to send SMS alerts.
Add a PIR sensor for dual-sensing.


👩‍💻 Author
Shivani
Project: Smart Door Alert System using Arduino
For academic/hobby/home security use 🔐


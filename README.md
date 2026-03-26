# IoT Sound-Reactive RGB LED System 🎶💡

A professional IoT-based sound-reactive lighting system that synchronizes an RGB LED with real-time audio from your laptop or PC. Built using **ESP32**, **Blynk IoT**, and **Python Audio Analysis**.

## 🚀 Features
- **Real-Time Sound Reactivity**: Syncs RGB LED colors with audio peaks (beats) detected from the laptop microphone.
- **Dynamic Beat Detection**: Intelligent audio analysis using Python to generate vibrant, random colors on sound peaks.
- **Dual Control Modes**:
  - **Auto Mode**: Synchronous sound-reactive lighting via Serial communication.
  - **Manual Mode**: Full remote control over RGB color sliders via the Blynk mobile app.
- **Blynk IoT Integration**: Remote Power ON/OFF and mode switching from anywhere.
- **Micro-Dosing Silence**: Automatic LED shut-off during periods of silence.

---

## 🛠️ Tech Stack
- **Firmware**: C++ (Arduino/ESP32)
- **Software**: Python 3.10+
- **IoT Platform**: Blynk Cloud
- **Communication**: Serial (Python to ESP32) & WiFi (ESP32 to Blynk)

---

## 📂 Project Structure
- `project_iot.ino`: ESP32 firmware for hardware control and Blynk integration.
- `Iot_project.py`: Python script for real-time audio capture, signal processing, and Serial data transmission.
- `ESP32_WiFi/`: Folder containing WiFi and library configurations.

---

## 🔌 Hardware Requirements
- **ESP32** Dev Board
- **RGB LED** (Common Cathode/Anode)
- **Resistors** (e.g., 220Ω for Red, Green, and Blue pins)
- **Jumper Wires** & **Breadboard**
- **Micro-USB Cable**

### Pin Configuration (ESP32)
- **Red Pin**: GPIO 25
- **Green Pin**: GPIO 26
- **Blue Pin**: GPIO 27
- **Common Pin**: GND (Cathode) or 3.3V (Anode)

---

## ⚙️ Setup & Installation

### 1. ESP32 Setup
1. Open `project_iot.ino` in the Arduino IDE.
2. Install the **Blynk** library.
3. Update your WiFi credentials and Blynk Auth Token:
   ```cpp
   char ssid[] = "YOUR_WIFI_NAME";
   char pass[] = "YOUR_WIFI_PASSWORD";
   #define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN"
   ```
4. Upload the code to your ESP32.

### 2. Python Setup
1. Ensure you have Python 3.x installed.
2. Install the required libraries:
   ```bash
   pip install sounddevice numpy pyserial
   ```
3. Update the `SERIAL_PORT` in `Iot_project.py` (e.g., `COM7` on Windows or `/dev/ttyUSB0` on Linux/macOS).

---

## 🎮 How to Use
1. **Power Up**: Plug in your ESP32 and ensure it connects to the Blynk Cloud.
2. **Launch Blynk**: Use the Blynk app to turn the system **ON** and select **Auto** mode.
3. **Run the Script**: Start the Python script to begin sound analysis:
   ```bash
   python Iot_project.py
   ```
4. **Play Music**: Play any audio on your laptop. The LED will pulse and change colors in sync with the beat!

---

## 👨‍💻 Author
**Bassel**  
*3rd Year Internet of Things Student - SUT*

---

## 📄 License
This project is licensed under the MIT License - see the LICENSE file for details.
# Alive_human_detection_bot
An IoT-based system to detect living humans using multiple sensors with real-time cloud integration via MQTT, Grafana, and remote control via Blynk.
# 🚨 Alive Human Detection Bot 🤖 | Winner @ IOTMANIA '25

![GitHub stars](https://img.shields.io/github/stars/KnowME-AS-Aditya/Alive_human_detection_bot?style=social)
![GitHub last commit](https://img.shields.io/github/last-commit/KnowME-AS-Aditya/Alive_human_detection_bot)
![License](https://img.shields.io/github/license/KnowME-AS-Aditya/Alive_human_detection_bot)

> 🏆 First Prize Winner @ **IOTMANIA**, Elysium 2025, SOA University — presented by **SOA Flying Community**  
> An IoT system capable of **detecting living humans in hazardous environments** using multiple sensors and real-time dashboards.

---

## 🧠 Project Summary

This project leverages **ESP32**, multiple sensors, and cloud tools like **MQTT** and **Grafana** to detect signs of life — motion, heartbeat, temperature, gases — and relay them to a real-time dashboard. It was built for emergency applications like **search & rescue** or **fire evacuations**, and even includes **remote control via Blynk**.

---

## 🔧 Tech Stack

- **Microcontroller**: ESP32 NodeMCU
- **Programming Language**: Arduino (C++)
- **Dashboard**: Grafana Cloud (via MQTT)
- **Control Interface**: Blynk App
- **Data Protocol**: MQTT , I2C
- **IDE**: Arduino IDE, Notepad++ (for repo)

---

## 🔌 Sensors & Components Used

| Sensor/Module      | Purpose                         |
|--------------------|----------------------------------|
| MAX30102           | Heart rate / SpO2               |
| PIR Sensor         | Motion detection                |
| HC-SR04            | Distance detection              |
| MQ-2 Gas Sensor    | Hazardous gas detection         |
| MLX90614           | Infrared temperature            |
| HC-05 (optional)   | Bluetooth module                |

---

## 📸 Screenshots

### MODEL_BOT [codenamed: *SANJIVANI*]
![Anterior view](images/dashboard.png)
![Lateral View](images/dashboard.png)



### 🔍 Grafana Dashboard Sample
![Dashboard Screenshot](images/Screenshot%202025-03-26%20082501.png)


---

## 🔩 Folder Structure
Alive_human_detection_bot/
├── Arduino_code/ # ESP32 Arduino code (.ino)
│ └── working3.ino
├── Grafana_Dashboard_sample/ # JSON files for sensor dashboards
│ └── SensorOutDashboard.json
├── images/ # Screenshots and setup images
│ └── *.png, *.jpg
├── docs/ # (Optional) Circuit diagrams or project flow
│ └── architecture.png
├── LICENSE
├── README.md

---

## 🚀 Setup Instructions

### 🔧 1. Flash Code to ESP32
- Open `Arduino_code/working3.ino` in Arduino IDE
- Install required libraries:
  - `MAX30105`, `Adafruit_MLX90614`, `PubSubClient`, etc.
- Select correct **Board & Port**
- Flash code to ESP32

### 🌐 2. Set Up Grafana Dashboard
- Create an MQTT data source in Grafana Cloud
- Import JSON from `Grafana_Dashboard_sample/`
- Connect ESP32's MQTT output to the cloud broker

### 📱 3. Setup Blynk Control (Optional)
- Use Blynk Legacy or Blynk 2.0 app
- Map digital control pins for motor/power or alerts

---

## 🧑‍🤝‍🧑 Contributors

| Name                 | Role                        |
|----------------------|-----------------------------|
| Aditya Ranjan Sahoo  | Sensors Integration, Codeware, Dashboard |
| Sourav Agrawal       | Blynk Interface, Testing, Firmware |
| Rajdeep Mohanty      | ESP-32 nodeMcu configurer, DESIGN base | 
| Abinash Nanda        | Servo ARM curation, remote-controlled Sync, Firmware & Testing |

---

## 🪪 License

Licensed under the [Apacahe 2.0](LICENSE)

---

## 💬 Acknowledgements

- SOA Flight Club & IOTMANIA 2025 Judges, Elysium 2025
- Open source contributors (Arduino, MQTT, Grafana)

---

## 🌟 Let's Connect

**Show your support** by ⭐ starring this repository.  
Feel free to [connect with me on LinkedIn](https://www.linkedin.com/in/aditya-ranjan-sahoo) and explore more cool tech projects!

---

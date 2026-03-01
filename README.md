# 🌿 Air Quality Monitoring System (ESP32 + Blynk)

## 📌 Overview
An IoT-based air quality monitoring system built using ESP32.  
The system measures air quality using MQ135 and temperature/humidity using DHT11.  
LED indicators show air quality levels, and data is monitored remotely using Blynk Cloud.

---

## 🛠 Components Used
- ESP32
- MQ135 Gas Sensor
- DHT11 Sensor
- Green LED (Good)
- Blue LED (Moderate)
- Red LED (Harmful)
- Blynk IoT Platform

---

## ⚙️ Working
- MQ135 detects air quality levels.
- ESP32 reads sensor values.
- LED indication:
  - 🟢 Good
  - 🔵 Moderate
  - 🔴 Harmful
- Data is sent to Blynk Cloud for real-time monitoring via mobile app.

---

## 🔌 Circuit Diagram
![Circuit Diagram](circuit-diagram.jpg)

---

## 🎥 Demo Video
[Watch Project Demo](https://drive.google.com/file/d/1TI3VHRtya2As3mA0z4Za6jyWypq4IFRu/view?usp=sharing)

---

## 🚀 Future Scope
Future improvements include integrating a GPS Neo module for location-based monitoring and an OLED display for real-time on-device data visualization.

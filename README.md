### **README.md**  

# 🔥 AI-Powered Smart Fire Alarm System  

## **Overview**  
This project is an **AI-enhanced Smart Fire Alarm System** that uses **Machine Learning (ML) for fire detection** and **real-time alerts**. It utilizes **sensor data (flame, gas, and temperature)** to predict fire risks and sends alerts via **SMS (GSM Module) and LoRa (Long-Range RF Communication)**.  

🚀 **Key Features:**  
- **AI-Based Fire Prediction:** Reduces false alarms by analyzing sensor patterns using ML.  
- **Multi-Sensor Integration:** Uses **Flame, Gas (MQ-2/MQ-135), and Temperature (DHT11/DHT22) sensors**.  
- **Instant Alerts:** Sends **SMS notifications** via the SIM800L module.  
- **Remote Communication:** Uses **LoRa SX1278** for long-range monitoring.  
- **Edge AI Processing:** Runs a **TinyML Model** on an **ESP32** or **Arduino Mega**.  

---

## **📌 Hardware Requirements**  
- **ESP32 / Arduino Mega** (for AI & connectivity)  
- **Flame Sensor (IR-Based)**  
- **Gas Sensor (MQ-2 or MQ-135)**  
- **DHT11/DHT22 Temperature Sensor**  
- **SIM800L GSM Module** (for SMS alerts)  
- **LoRa SX1278 Module** (for long-range data transmission)  
- **Power Supply (5V/12V depending on modules)**  
- **Jump Wires & Breadboard**  

---

## **🛠️ Software Requirements**  
- **Arduino IDE** (for programming)  
- **Python (for ML Model Training)**
  - TensorFlow  
  - Pandas  
  - NumPy  
  - Scikit-learn  
- **TensorFlow Lite for Microcontrollers** (TinyML deployment)  
- **Libraries Required (for Arduino)**  
  - `DHT.h` (Temperature sensor)  
  - `SoftwareSerial.h` (For GSM and LoRa communication)  
  - `TensorFlowLite_ESP32.h` (ML Model Deployment)  

---

## **📂 Project Structure**
```
/AI_Fire_alarm/
│── model_training/         # ML model training scripts
│   ├── fire_detection_train.py  # Train AI model
│   ├── convert_to_tflite.py     # Convert model to TensorFlow Lite
│   ├── fire_sensor_data.csv     # Sample dataset
│
│── embedded_system_code/           # Embedded system code
│   ├── ai_fire_alarm.ino       # AI-integrated fire alarm code
│   ├── fire_detection_model.h  # AI model header file (converted from TFLite)
│
│── README.md               # Documentation
│── fire_detection_model.tflite  # Trained AI model
```

---

## **🔧 Setup & Deployment**  

### **1️⃣ Train the AI Model**  
Run the Python script to train a fire detection model based on sensor data:
```bash
python model_training/fire_detection_train.py
```
Convert the trained model into a **TensorFlow Lite model**:
```bash
python model_training/convert_to_tflite.py
```
Save the **fire_detection_model.tflite** for deployment.

---

### **2️⃣ Deploy the AI Model on ESP32/Arduino**  
1. Convert `.tflite` model to a **C header file** using:  
```bash
xxd -i fire_detection_model.tflite > fire_detection_model.h
```
2. Copy **fire_detection_model.h** into the **Arduino project folder**.  
3. Upload the **ai_fire_alarm.ino** sketch to the **ESP32/Arduino Mega**.  

---

### **3️⃣ Hardware Wiring Guide**  
| Component         | Arduino/ESP32 Pin |
|------------------|----------------|
| Flame Sensor    | D2             |
| Gas Sensor (MQ-2/MQ-135) | A0             |
| Temperature Sensor (DHT11/DHT22) | D4             |
| GSM Module (SIM800L) | TX - D10, RX - D11 |
| LoRa SX1278     | TX - D5, RX - D6 |

---

## **📡 How It Works**
✅ Sensors collect real-time **flame, gas, and temperature** data.  
✅ The **AI model** runs inference on ESP32 to predict fire risks.  
✅ If risk is detected (AI score > 80%):  
   - 🚨 **Sends SMS alerts** via the GSM module.  
   - 📡 **Transmits data via LoRa** for remote monitoring.  
✅ Fire risk alerts are displayed on **serial monitor**.  

---

## **🚀 Future Enhancements**
✔ **Cloud Integration** (Send alerts to Firebase/AWS IoT)  
✔ **Mobile App Notification** (Using MQTT)  
✔ **AI Model Optimization** (For real-time learning on the device)  

---

## **📜 License**
This project is open-source and free to use for research and development purposes.  

---

## **📞 Contact**
For inquiries, feel free to reach out:  
📧 **Email:** evansbsansolis@gmail.com  
 

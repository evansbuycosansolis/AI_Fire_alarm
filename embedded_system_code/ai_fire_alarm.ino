#include <TensorFlowLite_ESP32.h>
#include <SoftwareSerial.h>
#include <DHT.h>

// TensorFlow Lite Model (fire_detection_model.tflite)
#include "fire_detection_model.h"

// Define pins
#define FLAME_SENSOR_PIN 2
#define GAS_SENSOR_PIN A0
#define DHTPIN 4
#define DHTTYPE DHT11

#define GSM_TX 10
#define GSM_RX 11
#define LORA_TX 5
#define LORA_RX 6

SoftwareSerial gsm(GSM_TX, GSM_RX);
SoftwareSerial lora(LORA_TX, LORA_RX);
DHT dht(DHTPIN, DHTTYPE);

// AI Model Input & Output
float input_data[3];
float output_data[1];
tflite::MicroInterpreter* interpreter;

void setup() {
    Serial.begin(115200);
    gsm.begin(9600);
    lora.begin(9600);
    dht.begin();

    pinMode(FLAME_SENSOR_PIN, INPUT);
    pinMode(GAS_SENSOR_PIN, INPUT);

    Serial.println("Smart Fire AI System Initialized...");

    // Load TensorFlow Lite Model
    tflite::InitializeTensorFlowLite();
    interpreter = tflite::LoadModel(fire_detection_model_tflite, sizeof(fire_detection_model_tflite));

    Serial.println("ML Model Loaded.");
}

void loop() {
    int flameStatus = digitalRead(FLAME_SENSOR_PIN);
    int gasLevel = analogRead(GAS_SENSOR_PIN);
    float temperature = dht.readTemperature();

    Serial.print("Flame: "); Serial.print(flameStatus);
    Serial.print(" Gas: "); Serial.print(gasLevel);
    Serial.print(" Temp: "); Serial.println(temperature);

    // Prepare input for AI Model
    input_data[0] = (float)flameStatus;
    input_data[1] = (float)gasLevel;
    input_data[2] = (float)temperature;

    // Run inference
    interpreter->input_tensor->data.f = input_data;
    interpreter->Invoke();
    float prediction = interpreter->output_tensor->data.f;

    Serial.print("Fire Risk Score: "); Serial.println(prediction);

    if (prediction > 0.8) {  // AI Confidence > 80%
        sendAlert(flameStatus, gasLevel, temperature);
        sendLoRa(flameStatus, gasLevel, temperature);
    }

    delay(5000);
}

void sendAlert(int flame, int gas, float temp) {
    Serial.println("Sending AI-Powered SMS Alert...");
    gsm.println("AT+CMGF=1");
    delay(1000);
    gsm.println("AT+CMGS=\"+11234567890\"");
    delay(1000);
    gsm.print("FIRE ALERT (AI-Powered)\nFlame: ");
    gsm.print(flame == LOW ? "Detected" : "None");
    gsm.print("\nGas Level: ");
    gsm.print(gas);
    gsm.print("\nTemperature: ");
    gsm.print(temp);
    gsm.println("�C");
    delay(1000);
    gsm.write(26);
    delay(5000);
}

void sendLoRa(int flame, int gas, float temp) {
    Serial.println("Sending AI-Powered LoRa Data...");
    lora.print("FIRE ALERT (AI)|Flame:");
    lora.print(flame == LOW ? "Detected" : "None");
    lora.print("|Gas:");
    lora.print(gas);
    lora.print("|Temp:");
    lora.print(temp);
    lora.println("C");
}

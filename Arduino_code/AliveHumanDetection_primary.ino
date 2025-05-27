#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "MAX30105.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#define TRIG_PIN 5       // Ultrasonic Trigger Pin
#define ECHO_PIN 18      // Ultrasonic Echo Pin
#define PIR_SENSOR 4     // PIR Motion Sensor Pin
#define MQ2_SENSOR 34    // MQ-2 Gas Sensor (Analog)
#define BAUD_RATE 115200 // Serial Monitor Speed

// Sensor & MQTT Variables
unsigned long lastSentTime = 0;  
const long publishInterval = 3000;  // Publish every 3 seconds

// MAX30102 Heart Rate Sensor
MAX30105 particleSensor;

// WiFi & MQTT Credentials
const char* ssid = "YOUR_WiFi_NAME";
const char* password = "Wi-Fi Network Password";
const char* mqtt_server = "testId.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "ESP_valid";
const char* mqtt_password = "***********";

// MQTT Client Setup
WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(BAUD_RATE);  // Start Serial for Monitor & Plotter
  pinMode(PIR_SENSOR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //Heart Sensor STD I2C Dtection
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("Error: MAX30102 Not Found!");
  } else {
    Serial.println("MAX30102 Ready!");
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x0A);
    particleSensor.setPulseAmplitudeIR(0x0A);
    particleSensor.enableDIETEMPRDY(); 
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Connect to MQTT
  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  connectMQTT();
}
//MQTT protocol setup through HiveMQ
void connectMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to HiveMQ...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Connected to HiveMQ!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying...");
      delay(2000);
    }
  }
}

//HC-SR05 Pulse emit
float getUltrasonicDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.0343 / 2; //ECHO pulse
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }

  unsigned long currentMillis = millis();
  if (currentMillis - lastSentTime >= publishInterval) {
    lastSentTime = currentMillis;

    // Read Sensor Data
    int pir_value = digitalRead(PIR_SENSOR);
    float ultrasonic_distance = getUltrasonicDistance();
    int gas_level = analogRead(MQ2_SENSOR);
    long irValue = particleSensor.getIR();
    long redValue = particleSensor.getRed();
    int bpm = estimateBPM(irValue);

    // Print Data to Serial Monitor
    Serial.print("PIR Motion: ");
    Serial.println(pir_value ? "Detected" : "No Movement");
    Serial.print("Distance (cm): ");
    Serial.println(ultrasonic_distance);
    Serial.print("MQ-2 Gas Level: ");
    Serial.println(gas_level);
    Serial.print("IR: ");
    Serial.print(irValue);
    Serial.print(", Red: ");
    Serial.print(redValue);
    Serial.print(", BPM: ");
    Serial.println(bpm);
    Serial.println("---------------------");
    /*
    // ✅ **Print Data in Serial Plotter Format**
    Serial.print("PIR="); Serial.print(pir_value); Serial.print("  ");
    Serial.print("Distance="); Serial.print(ultrasonic_distance); Serial.print("  ");
    Serial.print("Gas="); Serial.print(gas_level); Serial.print("  ");
    Serial.print("BPM="); Serial.println(bpm);  // **New Line Ensures Correct Plotting!**
    */

    // Format JSON & Publish to MQTT
    StaticJsonDocument<256> doc;
    doc["pir"] = pir_value;
    doc["distance"] = ultrasonic_distance;
    doc["gas"] = gas_level;
    doc["bpm"] = bpm;

    char payload[256];
    serializeJson(doc, payload);
    client.publish("esp32/sensors", payload);
  }

  client.loop();  // Keep MQTT connection alive
}

// **BPM Estimation Function**
int estimateBPM(long irValue) {
  static long lastBeatTime = 0;
  static int beatCount = 0;
  static int bpm=0;
  long currentTime = millis();

  if (irValue < 50000) {
        Serial.println("No Finger Detected on MAX30102!");
        return 0;  // No valid BPM if no finger detected
    }

  if (irValue > 60000) {
     if (beatCount == 0) {
            lastBeatTime = currentTime;
        }
    beatCount++;
    if (beatCount >= 2) {
      bpm = 60000 / (currentTime - lastBeatTime);
      lastBeatTime = currentTime;
      beatCount = 0;
      return bpm;
    }
  }
  return bpm;
}

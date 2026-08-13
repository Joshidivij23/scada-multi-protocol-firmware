#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "ssidhere";
const char* password = "passwordhere";

// MQTT broker details
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_username = "your_MQTT_USERNAME";
const char* mqtt_password = "your_MQTT_PASSWORD";

// MQTT topic to subscribe and publish
const char* topic = "your_MQTT_TOPIC";

// LED pin
const int ledPin = 2;

// WiFi client and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(ledPin, OUTPUT);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT broker
  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(topic);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  client.loop();
}

// Callback function to handle MQTT messages
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message received: ");
  Serial.println((char*)message);
  
  if (strcmp((char*)message, "ON") == 0) {
    digitalWrite(ledPin, HIGH);
    client.publish(topic, "LED turned on");
  } else if (strcmp((char*)message, "OFF") == 0) {
    digitalWrite(ledPin, LOW);
    client.publish(topic, "LED turned off");
  }
}

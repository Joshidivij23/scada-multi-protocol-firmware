#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

//  network credentials
const char* ssid = "ssidhere";
const char* password = "passwordhere";

//mqtt broker details
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_user = "hivemq.webclient.1679551764646";
const char* mqtt_password = ".X9DO1#puR08Kg>akS%r";

//mqtt topic to publish data to
const char* topic = "temp";

//pin to which the dht sensor is connected
#define DHTPIN 4

//type of sensor
#define DHTTYPE DHT11   


DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  //WiFi connection 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
//returning status for WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  //looping this process until connected to the mqtt broker
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

// reading sensor data
  float h = dht.readHumidity();
  float t = dht.readTemperature();

// checking for error in reading
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // publishing the data to the mqtt broker
  char payload[32];
  snprintf(payload, sizeof(payload), "{\"temperature\":%.2f,\"humidity\":%.2f}", t, h);
  client.publish(topic, payload);

  delay(2000);
}

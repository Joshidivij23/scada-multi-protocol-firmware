#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU9250.h>

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
float temperature = 0.0;
long previousMillis = 0;
const long interval = 1000; // Send temperature reading every second

Adafruit_MPU9250 mpu;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);

  // Start MPU9250
  Wire.begin();
  mpu.begin();
  mpu.setAccelerometerRange(MPU9250_RANGE_2_G);
  mpu.setGyroRange(MPU9250_RANGE_250_DPS);

  // Create BLE server
  BLEDevice::init("MyServer");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create BLE service
  BLEService *pService = pServer->createService(BLEUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b"));

  // Create BLE characteristic
  pCharacteristic = pService->createCharacteristic(BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic->addDescriptor(new BLE2902());

  // Start BLE service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void loop() {
  // Read temperature from MPU9250
  sensors_event_t event;
  mpu.getEvent(&event);
  temperature = ((event.temperature - 21.0) * 1.8) + 32.0;

  // Send temperature reading if device is connected
  if (deviceConnected) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      char buffer[10];
      dtostrf(temperature, 4, 2, buffer);
      pCharacteristic->setValue(buffer);
      pCharacteristic->notify();
    }
  }

  delay(100);
}

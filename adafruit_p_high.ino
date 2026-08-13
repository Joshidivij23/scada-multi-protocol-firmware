#include <Wire.h>

const int pressurePin = 2; // Replace with the pressure sensor pin
const int i2cAddress = 8;

void setup() {
  pinMode(pressurePin, INPUT);
  Wire.begin(); // Start I2C as master
}

void loop() {
  int pressureData = digitalRead(pressurePin);
  if (pressureData == HIGH) {
    Wire.beginTransmission(i2cAddress);
    Wire.write("pressure high");
    Wire.endTransmission();
  }

  delay(100); // Wait for 100ms before reading the response

  Wire.requestFrom(i2cAddress, 1);
  if (Wire.available()) {
    String response = Wire.readString();
    // Process the response from the ESP32 (e.g., display it on an LCD)
  }

  delay(1000); // Wait for 1 second before the next iteration
}

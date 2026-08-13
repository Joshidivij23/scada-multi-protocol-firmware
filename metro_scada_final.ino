const int pressurePin = 2; // Replace with the pressure sensor pin
const int dataPin = 3; // Replace with the data pin connected to the ESP32

void setup() {
  pinMode(pressurePin, INPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600); // Start serial communication
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    digitalWrite(dataPin, HIGH);
    delay(10); // Wait for 10ms to ensure the ESP32 receives the signal
    digitalWrite(dataPin, LOW);
  }

  int pressureData = digitalRead(pressurePin);
  if (pressureData == HIGH) {
    Serial.println("pressure high");
  }

  delay(1000); // Wait for 1 second before the next iteration
}

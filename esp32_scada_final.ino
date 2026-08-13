const int ledPin = 2; // Replace with the LED pin
const int dataPin = 3; // Replace with the data pin connected to the Adafruit Grand Central Metro

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(dataPin, INPUT);
  Serial.begin(9600); // Start serial communication
}

void loop() {
  if (digitalRead(dataPin) == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(500); // Wait for 500ms before turning off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("pressure high");
  }

  delay(1000); // Wait for 1 second before the next iteration
}

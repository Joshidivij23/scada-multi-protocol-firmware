// CORRECTED: these four signal constants were referenced below but never
// defined anywhere in the original file — compile error as written.
// Values are placeholders; adjust to match your actual signal encoding.
#define LOW_BATTERY_SIGNAL 1
#define FLOW_LINE_PRESSURE_HIGH_SIGNAL 2
#define FLOW_LINE_PRESSURE_LOW_SIGNAL 3
#define INPUT_SIGNAL_FROM_SCADA_NETWORK 4

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  //Wait for sensor data from Adafruit metro m4 grand central
  while(Serial.available() == 0);
  
  //Read the sensor data sent by Adafruit metro m4 grand central
  int sensor_data = Serial.read();
  
  //Blink the LED based on the sensor data
  if(sensor_data == LOW_BATTERY_SIGNAL){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }else if(sensor_data == FLOW_LINE_PRESSURE_HIGH_SIGNAL){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }else if(sensor_data == FLOW_LINE_PRESSURE_LOW_SIGNAL){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }else if(sensor_data == INPUT_SIGNAL_FROM_SCADA_NETWORK){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
  
  //Send the sensor data back to Adafruit metro m4 grand central
  Serial.write(sensor_data);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Read sensor data and store it in a variable
  int sensor_data = read_sensor_data();
  
  //Send sensor data to ESP32 dev module
  Serial.write(sensor_data);
  
  //Wait for ESP32 dev module to send the data back
  while(Serial.available() == 0);
  
  //Read the data sent by ESP32 dev module
  int data_received = Serial.read();
  
  //Compare the data sent and received
  if(sensor_data == data_received){
    //Sensor data sent and received successfully
    //Do nothing
  }else{
    //Sensor data sent and received does not match
    //Handle the error
  }
  
  //Delay before sending the next data
  delay(1000);
}

int read_sensor_data(){
  //Read the sensor data and return it
  //Replace this with your code to read sensor data from different sensors
  return 1;
}

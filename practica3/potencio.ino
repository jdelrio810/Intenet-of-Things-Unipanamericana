#include <SoftwareSerial.h>


int sensorPin = A0;    
float sensorValue = 0;  


SoftwareSerial ser(2,3);//Rx Tx

void setup() {
  
  pinMode(sensorPin,INPUT);
  Serial.begin(115200);
  ser.begin(115200);
}

void loop() {
  
  sensorValue = (3.3*analogRead(sensorPin))/1023;
  ser.println(sensorValue);
  Serial.println(sensorValue);
  delay(1000);
}

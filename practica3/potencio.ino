#include <SoftwareSerial.h>


int sensorPin = A0;    
float sensorValue = 0;  


SoftwareSerial ser(2,3);//Rx Tx

void setup() {
  
  pinMode(sensorPin,INPUT);
  
  Serial.begin(9600);

  ser.begin(9600);


}

void loop() {
  
  sensorValue = (5.0*analogRead(sensorPin))/1023;
  
  ser.println(sensorValue);
  
  Serial.println(sensorValue);
  
  delay(1000);


}

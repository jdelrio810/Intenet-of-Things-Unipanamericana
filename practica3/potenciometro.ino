void setup() {
  //Iniciamos la Comunicacion Serial a 9600 baudios
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(A0); //Lectura del ADC 
  float voltage = sensorValue * (3.3 / 1023); //escalamos a voltaje 

  
 //Enviamos por el puerto serie
  Serial.print("ADC= ");
  Serial.print(sensorValue);
  Serial.print("  Voltaje= ");
  Serial.println(voltage); 
  
  delay(1000);  
}

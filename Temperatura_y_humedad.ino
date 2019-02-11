#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <SPI.h>
#include "DHT.h" //cargamos la librería DHT
#include <Adafruit_Sensor.h>
#define DHTPIN 2 //Seleccionamos el pin en el que se conectará el sensor
#define DHTTYPE DHT22 //Se selecciona el DHT22(hay otros DHT)

DHT dht(DHTPIN, DHTTYPE); //Se inicia una variable que será usada por Arduino para comunicarse con el sensor   
    
    char ssid[] = "XXXXXXXX";   
    char pass[] = "XXXXXXXX";   
    int status = WL_IDLE_STATUS;
    WiFiClient  client; 
    
unsigned long myChannelNumber = "Chanel ID"; 
const char * myWriteAPIKey = "APIKEY";
int sensor = 0;

void setup() {  
Serial.begin(115200);
dht.begin(); 
WiFi.begin(ssid, pass);
ThingSpeak.begin(client);

while( WiFi.status() != WL_CONNECTED){
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("Wi-Fi connectado");

}
void loop() {
float t = dht.readTemperature(); 
float h = dht.readHumidity();

ThingSpeak.writeField(myChannelNumber,1,t, myWriteAPIKey);
delay(5000)
ThingSpeak.writeField(myChannelNumber,2,h, myWriteAPIKey);
delay (2000);

}

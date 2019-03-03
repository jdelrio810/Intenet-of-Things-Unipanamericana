#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
//#include <WiFi.h>
#include "DHT.h" 
#include <Adafruit_Sensor.h>
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 

char ssid[] = "XXXXXXXXX";
char pass[] = "XXXXXXXXX";
int status = WL_IDLE_STATUS;
WiFiClient  client;

unsigned long myChannelNumber = XXXXXXXX;
const char * myWriteAPIKey = "APIKEY";
void setup() {
WiFi.begin(ssid, pass); 
ThingSpeak.begin(client);
dht.begin();

Serial.begin(115200);
Serial.println();
Serial.print("Conectando a ");
Serial.print(ssid);

while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}

Serial.println();
Serial.println("Conectado a WiFi");
Serial.print("Dirección IP: ");
Serial.println(WiFi.localIP());

}

void loop() {
delay(2000);

float h = dht.readHumidity();
float t = dht.readTemperature();

Serial.print("Humedad: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperatura: ");
Serial.print(t);
Serial.println(" *C\t ");

// Carga los valores a enviar
ThingSpeak.setField(1, t);

// Escribe todos los campos a la vez.
ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

Serial.println("¡Datos enviados a ThingSpeak!");

// Añadimos un retraso para limtitar el número de escrituras en Thinhspeak

delay (1000);
}

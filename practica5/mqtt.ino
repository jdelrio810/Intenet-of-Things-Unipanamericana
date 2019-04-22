#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h" 
#include <Adafruit_Sensor.h>
#define DHTPIN 5 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE); 

//-------------------VARIABLES GLOBALES--------------------------
int contconexion = 0;

const char *ssid = "***********";
const char *password = "*******";
char   SERVER[50]   = "75.101.131.202"; //"m11.cloudmqtt.com"
int    SERVERPORT   = 10722;
String USERNAME = "******";   
char   PASSWORD[50] = "******";     

unsigned long previousMillis = 0;

char charPulsador [15];
String strPulsador;
String strPulsadorUltimo;

char PLACA[50];

char valueStr[15];
String strtemp = "";
char TEMPERATURA[50];
char PULSADOR[50];
char SALIDADIGITAL[50];
char SALIDAANALOGICA[50];


//-------------------------------------------------------------------------
WiFiClient espClient;
PubSubClient client(espClient);

//------------------------CALLBACK-----------------------------
void callback(char* topic, byte* payload, unsigned int length) {

  char PAYLOAD[5] = "    ";
  
  Serial.print("Mensaje Recibido: [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    PAYLOAD[i] = (char)payload[i];
  }
  Serial.println(PAYLOAD);

  if (String(topic) ==  String(SALIDADIGITAL)) {
    if (payload[1] == 'N'){
     digitalWrite(14, HIGH);
    }
    if (payload[1] == 'F'){
      digitalWrite(14, LOW);
    }
  }

  if (String(topic) ==  String(SALIDAANALOGICA)) {
    analogWrite(13, String(PAYLOAD).toInt());
  }
}

//------------------------RECONNECT-----------------------------
void reconnect() {
  uint8_t retries = 3;
  // Loop hasta que estamos conectados
  while (!client.connected()) {
    Serial.print("Intentando conexion MQTT...");
    // Crea un ID de cliente al azar
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    USERNAME.toCharArray(PLACA, 50);
    if (client.connect("", PLACA, PASSWORD)) {
      Serial.println("conectado");
      client.subscribe(SALIDADIGITAL);
      client.subscribe(SALIDAANALOGICA);
    } else {
      Serial.print("fallo, rc=");
      Serial.print(client.state());
      Serial.println(" intenta nuevamente en 5 segundos");
      // espera 5 segundos antes de reintentar
      delay(5000);
    }
    retries--;
    if (retries == 0) {
      // esperar a que el WDT lo reinicie
      while (1);
    }
  }
}

//------------------------SETUP-----------------------------
void setup() {
  dht.begin();
  //prepara GPI13 y 12 como salidas 
  pinMode(13, OUTPUT); // D7 salida analógica
  analogWrite(13, 0); // analogWrite(pin, value);
  pinMode(14, OUTPUT); // D6 salida digital
  digitalWrite(14, LOW);

  // Entradas
  pinMode(0, INPUT); // D5

  // Inicia Serial
  Serial.begin(115200);
  Serial.println("");

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      /*//para usar con ip fija
      IPAddress ip(192,168,0,156); 
      IPAddress gateway(192,168,0,1); 
      IPAddress subnet(255,255,255,0); 
      WiFi.config(ip, gateway, subnet); */
      
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
  
  client.setServer(SERVER, SERVERPORT);
  client.setCallback(callback);

  String temperatura = "/" + USERNAME + "/" + "temperatura"; 
  temperatura.toCharArray(TEMPERATURA, 50);
  String pulsador = "/" + USERNAME + "/" + "pulsador"; 
  pulsador.toCharArray(PULSADOR, 50);
  String salidaDigital = "/" + USERNAME + "/" + "salidaDigital"; 
  salidaDigital.toCharArray(SALIDADIGITAL, 50);
  String salidaAnalogica = "/" + USERNAME + "/" + "salidaAnalogica"; 
  salidaAnalogica.toCharArray(SALIDAANALOGICA, 50);
  
}

//--------------------------LOOP--------------------------------
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long currentMillis = millis();
    
  if (currentMillis - previousMillis >= 10000) { //envia la temperatura cada 10 segundos
    previousMillis = currentMillis;
    
    float temp = dht.readTemperature();
    strtemp = String(temp, 1); //1 decimal
    strtemp.toCharArray(valueStr, 15);
    Serial.println("Enviando: [" +  String(TEMPERATURA) + "] " + strtemp);
    client.publish(TEMPERATURA, valueStr);
  }
  
  if (digitalRead(0) == 0) {
    strPulsador = "presionado";
  } else {
    strPulsador = "NO presionado";
  }

  if (strPulsador != strPulsadorUltimo) { //envia el estado del pulsador solamente cuando cambia.
    strPulsadorUltimo = strPulsador;
    strPulsador.toCharArray(valueStr, 15);
    Serial.println("Enviando: [" +  String(PULSADOR) + "] " + strPulsador);
    client.publish(PULSADOR, valueStr);
  }
}

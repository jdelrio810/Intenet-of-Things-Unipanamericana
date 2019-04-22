#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "52.70.203.194" // io.adafruit.com
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "********"
#define AIO_KEY         "**********************"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish temperatura = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperatura");
Adafruit_MQTT_Publish pulsador = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pulsador");


// Setup a feed called 'onoff' for subscribing to changes to the button
Adafruit_MQTT_Subscribe salidaDigital = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/salidaDigital", MQTT_QOS_1);
Adafruit_MQTT_Subscribe salidaAnalogica = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/salidaAnalogica", MQTT_QOS_1);

/*************************** Sketch Code ************************************/

void digitalCallback(char *data, uint16_t len) {
  Serial.print("Hey we're in a onoff callback, the button value is: ");
  Serial.println(data);

     String message = String(data);
      message.trim();
      if (message == "ON") {digitalWrite(12, HIGH);}
      if (message == "OFF") {digitalWrite(12, LOW);} 
}

void analogicaCallback(char *data, uint16_t len) {
  Serial.print("Hey we're in a onoff callback, the button value is: ");
  Serial.println(data);

     String message = String(data);
     message.trim();
     analogWrite(13, message.toInt());
}


//-------------------VARIABLES GLOBALES--------------------------
int contconexion = 0;

const char *ssid = "----";
const char *password = "----";

unsigned long previousMillis = 0;

char charPulsador [15];
String strPulsador;
String strPulsadorUltimo;

//-------------------------------------------------------------------------

void setup() {

  //prepara GPI13 y 12 como salidas 
  pinMode(13, OUTPUT); // D7 salida analógica
  analogWrite(13, 0); // analogWrite(pin, value);
  pinMode(12, OUTPUT); // D6 salida digital
  digitalWrite(12, LOW);

  // Entradas
  pinMode(14, INPUT); // D5

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
      //para usar con ip fija
      IPAddress ip(192,168,1,156); 
      IPAddress gateway(192,168,1,1); 
      IPAddress subnet(255,255,255,0); 
      WiFi.config(ip, gateway, subnet); 
      
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }

  salidaDigital.setCallback(digitalCallback);
  salidaAnalogica.setCallback(analogicaCallback);
  mqtt.subscribe(&salidaDigital);
  mqtt.subscribe(&salidaAnalogica);
  
}

//--------------------------LOOP--------------------------------
void loop() {

  MQTT_connect();

  unsigned long currentMillis = millis();
    
  if (currentMillis - previousMillis >= 2000) { //envia la temperatura cada 2 segundos
    previousMillis = currentMillis;
    int analog = analogRead(17);
    float temp = analog*0.322265625;
    Serial.print(F("\nSending temperatura val "));
    Serial.print(temp);
    Serial.print("...");
    if (! temperatura.publish(temp)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  }

  if (digitalRead(14) == 0) {
    strPulsador = "presionado";
  } else {
    strPulsador = "NO presionado";
  }

  if (strPulsador != strPulsadorUltimo) { //envia el estado del pulsador solamente cuando cambia.
    strPulsadorUltimo = strPulsador;
    strPulsador.toCharArray(charPulsador, 15);
    Serial.print(F("\nSending pulsador val "));
    Serial.print(strPulsador);
    Serial.print("...");
    if (! pulsador.publish(charPulsador)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
    delay(1000);
  }

  // this is our 'wait for incoming subscription packets and callback em' busy subloop
  // try to spend your time here:
  mqtt.processPackets(500);
  
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  
  // if(! mqtt.ping()) {
  //   mqtt.disconnect();
  // }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

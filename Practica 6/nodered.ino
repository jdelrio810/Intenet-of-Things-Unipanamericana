
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 

// Configuración WiFi
char* ssid = "SSID-WIFI"; // SSID de la WiFi
char* pass = "PASS-WIFI"; // Constraseña de la WiFi
WiFiClient  clienteWifi;
 
// Configuración MQTT
PubSubClient clientMqtt(clienteWifi);
const char* servidorMqtt = "IP-BROKER-MQTT";
const char* topicAlarma = "/casa/puerta/alarma";
 
void setup() {
 

  Serial.begin(115200);
  delay(500);
  Serial.println("[INI]Comienzo del programa sistema alarma con ESP8266");
 
  // Señal arrancando
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);

 
  // Conexión con la red WiFi
  int intentosWiFi = 0;
  WiFi.begin(ssid, pass);
 
    Serial.print("[WIFI]Intentando conectar a: ");
    Serial.println(ssid);

 
  while (WiFi.status() != WL_CONNECTED || intentosWiFi > 30) {

    Serial.print(".");

 
    // Esperamos
    delay(500);
 
    intentosWiFi++;
  }
 

    Serial.println(".");

 
  // Si no ha conetado mostramos error
 if (WiFi.status() != WL_CONNECTED)
  {
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }
 

  Serial.println("[WIFI]Conectado a la WiFi");

 
  // Configuración MQTT
  clientMqtt.setServer(servidorMqtt, 1883);

  Serial.println("[MQTT]Conectado al servidor MQTT");

  // Apagado de LED
  digitalWrite(LED_BUILTIN, HIGH);
}
 
void loop()
{
  // Comprobamos conexión con broker MQTT
  if (!clientMqtt.connected()) {
    reconnectMqtt();
  }
  clientMqtt.loop();
 
    // Enviamos mensaje
    clientMqtt.publish(topicAlarma, "1");
 

    Serial.println("[MQTT]Publicando mensaje alarma: Puerta abierta");
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);

  }
}
 

void reconnectMqtt() {
  // Repetimos hasta conectar
  while (!clientMqtt.connected()) {

    Serial.println("[MQTT]Esperando conexión con MQTT...");

    // Intentamos conectar
    if (clientMqtt.connect("ALARMA NODEMCU")) {

      Serial.println("[MQTT]Conectado");

    } else {

      Serial.print("[MQTT]Fallo, rc=");
      Serial.print(clientMqtt.state());
      Serial.println(" se intentará o travez tras 5 segundos");
      
      // Esperamos 5 segundos
      delay(5000);
    }
  }
}

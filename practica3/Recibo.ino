int led = 5;//pin D1

void setup () {
      Serial.begin(115200); //Inicializo el puerto serial a 115200 baudios
      pinMode( led , OUTPUT);
}
void loop () {
      if (Serial.available()) { //Si está disponible
            char c = Serial.read(); //Guardamos la lectura en una variable char
            if (c == 'N') { //Si es una 'N', enciendo el LED
                  digitalWrite(led,HIGH);
                  Serial.println("'N' pulsada");
            } else if (c == 'D') { //Si es una 'D', apago el LED
                  Serial.println("'D' pressed");
                  digitalWrite(led,LOW);
            } 
      }
}

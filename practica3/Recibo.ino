int led = 5;//pin D1

void setup () {
      Serial.begin(115200); //Inicializo el puerto serial a 9600 baudios
      pinMode( led , OUTPUT);
}
void loop () {
      if (Serial.available()) { //Si está disponible
            char c = Serial.read(); //Guardamos la lectura en una variable char
            if (c == 'N') { 
                  digitalWrite(led,HIGH);
                  
            } else if (c == 'D') { 
                  
                  digitalWrite(led,LOW);
            } 
      }
}

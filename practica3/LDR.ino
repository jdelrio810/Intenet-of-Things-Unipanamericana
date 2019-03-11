// default analog pin to read from:
int analogInputPin = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // if any data on the serial port are available
  // read it and try to update the analogInputPin
  // based on the number that was read on the serial
  if (Serial.available() > 0) {
    analogInputPin = Serial.parseInt();
  }

  // read the analog value:
  int analogInputPinValue = analogRead(analogInputPin);

  // print the results to the serial port:
  // the output should have the following form: INPUTPIN:VALUE
  // followed by a newline character
  Serial.print(analogInputPin);
  Serial.print(":");
  Serial.print(analogInputPinValue);
  Serial.println("");

  // wait 50 milliseconds before the next loop
  delay(50);
}

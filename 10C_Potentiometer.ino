int sensorPin = 0;
int ledPin = 12;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  // Turn on
  digitalWrite(ledPin, HIGH);
  delay(sensorValue);
  // Turn off
  digitalWrite(ledPin, LOW);
  delay(sensorValue);
}


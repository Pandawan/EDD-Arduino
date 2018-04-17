int sensorPin = 0;
int ledPin1 = 11;
int ledPin2 = 10;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(ledPin1, sensorValue);
  analogWrite(ledPin2, 255 - sensorValue);
}


int sensorPin = A0;
int ledPin = 9;
int sensorValue;
int ledValue;
int delayTime = 500;

void setup() {
	pinMode(ledPin, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	sensorValue = analogRead(sensorPin);
	ledValue = map(sensorValue, 0, 1023, 0, 255);

	analogWrite(ledPin, ledValue);
	Serial.print("The sensor value is: ");
	Serial.print(sensorValue);
	Serial.print("	the LED value is: ");
	Serial.println(ledValue);
	delay(delayTime);
}
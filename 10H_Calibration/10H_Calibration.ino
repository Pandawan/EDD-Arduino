int sensorPin = A0;
int ledPin = 9;
int indicatorPin = 13;
int buttonPin = 2;

int minimum = 0;
int maximum = 1023;
int current = 0;
int mapped = 0;

void setup() {
	pinMode(indicatorPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
	pinMode(buttonPin, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	if (digitalRead(buttonPin) == HIGH) {
		minimum = 1023;
		maximum = 0;

		while (digitalRead(buttonPin) == HIGH) {
			Calibrate();
			PrintValue();
		}
	}
	else {
		current = analogRead(sensorPin);
		mapped = map(current, minimum, maximum, 0, 255);
    mapped = constrain(mapped, 0, 255);
		analogWrite(ledPin, mapped);
		PrintValue();
	}
}

void PrintValue() {
	Serial.print("Mimimum: ");
	Serial.print(minimum);

	Serial.print("	Maximum: ");
	Serial.print(maximum);

	Serial.print("	Current: ");
	Serial.print(current);

	Serial.print("	Mapped: ");
	Serial.println(mapped);
}

void Calibrate() {
	digitalWrite(indicatorPin, HIGH);
	current = analogRead(sensorPin);
	if (current > maximum) {
		maximum = current;
	}
	else if (current < minimum) {
		minimum = current;
	}
}

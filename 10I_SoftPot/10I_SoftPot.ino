int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int sensorPin = 0;

int redValue, greenValue, blueValue;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int sensorValue;
  sensorValue = analogRead(sensorPin);
  SetRGB(sensorValue);
}

void SetRGB(int rgbPosition) {
  redValue = constrain(map(rgbPosition, 0, 341, 255, 0), 0, 255) + constrain(map(rgbPosition, 682, 1023, 0, 255), 0, 255);
  greenValue = constrain(map(rgbPosition, 0, 341, 0, 255), 0, 255) + constrain(map(rgbPosition, 341, 682, 0, 255), 0, 255);
  blueValue = constrain(map(rgbPosition, 341, 682, 0, 255), 0, 255) + constrain(map(rgbPosition, 682, 1023, 0, 255), 0, 255);

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}


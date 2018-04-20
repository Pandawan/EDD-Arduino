int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  SetColor(255, 0, 0);
  delay(1000);
  SetColor(0, 200, 0);
  delay(1000);
  SetColor(0, 0, 200);
  delay(1000);
  SetColor(255, 200, 0);
  delay(1000);
  SetColor(255, 0, 200);
  delay(1000);
  SetColor(0, 200, 200);
  delay(1000);
}

void SetColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Turquoise-ish color (custom)
  SetColor(0x64, 0xFF, 0xDA);
  delay(1000);
  // Pink-ish color (custom)
  SetColor(0xFF, 0x40, 0x81);
  delay(1000);
}

void SetColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


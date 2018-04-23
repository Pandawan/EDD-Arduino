int redPin = 9;
int greenPin = 10;
int x = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  for (int x = 0; x < 250; x++) {
    analogWrite(redPin, x);
    analogWrite(greenPin, 255 - x);
    delay(10);
  }

  for (int x = 255; x > 0; x--) {
    analogWrite(redPin, x);
    analogWrite(greenPin, 255 - x);
    delay(10);
  }
}


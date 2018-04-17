int redPin = 9;
int greenPin = 10;
int x = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  while (x < 250) {
    analogWrite(redPin, x);
    analogWrite(greenPin, 250 - x);
    delay(1000);
    x = x + 50;
  }

  while (x > 0) {
    analogWrite(redPin, x);
    analogWrite(greenPin, 250 - x);
    delay(1000);
    x = x - 50;
  }
}


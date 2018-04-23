bool currentButton = LOW;
bool lastButton = LOW;
int ledPin = 13;
int buttonPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  currentButton = digitalRead(buttonPin);
  while(lastButton != currentButton) {
    delay(70);
    lastButton = currentButton;
    currentButton = digitalRead(buttonPin);
  }
  digitalWrite(ledPin, currentButton);
  lastButton = currentButton;
}


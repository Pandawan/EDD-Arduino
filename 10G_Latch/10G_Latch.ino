bool currentButton = LOW;
bool lastButton = LOW;
bool ledOn = false;
int ledPin = 13;
int buttonPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  currentButton = digitalRead(buttonPin);
  if(lastButton == LOW && currentButton == HIGH) {
    ledOn = !ledOn;
  }
  lastButton = currentButton;
  digitalWrite(ledPin, ledOn);
}


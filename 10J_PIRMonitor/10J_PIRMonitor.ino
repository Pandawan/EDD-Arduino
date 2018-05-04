boolean lastState = LOW;
boolean currentState = LOW;
int ledPin = 13;
int pirPin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  Serial.print("initializing sensor");
  for(int x = 0; x < 20; x++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print(" done");
  Serial.print("SENSOR ACTIVE");
}

void loop() {
  currentState = digitalRead(pirPin);
  digitalWrite(ledPin, currentState);

  if(currentState == HIGH && lastState == LOW) {
    Serial.println("---");
    Serial.print("motion detected at ");
    Serial.print(millis()/1000);
    Serial.println(" sec");
    lastState = currentState;
  }
  else if (currentState == LOW && lastState == HIGH) {
    Serial.print("motion ended at ");
    Serial.print(millis()/1000);
    Serial.println(" sec");
    lastState = currentState;
  }
}


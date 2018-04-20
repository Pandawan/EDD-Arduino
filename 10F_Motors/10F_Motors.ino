int motorPin = 9;

void setup() {
  pinMode(motorPin, OUTPUT);
  // Set serial transfer speed to 9600 bits/second
  Serial.begin(9600);
}

void loop() {
  SerialSpeed();
}

void SerialSpeed() {
  int speed;

  Serial.println("Type a speed (0-255) into the box above,");
  Serial.println("then click [send] or press [return]");
  Serial.println("");

  while(true) {
    while(Serial.available() > 0) {
      // Convert serial input into speed
      speed = Serial.parseInt();

      speed = constrain(speed, 0, 255);
      Serial.println("Setting speed to");
      Serial.println(speed);

      // Send new motor speed
      analogWrite(motorPin, speed);
    }
  }
}


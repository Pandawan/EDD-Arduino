int tempPin = 0;
int redPin = 10;
int bluePin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  float voltage, degreesC, degreesF;

  voltage = analogRead(tempPin) * 0.004882814;
  degreesC = (voltage - 0.5)*100;
  degreesF = degreesC*(9.0/5.0) + 32;

  if(degreesF >= 75) {
    SetColor(0x08, 0);
  }
  else {
    SetColor(0, 0x08);
  }

  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print(" deg C: ");
  Serial.print(degreesC);
  Serial.print(" deg F: ");
  Serial.println(degreesF);
  delay(1000);
}

void SetColor(int red, int blue) {
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
}

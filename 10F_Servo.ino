#include <Servo.h>
Servo servo1;

void setup() {
  servo1.attach(9);
}

void loop() {
  for(int pos = 0; pos <= 180; pos++) {
    servo1.write(pos);
    delay(15);
  }
}


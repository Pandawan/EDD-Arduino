#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("I love DE");
}

void loop() {
  lcd.noCursor();
  delay(500);
  lcd.cursor();
  delay(500);
}


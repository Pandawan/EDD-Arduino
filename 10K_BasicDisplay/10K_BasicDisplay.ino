#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Good morning!");
}


void loop() {
  lcd.setCursor(4,1);
  lcd.print("Timer: ");
  lcd.print(millis() / 1000);
}


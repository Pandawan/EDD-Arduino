#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("The entire time");
  lcd.setCursor(0, 1);
  lcd.print("I knew Thanos,");
  delay(1000);
  lcd.clear();
}

void loop() {
  lcd.print("The entire time");
  lcd.setCursor(0, 1);
  lcd.print("I knew Thanos,");
  delay(1750);
  lcd.clear();
  lcd.print("he only ever");
  lcd.setCursor(0, 1);
  lcd.print("had one goal:");
  delay(1750);
  lcd.clear();
  lcd.print("To wipe out half");
  lcd.setCursor(0, 1);
  lcd.print("the universe.");
  delay(1750);
  lcd.clear();
  lcd.print("If he gets");
  lcd.setCursor(0, 1);
  lcd.print("all the");
  delay(1500);
  lcd.clear();
  lcd.print("Infinity Stones...");
  delay(1500);
  lcd.clear();
  lcd.print("he can do it");
  lcd.setCursor(0, 1);
  lcd.print("with the snap");
  delay(1750);
  lcd.clear();
  lcd.print("of his fingers,");
  lcd.setCursor(0, 1);
  lcd.print("just like that.");
  delay(1750);
  lcd.clear();
}


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 20, 4);  // buırdaki i2c adresi 0x27 gibi değrlr olabilir
int sayac=0;
void setup() {
  lcd.init();
   lcd.backlight();
}

void alarm() {
  lcd.setCursor(0, 0);
  lcd.print("Dikkat!");
  lcd.setCursor(0, 1);
  lcd.print("Sistem Arizasi! ");
  lcd.backlight();
  delay(50);
  lcd.noBacklight();
  delay(30);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("SAYI:");
  lcd.setCursor(5,0);
  lcd.print(sayac++);
  
}

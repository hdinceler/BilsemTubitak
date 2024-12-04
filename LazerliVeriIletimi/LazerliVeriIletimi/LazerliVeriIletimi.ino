#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD ekran I2C adresi (genellikle 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int laserPin = 2; // D2 pinine bağlı lazer
const int interval = 1000; // Mesajlar arasındaki süre

void setup() {
  pinMode(laserPin, OUTPUT);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  // Lazer yanar, mesaj gönderildi
  digitalWrite(laserPin, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Mesaj: 1");
  delay(interval);

  // Lazer söner, mesaj bitti
  digitalWrite(laserPin, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Mesaj: 0");
  delay(interval);
}

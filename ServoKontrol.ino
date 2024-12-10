#define motorPin 3
#include <Servo.h>

int sicaklikDegeri = 0;  // Gelen sıcaklık değeri (0-180)
Servo motorSicaklik;

void setup() {
  motorSicaklik.attach(motorPin);  // Servo motorunu pin 3'e bağla
  Serial.begin(9600);  // Seri haberleşmeyi başlat
}

void loop() {
  if (Serial.available() > 0) {
    sicaklikDegeri = Serial.parseInt();  // Seri porttan gelen değeri oku
    
    // Sicaklik değeri 0 ile 180 arasında olmalı
    if (sicaklikDegeri >= 0 && sicaklikDegeri <= 180) {
      // Sicaklik değerini mikro saniyeye dönüştür
      int microseconds = map(sicaklikDegeri, 0, 180, 1000, 2000);

      // Servo motorunu belirtilen mikro saniyeye döndür
      motorSicaklik.writeMicroseconds(microseconds);
      
      // Değeri seri monitöre yazdır
      Serial.print("Servo Pozisyonu (mikro saniye): ");
      Serial.println(microseconds);
    } else {
      Serial.println("Geçersiz değer! Lütfen 0 ile 180 arasında bir değer girin.");
    }
    delay(300);  // Bir süre bekle
  }
}

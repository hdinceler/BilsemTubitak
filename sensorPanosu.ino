#include <Servo.h>
#include <DHT.h>
#define DHTPIN 2         // DHT11 sensörünün bağlı olduğu pin
#define DHTTYPE DHT11    // DHT11 sensörü kullanılıyor
DHT dht(DHTPIN, DHTTYPE);  // DHT nesnesi oluşturuluyor
Servo motor1;
void setup() {
  motor1.attach(3);      // Servo motorun bağlı olduğu pin
  dht.begin();           // DHT11 sensörünü başlat
  Serial.begin(9600);    // Seri haberleşmeyi başlat (debugging için)
}
void loop() {
  // Sıcaklık verisini DHT11 sensöründen al
  float sicaklik = dht.readTemperature(); // Sıcaklık °C cinsinden
  // Sıcaklık okuma başarısız olduysa tekrar dene
  if (isnan(sicaklik)) {
    Serial.println("DHT11 okuma hatası!");
    return;
  }

  // Sıcaklık değerini servo motor açısına dönüştür
  int motorAcisi = map(sicaklik, -30, 50, 0, 180);  // -30°C ile 50°C arasındaki sıcaklık değerini 0° ile 180° arasına dönüştür

  // Motoru belirtilen açıya döndür
  motor1.write(motorAcisi);

  // Sıcaklık değerini ve motor açısını seri monitöre yazdır
  Serial.print("Sicaklik: ");
  Serial.print(sicaklik);
  Serial.print(" °C, Motor Acisi: ");
  Serial.println(motorAcisi);

  delay(2000);  // 2 saniye bekle
}

#include <Servo.h>
#include <DHT.h>

#define DHTPIN 2         // DHT11 sensörünün bağlı olduğu pin
#define DHTTYPE DHT11    // DHT11 sensörü kullanılıyor

#define parlaklikPin A0
int parlaklik =0;

#define gazPin A1
int gazSeviyesi=0;

DHT dht(DHTPIN, DHTTYPE);  // DHT nesnesi oluşturuluyor

Servo motor_sicakik;  // Sıcaklık için servo motor
Servo motor_nem;      // Nem için servo motor

void setup() {
  pinMode(parlaklikPin , INPUT);
  motor_sicakik.attach(3);   // Servo motorun bağlı olduğu pin (sıcaklık için)
  motor_nem.attach(4);       // Servo motorun bağlı olduğu pin (nem için)
  
  dht.begin();               // DHT11 sensörünü başlat
  Serial.begin(9600);        // Seri haberleşmeyi başlat (debugging için)
}

void loop() {
  parlaklik= analogRead(parlaklikPin);

  // Sıcaklık verisini DHT11 sensöründen al
  float sicaklik = dht.readTemperature(); // Sıcaklık °C cinsinden
  // Nem verisini DHT11 sensöründen al
  float nem = dht.readHumidity();  // Nem değeri

  // Sıcaklık ve nem okuma başarısız olduysa tekrar dene
  if (isnan(sicaklik) || isnan(nem)) {
    Serial.println("DHT11 okuma hatası!");
    return;
  }

  // Sıcaklık değerini servo motor açısına dönüştür
  int motorAcisi_sicaklik = map(sicaklik, 10, 40, 0, 180);  // 10°C ile 40°C arasındaki sıcaklık değerini 0° ile 180° arasına dönüştür

  // Nem değerini servo motor açısına dönüştür
  int motorAcisi_nem = map(nem, 0, 100, 0, 180);  // Nem değeri %0 ile %100 arasında ve 0° ile 180° arasına dönüştür

  // Motorları belirtilen açıya döndür
  motor_sicakik.write(motorAcisi_sicaklik);
  motor_nem.write(motorAcisi_nem);

  // Sıcaklık ve nem değerlerini ve motor açılarını seri monitöre yazdır
  Serial.print("Parlaklik:");
  Serial.print(parlaklik);
  Serial.print(",");

  Serial.print("Sicaklik: ");
  Serial.print(sicaklik);
  Serial.print(" °C, Motor Acisi (Sicaklik): ");
  Serial.println(motorAcisi_sicaklik);

  Serial.print("Nem: ");
  Serial.print(nem);
  Serial.print(" %, Motor Acisi (Nem): ");
  Serial.println(motorAcisi_nem);

  delay(2000);  // 2 saniye bekle
}

#include <Adafruit_GFX.h>        // Adafruit GFX kütüphanesi
#include <Adafruit_PCD8544.h>    // Nokia 5110 için PCD8544 kütüphanesi
#include <OneWire.h>             // DS18B20 sensörü için OneWire kütüphanesi
#include <DallasTemperature.h>   // DS18B20 sensörü için DallasTemperature kütüphanesi

// Pin tanımları
#define CLK_PIN  4  // Clock (SCK)
#define DIN_PIN  5  // Data Input (MOSI)
#define DC_PIN   6  // Data/Command
#define CE_PIN   7  // Chip Enable (CS)
#define RST_PIN  8  // Reset
#define BUZZER_PIN 10 
#define ONE_WIRE_BUS 2  // DS18B20 sensörü için veri pini (Dijital Pin 2)

// OneWire ve DallasTemperature nesneleri
OneWire oneWire(ONE_WIRE_BUS); // OneWire objesi
DallasTemperature sensors(&oneWire); // DallasTemperature objesi

// LCD ekran tanımı
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK_PIN, DIN_PIN, DC_PIN, CE_PIN, RST_PIN);

void setup() {
  // LCD ekranı başlat
  display.begin();
  display.setContrast(25);  // Kontrast ayarı (0-100 arasında değişebilir)
  display.clearDisplay();   // Ekranı temizle
    pinMode(BUZZER_PIN, OUTPUT);

  // DS18B20 sensörü başlat
  sensors.begin();
}

void loop() {
  // Sıcaklık sensöründen veriyi oku
  sensors.requestTemperatures(); // Sıcaklık okuma komutu
  float sicaklik = sensors.getTempCByIndex(0); // İlk sensörden sıcaklık değeri (Celsius)

  // Ekranı temizle
  display.clearDisplay();

  // Yazı yazma konumlarını ayarlama
  display.setCursor(0, 0);    
  display.print("Sicaklik:");     // "Sicaklik:" yazısı

  display.setCursor(0, 10);  // Bir alt satıra geç
  display.print(sicaklik);   // Sıcaklık değeri

  display.setCursor(40, 10);  // "C" yazısını sağa yerleştir
  display.print("C");         // Sıcaklık birimi

  // Durumu belirleyin
  String durum;
  if (sicaklik < 35.0) {
    durum = "Cok Dusuk"; // Cok Dusuk
    digitalWrite(BUZZER_PIN, LOW);
  } else if (sicaklik >= 35.0 && sicaklik < 36.5) {
    durum = "Dusuk"; // Dusuk
    digitalWrite(BUZZER_PIN, LOW);
  } else if (sicaklik >= 36.5 && sicaklik < 37.5) {
    durum = "Iyi"; // Iyi
    digitalWrite(BUZZER_PIN, LOW);
  } else if (sicaklik >= 37.5 && sicaklik < 38.5) {
    durum = "Biraz Yuksek"; // Biraz Yuksek
    digitalWrite(BUZZER_PIN, HIGH);
  }else if (sicaklik > 38.5) {
    durum = "Cok Yuksek"; // Cok Yuksek
    digitalWrite(BUZZER_PIN, HIGH);
  }else {
    digitalWrite(BUZZER_PIN, LOW);
  }
  // Durumu ekrana yaz
  display.setCursor(0, 20);  // Yeni satıra geç
  display.print("Durum:");    // "Durum" yazısı

  display.setCursor(0, 30); // Bir sonraki satıra yerleştir
  display.print(durum);      // Durum bilgisi

  // Yazıyı ekrana gönder
  display.display();
  
  // 1 saniye bekle
  delay(100);               
}

#include <WiFi.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>

// SoftAP Ayarları
const char* apSSID = "TANIDIK_ALARMI";  // SoftAP adı
const char* apPassword = "12345678";    // SoftAP şifresi
#define buzzerPin 11
WiFiUDP udp;
const int udpPort = 12345;  // UDP portu
LiquidCrystal_I2C lcd(0x3F, 20, 4);
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistem Basliyor");
  lcd.setCursor(0, 1);
  lcd.print("Ortam Taraniyor...");
  delay(1000);

  Serial.begin(115200);

  // Wi-Fi SoftAP başlat
  WiFi.softAP(apSSID, apPassword);
  Serial.println(WiFi.softAPIP());

  // UDP başlat
  udp.begin(udpPort);
  Serial.println("UDP başlatıldı.");
}

void loop() {
  // Mesaj Al
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    Serial.print("Gelen mesaj: ");
    Serial.println(incomingPacket);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bulundu:");
    lcd.setCursor(0, 1);
    lcd.print(incomingPacket);

    // Yanıt gönder
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.print("AHMET");
    udp.endPacket();
  }else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Kimse Yok!");
  }

  delay(1000);  // 1 saniye bekle
}

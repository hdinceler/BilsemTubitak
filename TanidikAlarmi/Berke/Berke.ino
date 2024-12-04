#include <WiFi.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>

// Wi-Fi Ayarları
const char* ssid = "TANIDIK_ALARMI";  // SoftAP adı
const char* password = "12345678";    // SoftAP şifresi

WiFiUDP udp;
const int udpPort = 12345;  // UDP portu
IPAddress serverIP;         // Sunucu IP'si
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

  // Wi-Fi bağlantısı
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("SoftAP'ye bağlanılıyor...");
  }
  serverIP = WiFi.gatewayIP();
  Serial.println("SoftAP'ye bağlandı!");
  Serial.print("Sunucu IP: ");
  Serial.println(serverIP);

  // UDP başlat
  udp.begin(udpPort);
  Serial.println("UDP başlatıldı.");
}

void loop() {
  // Mesaj Gönder
  udp.beginPacket(serverIP, udpPort);
  udp.print("BERKE");
  udp.endPacket();
  // Serial.println("Mesaj gönderildi: Merhaba, ben ESP32_B!");

  // Yanıt Al
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    // Serial.print("Gelen mesaj: ");
    Serial.println(incomingPacket);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bulundu:");
    lcd.setCursor(0, 1);
    lcd.print(incomingPacket);
  }else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Kimse Yok!");
  }


  delay(1000);  // 1 saniye bekle
}

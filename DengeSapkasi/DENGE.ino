#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

MPU6050 mpu;
#define buzzerPin 11

float aci1 = 10.00;
float aci2 = 20.00;
float aci3 = 30.00;
float aci4 = 40.00;
float aci5 = 50.00;

unsigned long previousMillis = 0;  // Son tetikleme zamanı
bool buzzerState = LOW;            // Buzzer'ın durumu (açık/kapalı)
unsigned long interval = 1000;      // Başlangıç intervali
uint8_t tehlike_x=0;
uint8_t tehlike_y=0;
void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  
  // I2C başlatma
  Wire.begin();
  mpu.initialize();
  
  // Sensörün doğru çalışıp çalışmadığını kontrol et
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 bağlantısı başarısız!");
    while (1);
  }
}
void startBuzzer(unsigned long speed) {
  interval = speed;  // Hızı ayarla
  unsigned long currentMillis = millis();  // Geçen süreyi al
  
  // Eğer belirli bir zaman aralığı geçtiyse, buzzer'ı aç veya kapat
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Son tetikleme zamanını güncelle
    
    // Buzzer'ı aç veya kapat
    buzzerState = !buzzerState;
    digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
  }
}
 

void loop() {
  int16_t ax, ay, az;
  
  // İvmeölçer verilerini oku
  mpu.getAcceleration(&ax, &ay, &az);
  
  // X ve Y eksenindeki ivme verilerini al
  float accelX = ax / 16384.0;  // 16384 = MPU6050'nin ivmeölçer hassasiyeti
  float accelY = ay / 16384.0;  
  float accelZ = az / 16384.0;
  
  // Yatay konum dengesini hesapla (X ve Y eksenlerine göre)
  float angleX = atan(accelX / sqrt(accelY * accelY + accelZ * accelZ)) * 180.0 / PI;
  float angleY = atan(accelY / sqrt(accelX * accelX + accelZ * accelZ)) * 180.0 / PI;
  
  // Sonuçları seri monitörde yazdır
  Serial.print("X: ");
  Serial.print(angleX);
  Serial.print(" , Y: ");
  Serial.print(angleY);
  
  if( abs(angleX) > aci1 && abs(angleX) < aci2 )  tehlike_x=1; 
  if( abs(angleY) > aci1 && abs(angleY) < aci2 )  tehlike_y=1;

  if( abs(angleX) > aci2 && abs(angleX) < aci3)   tehlike_x=2;
  if( abs(angleY) > aci2 && abs(angleY) < aci3)   tehlike_y=2;

  if( abs(angleX) > aci3 && abs(angleX) < aci4)   tehlike_x=3;
  if( abs(angleY) > aci3 && abs(angleY) < aci4)   tehlike_y=3;
  
  if (abs(angleX) > aci4 && abs(angleX) < aci5)   tehlike_x=4;
  if (abs(angleY) > aci4 && abs(angleY) < aci5)   tehlike_y=4;
  
  if( abs(angleX) > aci5 ) tehlike_x=5;
  if( abs(angleY) > aci5 ) tehlike_y=5;
   Serial.print("tehlike_x:");
   Serial.print(tehlike_x);
   Serial.print(", tehlike_y:");
   Serial.print(tehlike_y);
   Serial.print("\n");
   

}

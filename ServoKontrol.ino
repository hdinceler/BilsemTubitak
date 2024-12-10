#define motorPin 3
#include <Servo.h>
int sicaklikDegeri=0;
Servo motorSicaklik;

void setup() {
  motorSicaklik.attach(motorPin);
  Serial.begin(9600);
}

void loop() {
 if( Serial.available()>0 ){
  sicaklikDegeri= Serial.parseInt();
  int mevcutKonum=motorSicaklik.read();
  if(sicaklikDegeri>mevcutKonum){
    for(int i=mevcutKonum; i<=sicaklikDegeri;i++ ){
      motorSicaklik.write(i);
      delay(20);
      Serial.println(i);
    }
  }
 }
}

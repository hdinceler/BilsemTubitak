#include <Servo.h>
#define motorPin 9
Servo bariyer;
unsigned int hedefKonum=0;
unsigned int bariyerKonum=0;
void yavasCalis(unsigned int hedefKonum,unsigned int gecikme);
void setup() {
  pinMode(motorPin,OUTPUT);
  Serial.begin(9600);
  bariyer.attach(motorPin);
  if(bariyerKonum>0) yavasCalis(0,50);
}
void yavasCalis(unsigned int hedefKonum,unsigned int gecikme){
  Serial.println(hedefKonum);
  Serial.println(bariyerKonum);
    if(hedefKonum<=90 && hedefKonum>=0 &&   hedefKonum>=bariyerKonum ){
      for(unsigned int i =bariyerKonum  ; i<= hedefKonum;  i++) {
        bariyer.write(i);
        bariyerKonum=i;
        delay(gecikme);
        Serial.print("hedef:");Serial.print(hedefKonum);Serial.print(", i:");Serial.print(i);Serial.print("\n");
      }
    }
     else if(hedefKonum<=90 && hedefKonum>=0 &&  hedefKonum<bariyerKonum ){
      for(unsigned int i =bariyerKonum  ; i>hedefKonum ;  i--) {
        bariyer.write(i);
        bariyerKonum=i;
        delay(gecikme);
        Serial.print("hedef:");Serial.print(hedefKonum);Serial.print(", i:");Serial.print(i);Serial.print("\n");
      }
    }
    else { return; }
}

void loop(){
 if(Serial.available()>0){
  String gelen =Serial.readString();
 
  hedefKonum=gelen.toInt();
  Serial.print("Hedef konum:"); Serial.print(hedefKonum);Serial.print("\n");
  yavasCalis(hedefKonum, 50);

 }

}

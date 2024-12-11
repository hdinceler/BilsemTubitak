#define ledRed 3
#define ledYellow 4
#define ledGreen 5
#define buzzer 6
#define potansGreen A4
#define potansYellow A5
#define potansRed A6
#define prop A0
unsigned int valProp=0;

unsigned int limitGreen=0;
unsigned int limitYellow=0;
unsigned int limitRed=0;
 
void setup() {
  pinMode(ledRed,OUTPUT);
  pinMode(ledYellow,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(potansGreen,INPUT);
  pinMode(potansYellow,INPUT);
  pinMode(potansRed,INPUT);
  pinMode(prop,INPUT);
  Serial.begin(9600);
}
void openYellow(); void closeAll(); void openRed(); void openGreen(); void noBeep();void beep(unsigned int durationActive,unsigned int durationPassive) ;

void loop() {
  valProp=analogRead(prop);
  
  limitGreen=analogRead(potansGreen);
  limitYellow=analogRead(potansYellow);
  limitRed=analogRead(potansRed);

  Serial.print("Prop:");
  Serial.print(valProp);
  Serial.print(", limitGreen:");
  Serial.print(limitGreen);
  Serial.print(", limitYellow:");
  Serial.print(limitYellow);
  Serial.print(", limitRed:");
  Serial.println(limitRed);

  if(valProp<limitGreen ) openGreen();
  else if (valProp >= limitGreen && valProp < limitYellow) openYellow();
  else if( valProp >limitGreen && valProp >=limitYellow ) openRed();
  else closeAll();
 
}

void beep(unsigned int durationActive,unsigned int durationPassive) {
    digitalWrite(buzzer, HIGH); delay(durationActive);
    digitalWrite(buzzer, LOW); delay(durationPassive);
}
void noBeep(){
    digitalWrite(buzzer, LOW);
}
void openGreen(){
  // noBeep();
  // beep(1,500);
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledRed,LOW);
}
void openYellow(){
  // beep(5,300);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledYellow,HIGH);
  digitalWrite(ledRed,LOW);
}
void openRed(){
  // beep(10,200);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledRed,HIGH);
}
void closeAll(){
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledRed,LOW);
}

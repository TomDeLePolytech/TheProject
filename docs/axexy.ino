#include<SoftwareSerial.h>
#define RX 2
#define TX 3
SoftwareSerial BlueT(RX,TX);



//-- MOTEUR A --
int ENA=9; //Connecté à Arduino pin 9(sortie PWM)
int IN1=4; //Connecté à Arduino pin 4
int IN2=5; //Connecté à Arduino pin 5
//-- MOTEUR B --
int ENB=10; //Connecté à Arduino pin 10(Sortie PWM)
int IN3=6; //Connecté à Arduino pin 6
int IN4=7; //Connecté à Arduino pin 7
int PWM1=0;
int PWM2=0;
char Data;

void setup() {
pinMode(ENA,OUTPUT); // Configurer   //A=moteur gauche
pinMode(ENB,OUTPUT); // les broches    //B=moteur droite
pinMode(IN1,OUTPUT); // comme sortie
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner
digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner

Serial.begin(9600);
BlueT.begin(9600);


// Direction du Moteur A
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
// Direction du Moteur B
// NB: en sens inverse du moteur A
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);


}

void loop() {

if (BlueT.available()){
    Data=BlueT.read();

    if (Data=='Y') { // axe Y
      PWM1=BlueT.parseInt();
      if (PWM1>0){  // vers le haut y+
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        analogWrite(ENA, 2.55*PWM1);
      }
      if (PWM1<0){ // vers le bas y-
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        analogWrite(ENA, -2.55*PWM1);
      }
      

     }

     if (Data=='X') { // axe x
      PWM2=BlueT.parseInt();
      if (PWM2>0){
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        analogWrite(ENB, 2.55*PWM2);
      }
      if (PWM2<0){
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        analogWrite(ENB, -2.55*PWM2);
      }
     }

    }
    }

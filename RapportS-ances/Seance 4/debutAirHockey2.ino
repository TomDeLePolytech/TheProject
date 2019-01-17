#include<SoftwareSerial.h>
#define RX 9
#define TX 8
SoftwareSerial BlueT(RX,TX);

//-- MOTEUR A --
int ENA=10; //Connecté à Arduino pin 9(sortie PWM)
int IN1=3; //Connecté à Arduino pin 4
int IN2=4; //Connecté à Arduino pin 5
//-- MOTEUR B --
int ENB=11; //Connecté à Arduino pin 10(Sortie PWM)
int IN3=5; //Connecté à Arduino pin 6
int IN4=6; //Connecté à Arduino pin 7
int PWM1=0;
int PWM2=0;
char Data;
int test;

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
    Serial.println(Data);

    if (Data=='Y') { // axe Y
      PWM1=BlueT.parseInt();
      Serial.println(PWM1);
      if (PWM1<=50){  // vers le haut y+ si pwm1<50
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        test = -5.1*PWM1+255;
        Serial.println(test);
        analogWrite(ENA, test);
      }
      if (PWM1>50){ // vers le bas y- si pwm1 > 50
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        analogWrite(ENA, 5.1*PWM1-255);
      }

     }

     if (Data=='X') { // axe x
      PWM2=BlueT.parseInt();
      if (PWM2>=50){ // droite si pwm2>50
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        analogWrite(ENB, 5.1*PWM2-255);
      }
      if (PWM2<50){ // gauche si pwm2 <50
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        analogWrite(ENB, -5.1*PWM2+255);
      }
     }

    }
    }

#include "Motor.h"
#include <Arduino.h>

void follow(int ang, int pwm){
	ad = sin(((ang-45)*PI)/180)*pwm;
	bc = cos(((ang-45)*PI)/180)*pwm;

	if(ad>=0){
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    analogWrite(9,ad);
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
    analogWrite(2,ad);
  }

  else{
    ad*(-1);
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    analogWrite(9,ad);
    digitalWrite(5,LOW);
    digitalWrite(4,HIGH);
    analogWrite(2,ad);
  }

  if(bc>=0){
    digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
    analogWrite(8,bc);
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    analogWrite(3,bc);
  }

  else{
    bc*(-1);
    digitalWrite(11,HIGH);
    digitalWrite(10,LOW);
    analogWrite(8,bc);
    digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
    analogWrite(3,bc);
  }
}

void calcularPid(int setPoint){

}
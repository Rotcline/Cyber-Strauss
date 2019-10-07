/*
Developed by:
 _______  __    __  _____	 	 _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|		|   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|		|  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__		|  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|		|_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 
--------------------------
RobotControl.cpp
Updated on 11/03/2018
--------------------------
*/
#include "RobotControl.h"
#include "Arduino.h"

VNHMotor::VNHMotor(int powerPort,int motorPort1,int motorPort2,int enablePort,int maxPower,bool inverted){
	inv=inverted;
	pwPort=powerPort;
	port1=motorPort1;
	port2=motorPort2;
	enPort=enablePort;
	maxPw=maxPower;
	
	if(maxPw>255){
		maxPw=255;
	}
}
VNHMotor::VNHMotor(int powerPort,int motorPort1,int motorPort2,int maxPower,bool inverted){
	inv=inverted;
	pwPort=powerPort;
	port1=motorPort1;
	port2=motorPort2;
	enPort=-1;
	maxPw=maxPower;
	
	if(maxPw>255){
		maxPw=255;
	}
}
void VNHMotor::setupMotor(){
	pinMode(pwPort,OUTPUT);
	pinMode(port1,OUTPUT);
	pinMode(port2,OUTPUT);
	if(enPort>=0)
		pinMode(enPort,OUTPUT);
}
void VNHMotor::set(double power){
	
	double p=power;
	if(p>1.0)
		p=1.0;
	if(p<-1.0)
		p=-1.0;
	int pw=(int)(maxPw*p);

	if(pw==0){
		digitalWrite(pwPort,LOW);
		digitalWrite(port1,LOW);
		digitalWrite(port2,LOW);
		if(enPort>=0)
			digitalWrite(enPort,LOW);
	}
	else if(pw<0){
		if(!inv){
			analogWrite(pwPort,-pw);
			digitalWrite(port1,HIGH);
			digitalWrite(port2,LOW);
			if(enPort>=0)
				digitalWrite(enPort,HIGH);
		}
		else{
			analogWrite(pwPort,-pw);
			digitalWrite(port1,LOW);
			digitalWrite(port2,HIGH);
			if(enPort>=0)
				digitalWrite(enPort,HIGH);
		}
	}
	else{
		if(!inv){
			analogWrite(pwPort,pw);
			digitalWrite(port1,LOW);
			digitalWrite(port2,HIGH);
			if(enPort>=0)
				digitalWrite(enPort,HIGH);
		}
		else{
			analogWrite(pwPort,pw);
			digitalWrite(port1,HIGH);
			digitalWrite(port2,LOW);
			if(enPort>=0)
				digitalWrite(enPort,HIGH);
		}
	}
}
void VNHMotor::stopMotor(){
	set(0.0);
}
double RobotControl::toBoundAngle(double angle){
  double res=angle;
  if(res>360.0){
    res-=360.0;
  }
  if(res<0.0){
    res+=360.0;
  }
  return res;
}
double RobotControl::degreesToRadians(double degrees){
  return degrees*PI/180.0;
}
RobotControl::RobotControl(VNHMotor* motorA,VNHMotor* motorB,VNHMotor* motorC,VNHMotor* motorD){
	motors=new VNHMotor*[4]{motorA,motorB,motorC,motorD};
}
void RobotControl::setMotors(unsigned int mts,double power){
	int ms=mts;
	if(ms>=MD){
		motors[3]->set(power);
		ms-=MD;
	}
	if(ms>=MC){
		motors[2]->set(power);
		ms-=MC;
	}
	if(ms>=MB){
		motors[1]->set(power);
		ms-=MB;
	}
	if(ms>=MA){
		motors[0]->set(power);
	}
}
void RobotControl::stopRobot(){
	setMotors(MA+MB+MC+MD,0.0);
}
void RobotControl::vectorMove(double movementAngle,double power,double rotationGain){
	double adPower=sin(degreesToRadians(toBoundAngle((360.0-movementAngle)+45.0)))*power;
	double bcPower=cos(degreesToRadians(toBoundAngle((360.0-movementAngle)+45.0)))*power;
	
	setMotors(MA,adPower+rotationGain);
	setMotors(MB,bcPower+rotationGain);
	setMotors(MC,bcPower-rotationGain);
	setMotors(MD,adPower-rotationGain);
}
void RobotControl::axisMove(double powerX,double powerY,double rotationGain){
	double adPower=-powerY+powerX;
	double bcPower=powerY+powerX;
	
	setMotors(MA,adPower+rotationGain);
	setMotors(MB,bcPower+rotationGain);
	setMotors(MC,bcPower-rotationGain);
	setMotors(MD,adPower-rotationGain);
}
void RobotControl::vectorMoveTime(double movementAngle,double power,double rotationGain,unsigned int ms){
	unsigned long int timeMark=millis();
	while((millis()-timeMark)<ms)
		vectorMove(movementAngle,power,rotationGain);
}
void RobotControl::moveFwd(double power){
	vectorMove(0.0,power,0.0);
}
void RobotControl::moveRev(double power){
	vectorMove(180.0,power,0.0);
}
void RobotControl::moveRight(double power){
	vectorMove(90.0,power,0.0);
}
void RobotControl::moveLeft(double power){
	vectorMove(270.0,power,0.0);
}

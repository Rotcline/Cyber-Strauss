#include <Arduino.h>
class Motor {
	private:
		byte pwm;
		byte ina;
		byte inb;
	public:
		//Motor(){
			/*this->pwm = pwm;
			this->ina = ina;
			this->inb = inb;
			pinMode(ina,OUTPUT);
			pinMode(inb,OUTPUT);*/
		//}
		void setPwm(byte pwm){
			this->pwm = pwm;
		}
		void setIna(byte ina){
			this->ina = ina;
			pinMode(ina,OUTPUT);
		}
		void setInb(byte inb){
			this->inb = inb;
			pinMode(inb,OUTPUT);
		}
		void fwd(int velocidad = 255){
			digitalWrite(ina,HIGH);
			digitalWrite(inb,LOW);
			analogWrite(pwm,velocidad);
		}
		void rev(int velocidad = 255){
			digitalWrite(ina,LOW);
			digitalWrite(inb,HIGH);
			analogWrite(pwm,velocidad);
		}
		void off(){
			digitalWrite(ina,HIGH);
			digitalWrite(inb,HIGH);
			analogWrite(pwm,100);
		}
};

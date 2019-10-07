#include "Motor.cpp"

class Motores{
  private:
    Motor motorA;
    Motor motorB;
    Motor motorC;
    Motor motorD;
    
  public:
  Motores(byte MotorA1, byte MotorA2, byte MotorB1, byte MotorB2, byte MotorC1, byte MotorC2, byte MotorD1, byte MotorD2, byte pwm1, byte pwm2, byte pwm3, byte pwm4){
    motorA.setPwm(pwm1);
    motorA.setIna(MotorA1);
    motorA.setInb(MotorA2);
    motorB.setPwm(pwm2);
    motorB.setIna(MotorB1);
    motorB.setInb(MotorB2);
    motorC.setPwm(pwm3);
    motorC.setIna(MotorC1);
    motorC.setInb(MotorC2);
    motorD.setPwm(pwm4);
    motorD.setIna(MotorD1);
    motorD.setInb(MotorD2);
  }
  void gi(short velocidad){
    motorA.rev(velocidad);
    motorB.rev(velocidad);
    motorC.rev(velocidad);
    motorD.rev(velocidad);
  }
  void gd(short velocidad){
    motorA.fwd(velocidad);
    motorB.fwd(velocidad);
    motorC.fwd(velocidad);
    motorD.fwd(velocidad);
  }
  void fwd(short velocidad){
    motorA.fwd(velocidad);
    motorB.fwd(velocidad);
    motorC.rev(velocidad);
    motorD.rev(velocidad);
  }
  void rev(short velocidad){
    motorA.rev(velocidad);
    motorB.rev(velocidad);
    motorC.fwd(velocidad);
    motorD.fwd(velocidad);
  }
  void esqSupIzq(short velocidad){
    motorA.fwd(velocidad);
    motorB.off();
    motorC.off();
    motorD.rev(velocidad);
  }
  void esqSupDer(short velocidad){
    motorA.off();
    motorB.fwd(velocidad);
    motorC.rev(velocidad);
    motorD.off();
  }
  void esqInfIzq(short velocidad){
    motorA.off();
    motorB.rev(velocidad);
    motorC.fwd(velocidad);
    motorD.off();
  }
  void esqInfDer(short velocidad){
    motorA.rev(velocidad);
    motorB.fwd();
    motorC.rev();
    motorD.fwd(velocidad);
  }
  void der(short velocidad){
    motorA.rev(velocidad);
    motorB.fwd(velocidad);
    motorC.rev(velocidad);
    motorD.fwd(velocidad);
  }
  void izq(short velocidad){
    motorA.fwd(velocidad);
    motorB.rev(velocidad);
    motorC.fwd(velocidad);
    motorD.rev(velocidad);
  }
  void off(){
    motorA.off();
    motorB.off();
    motorC.off();
    motorD.off();
    }
};

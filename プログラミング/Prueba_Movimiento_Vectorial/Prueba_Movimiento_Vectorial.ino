#include<Wire.h>
#include<MechaQMC5883.h>

MechaQMC5883 qmc;

int x, y, z;
int azimuth, actual, az;
float inicio;
int ang;
int pwm;
int ad, bc;
float setPoint, p, actualPoint;
float error, prevError, d;
float kd;
float kp;
float PID;
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

void setup() {
  pinMode(13,OUTPUT);//MotorD
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);//MotorB
  pinMode(10,OUTPUT);
  pinMode(7,OUTPUT);//MotorC esta al reves
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);//MotorA
  pinMode(4,OUTPUT);

  Wire.begin();
  Serial.begin(9600);
  qmc.init();
  pwm = 0;
  qmc.read(&x,&y,&z,&azimuth);
  inicio = azimuth;
  actual = 0;
}

inline int reboot(int inicial, int actual){
  int c = actual - inicial;
  if(c<0)
    c+=360;
  return c;
}

void loop() {
  qmc.read(&x,&y,&z,&azimuth);
  if (inicio == 0){
    inicio = azimuth;
  }
  az = reboot(inicio, azimuth);
  Serial.print(inicio);
  
  if(az<=20 || az>=340){
  follow(0,255);
    Serial.print(" ");
    Serial.println (az);
  }
  
  if(az<340 && az>180){
    kp = kd = 1.1;
    setPoint = 360;
    error = az - setPoint;
    p = error * kp;
    d = (error - prevError) * kd;
    prevError = error;
    PID = p+d;
    Serial.print(" ");
    Serial.println (az);
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    analogWrite(9,pwm - PID);
    digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
    analogWrite(8,pwm - PID);
    digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
    analogWrite(3,pwm - PID);
    digitalWrite(5,LOW);
    digitalWrite(4,HIGH);
    analogWrite(2,pwm - PID);
  }
  
  if(az>20 && az<=180){
    kp = kd = 1.1;
    setPoint = 0;
    error = az - setPoint;
    p = error * kp;
    d = (error - prevError) * kd;
    prevError = error;
    PID = p+d;
    Serial.print(" ");
    Serial.println (az);
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    analogWrite(9,pwm + PID);
    digitalWrite(11,HIGH);
    digitalWrite(10,LOW);
    analogWrite(8,pwm + PID);
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    analogWrite(3,pwm + PID);
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
    analogWrite(2,pwm + PID);
  }
}

//void vector(int ang, int pwm){
//  int ad = sin[((ang-45)PI)180]*pwm;
//  int bc = cos[((ang-45)PI)180]*pwm;
//  if(ad<=0 || )
//}

int ang = 0;
int pwm = 255;

void setup() {
  
}

void loop() {
  
int  a = sin(((ang-45)*PI)/180)*pwm;
int  b = sin(((ang-135)*PI)/180)*pwm;
int  c = sin(((ang-225)*PI)/180)*pwm;
int  d = sin(((ang-315)*PI)/180)*pwm;
//8&9==C
//10&11==D
//6&&7==B
//12&&13==A
  if(c>=0){
    analogWrite(8,0);
    analogWrite(9,c);
  }
  else{
    c*(-1);
    analogWrite(8,c);
    analogWrite(9,0);
  }  
    if(d>=0){
    analogWrite(11,0);
    analogWrite(10,d);
  }
  else{
    d*(-1);
    analogWrite(11,d);
    analogWrite(10,0);
  }  
    if(b>=0){
    analogWrite(7,0);
    analogWrite(6,b);
  }
  else{
    b*(-1);
    analogWrite(7,b);
    analogWrite(6,0);
  }  
    if(a>=0){
    analogWrite(13,0);
    analogWrite(12,a);
  }
  else{
    a*(-1);
    analogWrite(13,a);
    analogWrite(12,0);
  }  
}

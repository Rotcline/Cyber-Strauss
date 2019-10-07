#define l 850
int l1,l2,l3;
void setup() {
Serial.begin(9600);
pinMode(8,OUTPUT);
//pinMode(9,OUTPUT);
//pinMode(8,OUTPUT);
//pinMode(7,OUTPUT);
//pinMode(6,OUTPUT);
//pinMode(5,OUTPUT);
//pinMode(4,OUTPUT);
//pinMode(3,OUTPUT);
//pinMode(2,OUTPUT);
}

void loop() {
  digitalWrite(8,HIGH);
  l1 = analogRead(1);
  l2 = analogRead(2);
  l3 = analogRead(3);
  Serial.print(l1);
  Serial.print("\t");
  Serial.print(l2);
  Serial.print("\t");
  Serial.print(l3);
  Serial.println("\t");
}
///Motores
//if(l1<l||l2<l||l3<l){
//  digitalWrite(9,HIGH);//c
//  digitalWrite(8,LOW);}
//  digitalWrite(7,LOW);
//  digitalWrite(6,HIGH);
//  digitalWrite(5,LOW);
//  digitalWrite(4,HIGH);
//  digitalWrite(2,LOW);
//  digitalWrite(3,HIGH);  
//  }
//  else{
//  digitalWrite(9,LOW);
//  digitalWrite(8,HIGH);
//  digitalWrite(7,HIGH);
//  digitalWrite(6,LOW);
//  digitalWrite(5,HIGH);
//  digitalWrite(4,LOW);
//  digitalWrite(3,LOW);
//  digitalWrite(2,HIGH);
//  }
//}
//El Elim es gay GG

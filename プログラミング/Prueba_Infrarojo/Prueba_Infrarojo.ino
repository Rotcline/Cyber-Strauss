#include <HTInfraredSeeker.h>
#include <Wire.h>

int dir, strength;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  InfraredSeeker::Initialize();
  Serial.print("Lets Go");
}

void loop() {
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  dir = InfraredBall.Direction;
  strength = InfraredBall.Strength;
  Serial.println(dir);
}

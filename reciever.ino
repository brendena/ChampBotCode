#include "motor.h"
#include "header.h"


//inits myMotor
//and set the pins for it
Motor myMotor(6,7,10);



void setup() {
  myMotor.init(6,7,10);
  Serial.begin(9600);
}

void loop() { 
  myMotor.readMotorsInputAndTurn();
}


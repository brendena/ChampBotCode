#include "motor.h"
#include "header.h"
#include "submerge.h"
#include "fire.h"



//each differnt section of the champ bot
//is its own class and is a global object.
Motor motorMode;
Fire fireMode; 
Submerge submergingMode; 



void setup() {
  //set the pins for each part.
  //port 2 - 7
  //ch   1 - 6
  motorMode.pins(2,3,10);
  fireMode.pins(6);
  submergingMode.pins(7);
  Serial.begin(9600);
}

void loop() { 
  motorMode.readMotorsInputAndTurn();
  fireMode.checkFireSwitch();
  submergingMode.checkSubmerging();
  delay(1000);
}


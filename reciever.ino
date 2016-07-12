#include "motor.h"
#include "header.h"
#include "submerge.h"
#include "fire.h"



//each differnt section of the champ bot
//is its own class and is a global object.
//Motor motorMode;
//Fire fireMode; 
Submerge submergingMode; 
//Master masterSetup;


void setup() {
  //set the pins for each part.
  //port 2 - 7
  //ch   1 - 6

  // ch 1 left and right on the left stick
  // ch 2 oil spray
  // ch 3 & 4 right analog stick
  // ch 5 glowPlug / little top flipper right
  // ch 6 submergin/ large left flipper

  //shift register 7-10
  
  //motorMode.pins(4,5,10);
  //fireMode.pins(3,6,8,9);
  submergingMode.pins(7,8,9,10,11);
  
  //masterSetup.pins(7,8,9);

  
  Serial.begin(9600);
}

void loop() { 
  
  //motorMode.readMotorsInputAndTurn();
  //fireMode.checkFireSwitch();
  submergingMode.checkSubmerging();
  
  //masterSetup.cycleLoopSwitchRelay();

  
  delay(1000);
}


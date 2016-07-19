#include "motor.h"
#include "header.h"
#include "submerge.h"
#include "fire.h"
#include "head.h"



//each differnt section of the champ bot
//is its own class and is a global object.

Motor motorMode;
Fire fireMode; 
Submerge submergingMode; 
Head headRotationMode;
Master masterSetup;


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
  
  //motorMode.pins(4,5,10,1,2);
  fireMode.pins(3,6,3,4);
  submergingMode.pins(7,9,5,6,7);
  headRotationMode.pins(2,A3,A4);


  /*
  So A0 - A5 pins get mapped to values
  14 - 19
  */
  masterSetup.pins(A0,A1,A2);

  
  Serial.begin(9600);

  
  masterSetup.resetRelayes();
}

void loop() { 
  
  //motorMode.readMotorsInputAndTurn();
  fireMode.checkFireSwitch();
  submergingMode.checkSubmerging();
  headRotationMode.checkHeadRotation();
  
  
  /*
  //masterSetup.testShiftRegister();
  //masterSetup.testShiftRegister();
  //masterSetup.testShiftRegister();
  */
  
  masterSetup.cycleSwitchRelay();
  
  delay(1000);
  
  
}


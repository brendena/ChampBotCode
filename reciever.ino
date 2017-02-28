#include "motor.h"
#include "submerge.h"
#include "fire.h"
#include "head.h"
#include "Arduino.h"


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
  
  motorMode.pins(4,5,10,6,7,A5);
  fireMode.pins(3,6,5,1);
  //7,8,9 input
  //5,6,7,8, outputs
  submergingMode.pins(7,8,9,3,2,8,4);
  headRotationMode.pins(2,A3,A4);


  /*
  So A0 - A5 pins get mapped to values
  14 - 19
  */
  masterSetup.pins(A2,A1,A0);

  
  Serial.begin(9600);

  
  masterSetup.resetRelayes();
}

void loop() { 
  
  fireMode.checkFireSwitch();
  bool submerginOrRissing = submergingMode.checkSubmerging();
  motorMode.readMotorsInputAndTurn(submerging);
  headRotationMode.checkHeadRotation();
  
  
  /*
  //masterSetup.testShiftRegister();
  //masterSetup.testShiftRegister();
  //masterSetup.testShiftRegister();
  */
  
  masterSetup.cycleSwitchRelay();
  
  delay(2000);
  
  
}

#include "head.h"

Head::Head()
{
  
}

void Head::pins(int channelPin, int relayForwardRotation, int relayBackwardRotation)
{ 
   pinMode(channelPin, INPUT);
  _channelPin = channelPin; 
  
   pinMode(relayForwardRotation, OUTPUT);
  _relayForwardRotation = relayForwardRotation; 

    pinMode(relayBackwardRotation, OUTPUT);
  relayBackwardRotation = relayBackwardRotation; 

}


void Head::_testInputValues(int relayForwardRotation)
{
  Serial.print("DC Rotating @ value: ");
  Serial.println(relayForwardRotation);

};

void Head::checkHeadRotation()
{
  //mode 0 = down | Counter-Clockwise motion
  //mode 1 = up | Clockwise motion
  //mode 2 = nothing | brake

  /*
  NOOOOOOOOOOOOOOOOOOOOTES
  change pulse in pulse to the right input pin
  !!!!!!!!!!!!!!!!!!!!!!
  */
  
  int relayForwardRotation = pulseInPlus(_channelPin);
  
  //_testInputValues(relayForwardRotation);
 
  _checkRotationConditionals(relayForwardRotation);
}

void Head::_checkRotationConditionals(int relayForwardRotation)
{
  int mode = DialValue(relayForwardRotation);
/*
_relayBackwardRotation - is relay ___
_relayForwardRotation - is relay ___ 1 or 2
_relayBackwardRotation - backwards - when ___
_relayForwardRotation - forward- when ___


*/

  
  if(mode == 0)
  {
      //For Anti Clock-wise motion, moving the head down 
       
      Serial.println("Moving The Head Down!"); 
      digitalWrite(_relayBackwardRotation,1) ;
      digitalWrite(_relayForwardRotation,0) ;
  }
  else if(mode == 1)
  {
      //For Clock wise motion, moving the head up

      Serial.println("Moving The Head Up!");
      digitalWrite(_relayBackwardRotation,0) ;
      digitalWrite(_relayForwardRotation,1) ;
  }
  //mode 2 nothing
  else
  {
      Serial.println("Head is Not Moving!");
    
      //For brake
      digitalWrite(_relayBackwardRotation,1) ;
      digitalWrite(_relayForwardRotation,1) ;  
  }
}



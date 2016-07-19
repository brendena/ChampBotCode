#include "head.h"

Head::Head()
{
  
}

void Head::pins(int channelPin, int relayUpDownRotation, int relayOnOffRotation)
{ 
   pinMode(relayUpDownRotation, OUTPUT);
  _relayUpDownRotation = relayUpDownRotation; 

    pinMode(relayOnOffRotation, OUTPUT);
  _relayOnOffRotation = relayOnOffRotation; 

}


void Head::_testInputValues(int UpDownRotationValue, int OnOffRotationValue)
{
  Serial.print("DC on-Off value: ");
  Serial.println(OnOffRotationValue);

  Serial.print("DC Rotating @ value: ");
  Serial.println(UpDownRotationValue);

};

void Head::checkHeadRotation()
{
  //mode 0 = up | Clock wise motion
  //mode 1 = down | Anti Clock-wise motion
  //mode 2 = nothing | brake

  /*
  NOOOOOOOOOOOOOOOOOOOOTES
  change pulse in pulse to the right input pin
  !!!!!!!!!!!!!!!!!!!!!!
  */
  
  int UpDownRotationValue = pulseInPlus(_relayUpDownRotation);

  int OnOffRotationValue = pulseInPlus(_relayOnOffRotation);
  
  _testInputValues(UpDownRotationValue, OnOffRotationValue);
 
  //_checkRotationConditionals(UpDownRotationValue, OnOffRotationValue);
}

void Head::_checkRotationConditionals(int UpDownRotationValue, int OnOffRotationValue)
{
  int mode = DialValue(UpDownRotationValue);
  
  if(mode == 0)
  {
      Serial.println("Moving The Head Up!");
      
      //For Clock wise motion, moving the head up
      digitalWrite(_relayOnOffRotation,LOW) ;
      digitalWrite(_relayUpDownRotation,LOW) ;
  }
  else if(mode == 1)
  {
      Serial.println("Moving The Head Down!");
    
      //For Anti Clock-wise motion, moving the head down
      digitalWrite(_relayOnOffRotation,LOW) ;
      digitalWrite(_relayUpDownRotation,HIGH) ;
  }
  //mode 2 nothing
  else
  {
      Serial.println("Head is Not Moving!");
    
      //For brake
      digitalWrite(_relayOnOffRotation,HIGH) ;
      digitalWrite(_relayUpDownRotation,HIGH) ;  
  }
}



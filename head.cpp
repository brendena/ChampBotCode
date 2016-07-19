#include "head.h"

Head::Head()
{
  
}

void Head::pins(int channelPin, int relayUpDownRotation, int relayOnOffRotation)
{ 
   pinMode(channelPin, INPUT);
  _channelPin = channelPin; 
  
   pinMode(relayUpDownRotation, OUTPUT);
  _relayUpDownRotation = relayUpDownRotation; 

    pinMode(relayOnOffRotation, OUTPUT);
  _relayOnOffRotation = relayOnOffRotation; 

}


void Head::_testInputValues(int UpDownRotationValue)
{
  Serial.print("DC Rotating @ value: ");
  Serial.println(UpDownRotationValue);

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
  
  int UpDownRotationValue = pulseInPlus(_channelPin);
  
  //_testInputValues(UpDownRotationValue);
 
  _checkRotationConditionals(UpDownRotationValue);
}

void Head::_checkRotationConditionals(int UpDownRotationValue)
{
  int mode = DialValue(UpDownRotationValue);
  
  if(mode == 0)
  {
      //For Anti Clock-wise motion, moving the head down 
       
      Serial.println("Moving The Head Down!"); 
      digitalWrite(_relayOnOffRotation,0) ;
      digitalWrite(_relayUpDownRotation,1) ;
  }
  else if(mode == 1)
  {
      //For Clock wise motion, moving the head up

      Serial.println("Moving The Head Up!");
      digitalWrite(_relayOnOffRotation,0) ;
      digitalWrite(_relayUpDownRotation,0) ;
  }
  //mode 2 nothing
  else
  {
      Serial.println("Head is Not Moving!");
    
      //For brake
      digitalWrite(_relayOnOffRotation,1) ;
      digitalWrite(_relayUpDownRotation,1) ;  
  }
}



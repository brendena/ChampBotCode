#include "submerge.h"

Submerge::Submerge()
{
}

void Submerge::pins (int submergeRadioPin, int modeDialPin, int relayReleaseValve,  int relayInflateValve, int relayEmergencyValve)
{
  pinMode(submergeRadioPin, INPUT);
  _submergeRadioPin = submergeRadioPin;

  pinMode(modeDialPin, INPUT);
  _modeDialPin = modeDialPin;
  
  pinMode(relayReleaseValve, OUTPUT);
  _relayReleaseValve = relayReleaseValve;

  pinMode(relayInflateValve, OUTPUT);
  _relayInflateValve = relayInflateValve;

  pinMode(relayEmergencyValve, OUTPUT);
  _relayEmergencyValve = relayEmergencyValve;
  
  _firstTime = true;
  _inflated = true;
}

void Submerge::_testInputValues(int submerginValue, int modeDial )
{
  Serial.print("submerging switch value ");
  Serial.println(submerginValue);

  Serial.print("mode Dial value ");
  Serial.println(modeDial);
}

void Submerge::checkSubmerging()
{
  int submergeRadioValue = pulseInPlus(_submergeRadioPin);

  int modeDialValue = pulseInPlus(_modeDialPin);
  
  //_testInputValues(submergeRadioValue, modeDialValue);
  
  _checkSubmerginConditional(submergeRadioValue, modeDialValue );
}

void Submerge::_checkSubmerginConditional(int submergeValue, int modeDial)
{
  
  bool submergeSwitchValue = returnSwitchValue(submergeValue);
  int modeDialValue = DialValue(modeDial);
  
  if (submergeSwitchValue  == true)
  {
      //rising mode
      if(modeDialValue == 1){
        Serial.println("Rising mode is on!");
        digitalWrite(_relayReleaseValve, HIGH);
        digitalWrite(_relayInflateValve, LOW);
        
        /*
        if(firstTime)
        {
          Serial.println("Start Submerging timer");
          startTime = millis();
          firstTime = false;
        }
        
        else
        {
        
          
          digitalWrite(_relayReleaseValve, HIGH);
          
          
          currentTime = millis();
          if ( currentTime - startTime <= 20000)
          {
             Serial.print("Timer: ");
             Serial.println((currentTime - startTime) / 1000 );
             digitalWrite(_pin, HIGH);
          }
          // Emergency!! turn off submerging mode
          
          else
          {
             Serial.println("Emergency!! turning off submerging mode!");
             digitalWrite(_pin, LOW);
          }
          
        }
        */
      }
      //diving mode
      else if(modeDialValue == 0){
        Serial.println("Diving mode is on!");
        digitalWrite(_relayReleaseValve, HIGH);
        digitalWrite(_relayInflateValve, LOW);
      }

      //inbetween a mode so don't do anything
      else
      {
        Serial.println("inbetween Modes nothing happens");
      }
      
      
      //firstTime = false;
  }
  else
  {
    Serial.println("Submerging mode is off!");
    digitalWrite(_relayReleaseValve, LOW);
    digitalWrite(_relayInflateValve, LOW);
    //firstTime = true;
  }
  
}


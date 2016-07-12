#include "submerge.h"

Submerge::Submerge()
{
  _emergancyChecker = false;
  _emergencyTimerValue = 10000; //(20 sec)
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
      if(modeDialValue == 1)
      {
        
        Serial.println("Rising mode is on!");
        digitalWrite(_relayReleaseValve, HIGH);
        digitalWrite(_relayInflateValve, LOW);
      }
      //diving mode
      else if(modeDialValue == 0)
      {
        int timer = _checkTimer();
        
          if ( timer <= _emergencyTimerValue)
          {
             Serial.println("Diving mode is on!");
             digitalWrite(_relayReleaseValve, HIGH);
             digitalWrite(_relayInflateValve, LOW);
             digitalWrite(_relayEmergencyValve, LOW);
          }
          // Emergency!! turn off submerging mode  
          else
          {
             _emergancyChecker = true;
             Serial.println("EMERGENCY!! Turned off Diving mode!");
             Serial.println("RISING MODE IS ON!!");
             digitalWrite(_relayEmergencyValve, HIGH);
             digitalWrite(_relayReleaseValve, LOW);
             digitalWrite(_relayInflateValve, LOW);
          }
      }

      //inbetween a mode so don't do anything
      else
      {
        Serial.println("inbetween Modes nothing happens");
      }
      _firstTime = false;
  }
  else
  {
    Serial.println("Submerging mode is off!");
    digitalWrite(_relayReleaseValve, LOW);
    digitalWrite(_relayInflateValve, LOW);
    _firstTime = true;
  }
  
}

int Submerge::_checkTimer()
{
  int timer = 0;
  if(_firstTime)
  {
    Serial.println("Start Submerging timer");
    startTime = millis();
    _firstTime = false;
  }
  else
  {
    currentTime = millis();
    timer = currentTime - startTime;
    Serial.print("Timer: ");
    Serial.println(timer / 1000 );
  }
  return timer;
}


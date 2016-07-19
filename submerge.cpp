#include "submerge.h"

Submerge::Submerge()
{
  _emergancyChecker = false;
  _emergencyTimerValue = 600000; //(60 sec)
}

void Submerge::pins (int submergeRadioPin, int modeDialPin, int relayReleaseValve,  int relayInflateValve, int relayEmergencyValve)
{
  pinMode(submergeRadioPin, INPUT);
  _submergeRadioPin = submergeRadioPin;

  pinMode(modeDialPin, INPUT);
  _modeDialPin = modeDialPin;
  
  _relayReleaseValve = relayReleaseValve;

  _relayInflateValve = relayInflateValve;
  
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
        turnOnOffRelay(_relayReleaseValve, 1);
        turnOnOffRelay(_relayInflateValve, 0);
      }
      //diving mode
      else if(modeDialValue == 0)
      {
          int emergencyTimer = _checkTimer();
          //Serial.print(emergencyTimer);
          //Serial.print(" <= " );
          //Serial.println(_emergencyTimerValue);
          if ( emergencyTimer <= _emergencyTimerValue)
          {
             Serial.println("Diving mode is on!");
             turnOnOffRelay(_relayReleaseValve, 0);
             turnOnOffRelay(_relayInflateValve, 1);
             turnOnOffRelay(_relayEmergencyValve, 1);
          }
          // Emergency Mode  
          else
          {
             _emergancyChecker = true;
             Serial.println("EMERGENCY!! Turned off Diving mode!");
             Serial.println("RISING MODE IS ON!!");
             turnOnOffRelay(_relayEmergencyValve, 0);
             turnOnOffRelay(_relayReleaseValve, 1);
             turnOnOffRelay(_relayInflateValve, 1);
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
    turnOnOffRelay(_relayReleaseValve, 1);
    turnOnOffRelay(_relayInflateValve, 1);
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


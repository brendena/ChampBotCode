#include "submerge.h"

Submerge::Submerge()
{
  _emergancyChecker = false;
  _inflatingChecker = false;
  _emergencyTimerValue = 60000; //(60 sec)
  _inflatingTimerValue = 5000; //(5 sec)
  _timer = 0;
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
  
  _firstTimeSubmerging = true;
  _firstTimeInflating = true;
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
        int inflatingTimer = _checkTimer(_firstTimeInflating);
        
        if ( inflatingTimer <= _inflatingTimerValue)
        {
          Serial.println("Rising mode is on!");
          turnOnOffRelay(_relayReleaseValve, 1);
          turnOnOffRelay(_relayInflateValve, 0);
        }
        else
        {
          _inflatingChecker = true;
          Serial.println("Inflating Done!!");
          turnOnOffRelay(_relayReleaseValve, 1);
          turnOnOffRelay(_relayInflateValve, 1);
        }
      }
      //diving mode
      else if(modeDialValue == 0)
      {
          int emergencyTimer = _checkTimer(_firstTimeSubmerging);
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

        // reseting timer's indicators
        _startTime = millis();
        _firstTimeSubmerging = true;
        _firstTimeInflating = true;
      
      }
      _firstTimeSubmerging = false;
      _firstTimeInflating = false;
  }
  else
  {
    Serial.println("Submerging mode is off!");
    turnOnOffRelay(_relayReleaseValve, 1);
    turnOnOffRelay(_relayInflateValve, 1);

    // reseting timer's indicators
    _timer = 0;
    _startTime = millis();
    _firstTimeSubmerging = true;
    _firstTimeInflating = true;
  }
  
}

unsigned long Submerge::_checkTimer(bool& firstTimeIndicator)
{
  _timer = 0;
  if(firstTimeIndicator)
  {
    Serial.println("Starting Timer");
    _startTime = millis();
  }
  else
  {
    _currentTime = millis();
    _timer = _currentTime - _startTime;
    Serial.print("Timer: ");
    Serial.println(_timer / 1000 );
  }
  return _timer;
}


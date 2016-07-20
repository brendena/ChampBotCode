#include "submerge.h"

Submerge::Submerge()
{
  _emergancyChecker = false;
  _inflatingChecker = false;
  _emergencyTimerValue = 60000; //(60 sec)
  _inflatingTimerValue = 5000; //(5 sec)
  _emergencyInflatingTimerValue = 3000; //(3 sec)
  _timer = 0;
}

void Submerge::pins (int submergeRadioPin, int e_modeDialPin , int modeDialPin,
                     int relayReleaseValve, int relayInflateValve, int e_relayReleaseValve, int e_relayInflateValve)
{
  pinMode(submergeRadioPin, INPUT);
  _submergeRadioPin = submergeRadioPin;

  pinMode(e_modeDialPin, INPUT);
  _e_modeDialPin = e_modeDialPin;
  
  pinMode(modeDialPin, INPUT);
  _modeDialPin = modeDialPin;
  
  _relayReleaseValve = relayReleaseValve;

  _relayInflateValve = relayInflateValve;

  _e_relayReleaseValve = e_relayReleaseValve;
  
  _e_relayInflateValve = e_relayInflateValve;
  
  _firstTimeSubmerging = true;
  _firstTimeInflating = true;
  _firstTimeEmergencyInflating = true;
}

void Submerge::_testInputValues(int submerginValue, int modeDialValue, int e_modeDialValue )
{
  Serial.print("submerging switch value ");
  Serial.println(submerginValue);

  Serial.print("mode Dial value ");
  Serial.println(modeDialValue);

  Serial.print("Emergency mode Dial value ");
  Serial.println(e_modeDialValue);
}

void Submerge::checkSubmerging()
{
  int submergeRadioValue = pulseInPlus(_submergeRadioPin);

  int modeDialValue = pulseInPlus(_modeDialPin);

  int e_modeDialValue = pulseInPlus(_e_modeDialPin);
  
  //_testInputValues(submergeRadioValue, modeDialValue, e_modeDialValue);
  
  _checkSubmerginConditional(submergeRadioValue, modeDialValue, e_modeDialValue );
}

void Submerge::_checkSubmerginConditional(int submergeValue, int modeDial, int e_modeDial)
{
  
  bool submergeSwitchValue = returnSwitchValue(submergeValue);
  int modeDialValue = DialValue(modeDial);
  int emergencyDialValue = DialValue(e_modeDial);

  int active_In_flateRelay, active_De_flateRelay;
  int emergency_In_flateRelay, emergency_De_flateRelay;
  
  //emergcy off
  if(emergencyDialValue == false)
  {
    Serial.println("Emergency mode is OFF!");
    
    active_In_flateRelay = _relayInflateValve;
    active_De_flateRelay = _relayReleaseValve;

    emergency_In_flateRelay = _e_relayInflateValve;
    emergency_De_flateRelay = _e_relayReleaseValve;

    turnOnOffRelay(active_De_flateRelay, 1);
    turnOnOffRelay(active_In_flateRelay, 1);
    turnOnOffRelay(emergency_De_flateRelay, 0);
    turnOnOffRelay(emergency_In_flateRelay, 1);
  }
  else if(emergencyDialValue == true)
  {
    Serial.println("Emergency mode is ON!");
    active_In_flateRelay = _e_relayInflateValve;
    active_De_flateRelay = _e_relayReleaseValve;

    emergency_In_flateRelay = _relayInflateValve;
    emergency_De_flateRelay = _relayReleaseValve;

    turnOnOffRelay(active_De_flateRelay, 1);
    turnOnOffRelay(active_In_flateRelay, 1);
    turnOnOffRelay(emergency_De_flateRelay, 0);
    turnOnOffRelay(emergency_In_flateRelay, 1);
  }

  
  if (submergeSwitchValue  == true)
  {
      //rising mode
      if(modeDialValue == 1)
      {
        int inflatingTimer = _checkTimer(_firstTimeInflating);
        
        if ( inflatingTimer <= _inflatingTimerValue)
        {
          Serial.println("Rising mode is on!");
          turnOnOffRelay(active_De_flateRelay, 1);
          turnOnOffRelay(active_In_flateRelay, 0);
        }
        else
        {
          _inflatingChecker = true;
          Serial.println("Inflating Done!!");
          turnOnOffRelay(active_De_flateRelay, 1);
          turnOnOffRelay(active_In_flateRelay, 1);
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
             turnOnOffRelay(active_De_flateRelay, 0);
             turnOnOffRelay(active_In_flateRelay, 1);
             
          }
          // Emergency Mode  
          else
          {
              _emergancyChecker = true;
              Serial.println("EMERGENCY!!");
             
              int emergencyInflatingTimer = _checkTimer(_firstTimeEmergencyInflating);
              
              if ( (emergencyInflatingTimer - _emergencyTimerValue) <= _emergencyInflatingTimerValue)
              {
                Serial.println("Emergency Inflating...");
                // activate emergency system
                turnOnOffRelay(emergency_De_flateRelay, 1);
                turnOnOffRelay(emergency_In_flateRelay, 0);

                 // turn off active system
                 turnOnOffRelay(active_De_flateRelay, 0);
                 turnOnOffRelay(active_In_flateRelay, 1);
              }
              else
              {
                _emergencyInflatingChecker = true;
                Serial.println("Emergency Inflating Done!!");
                // Active system
                 turnOnOffRelay(active_De_flateRelay, 1);
                 turnOnOffRelay(active_In_flateRelay, 1);
                 
                 // Emergency system
                 turnOnOffRelay(emergency_De_flateRelay, 1);
                 turnOnOffRelay(emergency_In_flateRelay, 1);
              }
             _firstTimeEmergencyInflating = false;
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
        _firstTimeEmergencyInflating = true;
      
      }
      _firstTimeSubmerging = false;
      _firstTimeInflating = false;
      _firstTimeEmergencyInflating = false;
  }
  else
  {
    Serial.println("Submerging mode is off!");

     // Active system
     turnOnOffRelay(active_De_flateRelay, 1);
     turnOnOffRelay(active_In_flateRelay, 1);

    // reseting timer's indicators
    _timer = 0;
    _startTime = millis();
    _firstTimeSubmerging = true;
    _firstTimeInflating = true;
    _firstTimeEmergencyInflating = true;
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


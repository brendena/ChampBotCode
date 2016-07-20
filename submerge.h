#ifndef SUBMERGE_H
#define SUBMERGE_H

#include "master.h"
#include "Arduino.h"  

class Submerge : public Master
{
  public:
    Submerge ();
    void pins (int submergeRadioPin, int modeDialPin,  int relayReleaseValve,  int relayInflateValve, int relayEmergencyValve);
    void checkSubmerging();
    
  private:
    int _submergeRadioPin; //pin
    int _modeDialPin;

    
    int _relayReleaseValve;
    int _relayInflateValve;
    int _relayEmergencyValve;
    
    unsigned long _timer, _startTime, _currentTime, _emergencyTimerValue, _inflatingTimerValue;
    bool _firstTimeSubmerging, _firstTimeInflating;
    void _testInputValues(int submerginValue, int modeDial );
    void _checkSubmerginConditional(int submergeRadioValue, int modeDialValue);

    unsigned long _checkTimer(bool& firstTimeIndicator);
    bool _emergancyChecker, _inflatingChecker;
};
/*
Notes
When no power is given to the 
relay that mean that the valves are closed

*/

#endif

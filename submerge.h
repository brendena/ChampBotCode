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
    
    unsigned long startTime, currentTime;
    bool _firstTime;
    void _testInputValues(int submerginValue, int modeDial );
    void _checkSubmerginConditional(int submergeRadioValue, int modeDialValue);

    int _checkTimer();

    int _inflated, _emergencyTimerValue;

    bool _emergancyChecker;
};
/*
Notes
When no power is given to the 
relay that mean that the valves are closed

*/

#endif

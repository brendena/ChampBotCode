#ifndef SUBMERGE_H
#define SUBMERGE_H

#include "master.h"
#include "Arduino.h"  

class Submerge : public Master
{
  public:
    Submerge ();
    void pins (int submergeRadioPin, int modeDialPin, int e_modeDialPin ,  
               int relayReleaseValve, int relayInflateValve, int e_relayReleaseValve, int e_relayInflateValve);
    void checkSubmerging();
    
  private:
    int _submergeRadioPin; //pin
    int _modeDialPin, _e_modeDialPin;

    
    int _relayReleaseValve;
    int _relayInflateValve;

    // emergency system
    int _e_relayReleaseValve;
    int _e_relayInflateValve;
    
    /*
    unsigned long _timer, _startTime, _currentTime, _emergencyTimerValue, _inflatingTimerValue, _emergencyInflatingTimerValue;
    bool _firstTimeSubmerging, _firstTimeInflating, _firstTimeEmergencyInflating;
    bool _emergancyChecker, _inflatingChecker, _emergencyInflatingChecker;
    */

   struct timerObject{
      unsigned long _startTime;
      int duration;
      bool _flag;
    };
    
    timerObject _emergencyTimer;
    timerObject _inflatingTimerValue;
    timerObject _emergencyInflatingTimerValue;

   
    void _testInputValues(int submerginValue, int modeDialValue, int e_modeDialValue );
    void _checkSubmerginConditional(int submergeRadioValue, int modeDial, int e_modeDial);
    void resetTimers();

    bool _checkTimer(bool& firstTimeIndicator);
    
    bool emergancyModeIsPermanentlyOn;


    //one means not active
    void changeRelayStates(int state);
};
/*
Notes
When no power is given to the 
relay that mean that the valves are closed

*/

#endif

#ifndef SUBMERGE_H
#define SUBMERGE_H

#include "master.h"
#include "Arduino.h"  

/************** Start Submerge Class Definition ************/

class Submerge : public Master
{
	/************** Start Public Functions ************/
	public:
	    Submerge ();	// constructor

	    // initialize pins for the submerge system
	    void pins (int submergeRadioPin, int modeDialPin, int e_modeDialPin ,  
	               int relayReleaseValve, int relayInflateValve, int e_relayReleaseValve, int e_relayInflateValve);
	    
	    // a testing function
	    void checkSubmerging();

	/************** End Public Functions ************/


	/************** Start Private Functions ************/
	private:
		// class members 
	    int _submergeRadioPin; //pin
	    int _modeDialPin, _e_modeDialPin;
	    
	    int _relayReleaseValve;
	    int _relayInflateValve;

	    // emergency system
	    int _e_relayReleaseValve;
	    int _e_relayInflateValve;
	    
	    // variables for the timer system
	    /*************************************************/
	    unsigned long _timer, _startTime, _currentTime;
	    unsigned long _emergencyTimerValue, _inflatingTimerValue, _emergencyInflatingTimerValue;
	    
	    bool _firstTimeSubmerging, _firstTimeInflating, _firstTimeEmergencyInflating;
	    bool _emergancyChecker, _inflatingChecker, _emergencyInflatingChecker;
	    /*************************************************/

	    // main timer function
	    unsigned long _checkTimer(bool& firstTimeIndicator);
	
	    // testing function for getting input
	    void _testInputValues(int submerginValue, int modeDialValue, int e_modeDialValue );
	    
	    // a checker function for input from the remote control 
	    void _checkSubmerginConditional(int submergeRadioValue, int modeDial, int e_modeDial);
	    
	/************** End Private Functions ************/

};


/************** End Master Class Definition ************/

#endif

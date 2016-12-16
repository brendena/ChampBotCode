
#ifndef FIRE_H
#define FIRE_H

#include "master.h"
#include "Arduino.h"

/************** Start Fire Class Definition ************/
class Fire : public Master
{
	/************** Start Public Functions ************/

	public:
	    Fire ();	//Constructor

	   	// initialize pins for the fire system
	    void pins (int glowPlug, int oilSpray, int relayGlowPlug, int relayOilSpray);
	   
	    // main function for the fire system 
	    void checkFireSwitch();
	
	/************** End Public Functions ************/

	/************** Start Private Functions ************/
	private:
		// class members
		int _glowPlug;
	    int _oilSpray;
	    int _relayGlowPlug;
	    int _relayOilSpray;

	    // testing function
	    void _testInputValues(int glow, int oil );
	    
	    // checks for input from the user
	    void _checkFireSwitchConditionals(int glowPlugRadioValue, int oilSprayRadioValue);

	/************** End Private Functions ************/

};

/************** End Fire Class Definition ************/


#endif


#ifndef HEAD_H
#define HEAD_H

#include "master.h"
#include "Arduino.h"


/************** Start Head Class Definition ************/
class Head : public Master
{

	/************** Start Public Functions ************/
	public:
	    Head ();	// constructor

	   	// initialize pins for the head movement system
	    void pins (int channelPin, int relayForwardRotation, int relayBackwardRotation);
	    
	    // main function to move the head up and down 
	    void checkHeadRotation();

	/************** End Public Functions ************/


	/************** Start Private Functions ************/
	private:
		// class members
	    int _relayForwardRotation; // up-Down relay 
	    int _relayBackwardRotation;  // On-Off relay
	    int _channelPin;
	    
	    // testing function
	    void _testInputValues(int relayForwardRotation);
	    
	    // checks for input from the user
	    void _checkRotationConditionals(int relayForwardRotation);
	    
	/************** End Private Functions ************/	    

};
/************** End Head Class Definition ************/

#endif

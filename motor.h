#ifndef Motor_h
#define Motor_h

#include "master.h"
#include "Arduino.h"
#include <SPI.h>

/************** Start Motor Class Definition ************/

class Motor : public Master
{
	/************** Start Public Functions ************/
	public:
	    Motor ();	// constructor
	    
	   	// initialize pins for the motor system
	    void pins(int xPin, int yPin, int slavePin, int leftMotorRelay, int rightMotorRelay);
	    
	    // main function for motors 
	    void readMotorsInputAndTurn();
  	/************** End Public Functions ************/

    
   	/************** Start Private Functions ************/

	private:
	  	// class members
	  	int _lastRegisteredSpeedRight;
	    int _lastRegisteredSpeedLeft;
	    int _speedLeftMotor;
	    int _speedRightMotor;
	    int _xPin;
	    int _yPin;
	    int _slavePin;
	    int _leftMotorRelay;
	    int _rightMotorRelay;
	    static int _marginErrorNumber; 

	    // testing function for input
	    void _testInputValues(int upDown, int leftRigh);
	    
		// send movement signals to the motors 
	    void _digitalPotWrite(int address, int value);
	    
	    // get user input and move
	    void _figureOutDirectionEngine(int y, int x);

	    // turn on/off relayes to allow going backwards 
	    void _relaySwitches();
	    
	    //a helper function to smooth the motor movement 
	    void _rampUp(int channel, int lastRegisteredSpeed, int currentSpeed);

  	/************** End Private Functions ************/


};

/************** End Motor Class Definition ************/


#endif

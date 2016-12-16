#ifndef master
#define master
#include "Arduino.h"



/************** Start Master Class Definition ************/
class Master 
{

	/************** Start Public Functions ************/
	public:
	  	
	 	// initialize pins on the arduino
	    void pins(int dataPin, int latchPin, int clockPin);
	    
	    // a function to update relayes status 
	    void cycleSwitchRelay();

	    // a function to trun off all relayes 
	    void resetRelayes();

	    // a function to turn on or off a relay by specifying its pin number
	    void turnOnOffRelay(int changePin, int onOff);

	    // a test function for shift register
	    void testShiftRegister();
	
	/************** End Public Functions ************/


	/************** Start Private and Protected Functions ************/
	protected:

		// constans variables used for remote input limits 
	    static int _minParametersMaped;
	    static int _maxParametersMaped;
	    static int _mapedLowerBound; 
	    static int _mapedUpperBound;
		
		// changes the range of acceptable input from a specific button/dial/switch on the remote control
		int changeRange(int x);

		// defines a margin area where any input within that range wouldn't be acceptable
		bool marginError(int postion , int  marginError);

		// turns on a pin
    	int pulseInPlus(int pin);

    	// checks the input value a switch 
    	bool returnSwitchValue(int x);

    	// checks the input value of a dial 
    	int DialValue(int value);
    
   

  	private:
  		// constans variables for the shift register system
	    static int _marginErrorNumber;
	    static int _shiftRegisterMaxValue;
	    static int _shiftRegisterCurrentValue;
	    static int _shiftRegisterOriginalValue;
	    
	    //SR - shift register
	    int _SRDataPin; 
	    int _SRLatchPin;
	    int _SRClockPin;
	    
	    // main shift register driver function
	    void _shiftInBytes(int bytes);

	    /************** End Private and Protected Functions ************/

};


/************** End Master Class Definition ************/

#endif

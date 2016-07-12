#ifndef master
#define master
#include "Arduino.h"



class Master {
	protected:
		int changeRange(int x);
		bool marginError(int postion , int  marginError);
		static int minParametersMaped;
		static int maxParametersMaped;
    int pulseInPlus(int pin);

    static int _mapedLowerBound; 
    static int _mapedUpperBound; 
    
    bool returnSwitchValue(int x);
    void turnOnOffRelay(int changePin, int onOff); //array
    void cycleLoopSwitchRelay();

    int DialValue(int value);
    
    void pins(int dataPin, int latchPin, int clockPin);

  private:
    static int _marginErrorNumber; 
    
    static int _shiftRegisterCurrentValue;
    static int _shiftRegisterOriginalValue;
    
    static int _SRDataPin; //SR - shift register
    static int _SRLatchPin;
    static int _SRClockPin;
    
    void _shiftInBytes(int bytes);
    
    
};

#endif

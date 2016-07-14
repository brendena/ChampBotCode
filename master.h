#ifndef master
#define master
#include "Arduino.h"



class Master {
  public:
  
    void pins(int dataPin, int latchPin, int clockPin);
    void cycleSwitchRelay();
    void resetRelayes();
    void turnOnOffRelay(int changePin, int onOff); //array
    void test();
    void testShiftRegister();

    
	protected:
		int changeRange(int x);
		bool marginError(int postion , int  marginError);
		static int minParametersMaped;
		static int maxParametersMaped;
    int pulseInPlus(int pin);

    static int _mapedLowerBound; 
    static int _mapedUpperBound; 
    
    bool returnSwitchValue(int x);

    int DialValue(int value);
    
    

    

  private:
    static int _marginErrorNumber; 
    
    static int _shiftRegisterCurrentValue;
    static int _shiftRegisterOriginalValue;
    
    int _SRDataPin; //SR - shift register
    int _SRLatchPin;
    int _SRClockPin;
    
    void _shiftInBytes(int bytes);
    
    
};

#endif

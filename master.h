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
};

#endif

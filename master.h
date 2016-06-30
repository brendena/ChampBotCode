#ifndef master
#define master
#include "Arduino.h"


class Master {
	protected:
		int changeRange(int x);
		bool marginError(int postion , int  marginError);
		static int minParametersMaped;
		static int maxParametersMaped;
		
};

#endif


#ifndef HEAD_H
#define HEAD_H

#include "master.h"
#include "Arduino.h"

class Head : public Master
{
   private:
    int _relayUpDownRotation; // up-Down relay 
    int _relayOnOffRotation;  // On-Off relay
    int _channelPin;
    
    void _testInputValues(int UpDownRotationValue);
    void _checkRotationConditionals(int UpDownRotationValue);
    
  public:
    Head ();
    void pins (int channelPin, int relayUpDownRotation, int relayOnOffRotation);
    void checkHeadRotation();
};



#endif

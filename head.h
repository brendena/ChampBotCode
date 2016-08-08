
#ifndef HEAD_H
#define HEAD_H

#include "master.h"
#include "Arduino.h"

class Head : public Master
{
   private:
    int _relayForwardRotation; // up-Down relay 
    int _relayBackwardRotation;  // On-Off relay
    int _channelPin;
    
    void _testInputValues(int forwardRotationValue);
    void _checkRotationConditionals(int backwardRotationValue);
    
  public:
    Head ();
    void pins (int channelPin, int relayForwardRotation, int relayBackwardRotation);
    void checkHeadRotation();
};



#endif

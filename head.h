
#ifndef HEAD_H
#define HEAD_H

#include "master.h"
#include "Arduino.h"

class Head : public Master
{
   private:
    int _relayUpDownRotation; // up-Down relay 
    int _relayOnOffRotation;  // On-Off relay
    
    void _testInputValues(int UpDownRotationValue, int OnOffRotationValue);
    void _checkRotationConditionals(int UpDownRotationValue, int OnOffRotationValue);
    
  public:
    Head ();
    void pins (int channelPin, int relayUpDownRotation, int relayOnOffRotation);
    void checkHeadRotation();
};



#endif

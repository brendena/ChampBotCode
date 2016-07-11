#ifndef FIRE_H
#define FIRE_H

#include "master.h"
#include "Arduino.h"

class Fire : public Master
{
  public:
    Fire ();
    void pins (int glowPlug, int oilSpray);
    void checkFireSwitch();
    
  private:
    void _testInputValues(int glow, int oil );
    void _checkFireSwitchConditionals(int glowPlugRadioValue, int oilSprayRadioValue);
    int _glowPlug;
    int _oilSpray;
    int _relayGlowPlug;
    int _relayOilSpray;
};



#endif

#ifndef FIRE_H
#define FIRE_H

#include "master.h"
#include "Arduino.h"

class Fire : public Master
{
  public:
    Fire ();
    void pins (int pinNumber);
    void checkFireSwitch();
    
  private:
    void _testInputValues(int x);
    void _checkFireSwitchConditionals(int ch);
    int _pin; //pin
};



#endif

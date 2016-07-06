#ifndef SUBMERGE_H
#define SUBMERGE_H

#include "master.h"
#include "Arduino.h"  

class Submerge : public Master
{
  public:
    Submerge ();
    void pins (int pinNumber);
    void checkSubmerging();
    
  private:
    int _pin; //pin
    unsigned long startTime, currentTime;
    bool firstTime;
    void _testInputValues(int x);
    void _checkSubmerginConditional(int ch);
};

#endif

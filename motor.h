#ifndef Motor_h
#define Motor_h

#include "master.h"
#include "Arduino.h"
#include <SPI.h>

class Motor : public Master
{
  public:
    Motor ();
    void pins(int xPin, int yPin, int slavePin, int leftMotorRelay, int rightMotorRelay);
    void readMotorsInputAndTurn();
    
  private:
    void _testInputValues(int upDown, int leftRigh);
    static int _marginErrorNumber; 
    void _digitalPotWrite(int address, int value);
    void _figureOutDirectionEngine(int y, int x);
    void _relaySwitches();
    
    int _speedLeftMotor;
    int _speedRightMotor;
    int _xPin; //pin
    int _yPin;
    int _slavePin;
    int _leftMotorRelay;
    int _rightMotorRelay;
};


#endif

#ifndef Motor_h
#define Motor_h

#include "master.h"
#include "Arduino.h"
#include <SPI.h>

class Motor : public Master
{
  public:
    Motor (int xPin, int yPin, int slavePin);
    void init(int xPin, int yPin, int slavePin);
    void readMotorsInputAndTurn();
    
  private:
    static int _marginErrorNumber; 
    void _digitalPotWrite(int address, int value);
    void _figureOutDirectionEngine(int x, int y);
    int _speedLeftMotor;
    int _speedRightMotor;
    int _xPin; //pin
    int _yPin;
    int _slavePin;
};


#endif

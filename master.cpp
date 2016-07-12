#include "master.h"

int Master::minParametersMaped = 0;
int Master::maxParametersMaped = 100;
int Master::_mapedLowerBound = 1040;
int Master::_mapedUpperBound = 1880;
int Master::_shiftRegisterCurrentValue = 0;



void Master::pins(int dataPin, int latchPin, int clockPin)
{
  pinMode(dataPin, OUTPUT);
  _SRDataPin = dataPin;
  pinMode(latchPin, OUTPUT);
  _SRLatchPin = latchPin;
  pinMode(clockPin, OUTPUT); 
  _SRClockPin = clockPin;
}

int Master::DialValue(int value)
{
  int returnValue;
  if(value < 1300)
  {
    returnValue = 0;
  }
  else if(value > 1700)
  {
    returnValue = 1;
  }
  else 
  {
      returnValue = 2;
  }
  return returnValue;
}

/*
Input 
example
turnOnOffRelay( [[pinYouWantToSwitch, OnOrValue], [8, 0]] );

How Works-
Basically the 74hc595 has 8 output pins and this function allows you to change 
and turn off or on each of these pins individually

*/

void Master::turnOnOffRelay(int changePin, int onOff)
{

    //checking to see if it needs to be changed

    // this will make the value 
    changePin = 2 ^ changePin;
    
    //checking to see active
    if( _shiftRegisterCurrentValue & changePin != changePin)
    {
      //checking to see if you want to turn it off
      if(onOff == false)
      {
        _shiftRegisterCurrentValue -  changePin;
      }
    }
    //not active
    else
    {
      //checking to see want turn it on
      if(onOff == true)
      {
        _shiftRegisterCurrentValue + changePin;
      }
    }
  
}

/*
every cycle there
*/
void Master::cycleLoopSwitchRelay()
{

  if(_shiftRegisterCurrentValue != _shiftRegisterCurrentValue)
  {
    _shiftInBytes(_shiftRegisterCurrentValue);  
  }
  
  _shiftRegisterOriginalValue = _shiftRegisterCurrentValue;
  /* 
  i want it to check to see if it's changed so i don't have to keep wrighting
  to it
  */
}

void Master::_shiftInBytes(int value) {
  digitalWrite(_SRLatchPin, LOW); //Pulls the chips latch low
  shiftOut(_SRDataPin, _SRClockPin, MSBFIRST, value); //Shifts out the 8 bits to the shift register
  digitalWrite(_SRLatchPin, HIGH); //Pulls the latch high displaying the data
}

int Master::pulseInPlus(int pin)
{

  int pulseValue = pulseIn(pin, HIGH, 50000);
  //Serial.println("this is the pulse value");
  //Serial.println(pulseValue);
  if(pulseValue == 0){
    Serial.print("\n not getting signal \n");
  }
  return pulseValue;
}

int Master::changeRange(int x){

  if(x == 0){
    return 0;  
  }
  else if(x < _mapedLowerBound)
  {
    return minParametersMaped;
  }
  else if(x > _mapedUpperBound)
  {
    return maxParametersMaped;
  }
  
  return map(x,_mapedLowerBound, _mapedUpperBound,minParametersMaped, maxParametersMaped);
  
  //map(value, fromLow, fro-+mHigh,toLow, toHigh)
    
}

bool Master::marginError(int postion, int marginError){
  return ( (postion <= marginError) && (postion >= -marginError) );
}  


bool Master::returnSwitchValue(int x)
{
  if( x > 1600 )
  {
    return true;
  }
  else
  {
    return false;  
  }
}




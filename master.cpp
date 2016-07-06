#include "master.h"

int Master::minParametersMaped = 0;
int Master::maxParametersMaped = 100;

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

  return map(x,1055, 1900,minParametersMaped, maxParametersMaped);
  
  //map(value, fromLow, fro-+mHigh,toLow, toHigh)
    
}

bool Master::marginError(int postion, int marginError){
  return ( (postion <= marginError) && (postion >= -marginError) );
}  


bool Master::returnSwitchValue(int x)
{
  if( x > 1500 )
  {
    return true;
  }
  else
  {
    return false;  
  }
}




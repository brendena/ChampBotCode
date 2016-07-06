#include "fire.h"

Fire::Fire()
{
  
}

void Fire::pins(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  _pin = pinNumber; 
}

void Fire::_testInputValues(int x)
{
  Serial.print("fire switch value ");
  Serial.println(x);
};

void Fire::checkFireSwitch()
{
  int ch = pulseInPlus(_pin);

  //_testInputValues(ch);
  
  _checkFireSwitchConditionals(ch);
}

void Fire::_checkFireSwitchConditionals(int ch)
{
  bool switchValue = returnSwitchValue(ch);
  
  if (switchValue  == true)
  {
    Serial.println("Fire Switch is on!");
    digitalWrite(_pin, HIGH);
  }
  else
  {
    Serial.println("Fire Switch is off!");
    digitalWrite(_pin, LOW);
  }
  
}

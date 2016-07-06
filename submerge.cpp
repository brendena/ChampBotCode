#include "submerge.h"

Submerge::Submerge()
{
}

void Submerge::pins (int pinNumber)
{
  pinMode(pinNumber, INPUT);
  _pin = pinNumber;
  firstTime = true;
}

void Submerge::_testInputValues(int x)
{
  Serial.print("submerging switch value ");
  Serial.println(x);
}

void Submerge::checkSubmerging()
{
  int ch = pulseInPlus(_pin);

  _testInputValues(ch);
  
  //_checkSubmerginConditional(ch);
}

void Submerge::_checkSubmerginConditional(int ch)
{
  bool switchValue = returnSwitchValue(ch);

  if (switchValue  == true)
  {
      Serial.println("Submerging mode is on!");
      if(firstTime)
      {
        Serial.println("Start Submerging timer");
        startTime = millis();
        firstTime = false;
      }
      else
      {
        currentTime = millis();
        if ( currentTime - startTime <= 20000)
        {
           digitalWrite(_pin, HIGH);
        }
        // Emergency!! turn off submerging mode
        else
        {
           Serial.println("Emergency!! turning off submerging mode!");
           digitalWrite(_pin, LOW);
        }
      }
      firstTime = false;
  }
  else
  {
    Serial.println("Submerging mode is off!");
    digitalWrite(_pin, LOW);
    firstTime = true;
  }
}


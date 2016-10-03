#include "submerge.h"

Submerge::Submerge()
{ 
  _emergencyTimer._startTime = 0;
  _emergencyTimer.duration = 60000;
  _emergencyTimer._flag = 0;

  _inflatingTimerValue._startTime = 0;
  _inflatingTimerValue.duration = 3000;
  _inflatingTimerValue._flag = 0;
  
  _emergencyInflatingTimerValue._startTime = 0;
  _emergencyInflatingTimerValue.duration = 2000;
  _emergencyInflatingTimerValue._flag = 0;
  
  emergancyModeIsPermanentlyOn = 0;
}

void Submerge::pins (int submergeRadioPin, int e_modeDialPin , int modeDialPin,
                     int relayReleaseValve, int relayInflateValve, int e_relayReleaseValve, int e_relayInflateValve)
{
  pinMode(submergeRadioPin, INPUT);
  _submergeRadioPin = submergeRadioPin;

  pinMode(e_modeDialPin, INPUT);
  _e_modeDialPin = e_modeDialPin;
  
  pinMode(modeDialPin, INPUT);
  _modeDialPin = modeDialPin;
  
  _relayReleaseValve = relayReleaseValve;

  _relayInflateValve = relayInflateValve;

  _e_relayReleaseValve = e_relayReleaseValve;
  
  _e_relayInflateValve = e_relayInflateValve;
}

void Submerge::_testInputValues(int submerginValue, int modeDialValue, int e_modeDialValue )
{
  Serial.print("submerging switch value ");
  Serial.println(submerginValue);

  Serial.print("mode Dial value ");
  Serial.println(modeDialValue);

  Serial.print("Emergency mode Dial value ");
  Serial.println(e_modeDialValue);
}

void Submerge::checkSubmerging()
{
  int submergeRadioValue = pulseInPlus(_submergeRadioPin);

  int modeDialValue = pulseInPlus(_modeDialPin);

  int e_modeDialValue = pulseInPlus(_e_modeDialPin);
  
  //_testInputValues(submergeRadioValue, modeDialValue, e_modeDialValue);

  int submerginOrRissing = 1;
  
  //lost signal
  if (submergeRadioValue == 0)
  {
  	//if we started timer
	if(_inflatingTimerValue._flag == true || _emergencyInflatingTimerValue == true){
		//if timers not done
		//say where done with the timer;
		if(_checkTimer(_inflatingTimerValue) == true){
			emergancyModeIsPermanentlyOn = true;
		}
		else{
			submerginOrRissing = _checkSubmerginConditional(submergeRadioValue, modeDialValue, e_modeDialValue );
		}
	}
	else{
		//do nothing
	}
  }
  // have signal
  else
  {
    submerginOrRissing = _checkSubmerginConditional(submergeRadioValue, modeDialValue, e_modeDialValue );
  }
  return submerginOrRissing;
}

bool Submerge::_checkSubmerginConditional(int submergeValue, int modeDial, int e_modeDial)
{
  
  bool actionSwitchValue = returnSwitchValue(submergeValue);
  int modeDialValue = DialValue(modeDial);
  int emergencyDialValue = DialValue(e_modeDial);


  //default normal state
  
  
  int switchingCase = 0;
  if(emergencyDialValue = true){
    switchingCase = 10;
  }
  
  if(actionSwitchValue == true){
    //rising mode
    if(modeDialValue == 1)
    {
    	if(emergencyDialValue = true || _emergencyTimer == true){
    		switchingCase = 11
    	}
    	else{
    		switchingCase = 1;
    	}
    }
    //diving mode
    else if(modeDialValue == 0)
    {
    	if(emergencyDialValue == true || _emergencyTimer == true){
    		switchingCase = 12;
    	}
    	else{
    		switchingCase = 2;
    	}
    }
    else{
    	switchingCase = 5;
  	}
  }

  
  switch(switchingCase)
  {
    case 0:
      Serial.println("didn't get a case");
      resetTimers();
      changeRelayStates(0);
      break;

      
    //inflating
    case 1:
      if ( _checkTimer(_inflatingTimerValue))
      {
        Serial.println("Rising mode is on!");
        changeRelayStates(1);
      }
      else
      {
        Serial.println("Inflating Done!!");
        changeRelayStates(0);
      }
      break;

      
    //deflating
    case 2:
	  if ( _checkTimer(_ermergencyTimer))
      {
        Serial.println("deflating is on!");
        changeRelayStates(2);
      }
      else
      {
/*where emergency mode need to be inacted*/
        Serial.println("deflating timer is done ");
        Serial.println("probably lost signal");
        changeRelayStates(0);
      }
      break;

    case 10:
    	changeRelayStates(10);
    	resetTimers();
    	break;
      
    //E_inflating
    case 11:
      if ( _checkTimer(_inflatingTimerValue))
      {
        Serial.println("inflating is on!");
        changeRelayStates(1);
      }
      else
      {
        Serial.println("inflating is done ");
        changeRelayStates(10);
      }
      break;
      
    //E_deflating
    case 12:
	  Serial.println("e-float");
	  Serial.println("nothing happens");
      break;

    //inbetween Modes
    case 5:
      resetTimers();
      break;
  }
  if(switchingCase == 0 || switchingCase == 10){
    return 0; 
  }
  else{
    return 1;
  }
}

/*
return a bool.
True mean the timers done.
*/
bool Submerge::_checkTimer(timerObject& timer)
{
  bool timerDone = false;
  if(timer.flag)
  {
    Serial.println("Starting Timer");
    timer._startTime = millis();
  }
  else
  {
  	unsigned long currentTime = millis();
  	if(currentTime < timer._startTime + timer._duration){
  		timerDone = true;
  	}
    Serial.print("Timer: ");
    Serial.println(timer._startTime + timer._duration - currentTime  / 1000 );
  }
  return timerDone;
}

void Submerge::resetTimers(){
	_emergencyInflatingTimerValue.flag = 0;
	_inflatingTimerValue._flag = 0;
	_ermergencyTimer._flag = 0;
}


void Submerge::changeRelayStates(int state){
	/*
	0 - normal state

	1 - inflate 
	
	2 - deflate
	
	10 - E-Mode normal state
	
	11 - E-Mode inflate
	
	12 - E-Mode deflate
	*/
  switch(state)
  {
    //normal state
    case 0:{
      turnOnOffRelay(_relayReleaseValve, 1);
      turnOnOffRelay(_relayInflateValve, 1);
      turnOnOffRelay(_e_relayInflateValve,0);
      turnOnOffRelay(_e_relayReleaseValve,0);
      break;
    }
    //inflating
    case 1:{
      turnOnOffRelay(_relayReleaseValve, 1);
      turnOnOffRelay(_relayInflateValve, 0);
      turnOnOffRelay(_e_relayInflateValve,0);
      turnOnOffRelay(_e_relayReleaseValve,0);
    }
    //deflating
    case 2:{
      turnOnOffRelay(_relayReleaseValve, 0);
      turnOnOffRelay(_relayInflateValve, 1);
      turnOnOffRelay(_e_relayInflateValve,0);
      turnOnOffRelay(_e_relayReleaseValve,0);
    }
    //emergency mode normal mode
    case 10:{
      turnOnOffRelay(_relayReleaseValve, 0);
      turnOnOffRelay(_relayInflateValve, 1);
      turnOnOffRelay(_e_relayInflateValve,1);
      turnOnOffRelay(_e_relayReleaseValve,1);
    }
    //emergency mode inflating
    case 11:{
      turnOnOffRelay(_relayReleaseValve, 0);
      turnOnOffRelay(_relayInflateValve, 1);
      turnOnOffRelay(_e_relayInflateValve,1);
      turnOnOffRelay(_e_relayReleaseValve,0);
    }
    //emergency mode deflating
    case 12:{
      turnOnOffRelay(_relayReleaseValve, 0);
      turnOnOffRelay(_relayInflateValve, 1);
      turnOnOffRelay(_e_relayInflateValve,0);
      turnOnOffRelay(_e_relayReleaseValve,1);
    }
  }
  
}


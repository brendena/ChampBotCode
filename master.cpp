    #include "master.h"

int Master::_minParametersMaped = 0;
int Master::_maxParametersMaped = 100;
int Master::_mapedLowerBound = 1040;
int Master::_mapedUpperBound = 1880;
int Master::_shiftRegisterCurrentValue = 0;
int Master::_shiftRegisterOriginalValue = 0;
int Master::_shiftRegisterMaxValue = 255;

  /* 1 - oil spray
   * 2 - relayInflateValve
   * 3 - relayReleaseValve
   * 4 - e_relayInflateValve
   * 5 - glow plug
   * 6 - left relay
   * 7 - right relay
   * 8 - e_relayReleaseValve
   */
Master::Master(){
  rN.oilSpray = 1;
  rN.relayInflateValue = 2;
  rN.relayReleaseValve = 4;
  rN.e_relayInflateValve  = 8;
  rN.glowPlug = 16;
  rN.leftRelay = 32;
  rN.rightRelay = 64;
  rN.e_relayReleaseValve = 128;
}


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
  
  if (value == 0)
  {
    returnValue = 2;  
  }
  else if(value < 1300)
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

How Works-
Basically the 74hc595 has 8 output pins and this function allows you to change 
and turn off or on each of these pins individually

*/

void Master::turnOnOffRelay(int changePin, int onOff)
{

    changePin = 1 << ( changePin -1);
    //changePin = 2 ^ changePin; 
  
    //Serial.println(" ");
    //Serial.println(_shiftRegisterCurrentValue & changePin);  
    //checking to see active
    if( (_shiftRegisterCurrentValue & changePin) == changePin)
    {
      //checking to see if you want to turn it off
      if(onOff == false)
      {
        _shiftRegisterCurrentValue = _shiftRegisterCurrentValue - changePin;
        //Serial.println("_ ");
        //Serial.print("turning Off shift Register Current Value: ");
        //Serial.println(_shiftRegisterCurrentValue);
      }
    }
    //not active
    else
    {
      //checking to see want turn it on
      if(onOff == true)
      {
        _shiftRegisterCurrentValue = _shiftRegisterCurrentValue + changePin;
        //Serial.println("_ ");
        //Serial.print("Turning on shift Register Current Value: ");
        //Serial.println(_shiftRegisterCurrentValue);
      }
    }
  Serial.println(" ");
}

/*
basically check when and where things can happen.
*/
void Master::_checkConditionals(){

  //see if its active
  //active mean values 0
  // if submerging  you can't
  if(( (_shiftRegisterCurrentValue & rN.relayInflateValue) != rN.relayInflateValue) ||
     (  (_shiftRegisterCurrentValue & rN.relayReleaseValve) != rN.relayReleaseValve )||
     (  (_shiftRegisterCurrentValue & rN.e_relayInflateValve) != rN.e_relayInflateValve)){
      //you can't oilspray left or right relay and glowPlug
    _shiftRegisterCurrentValue = _shiftRegisterCurrentValue | rN.oilSpray | rN.glowPlug | rN.leftRelay | rN.rightRelay;
  }
  
  //if glowPlugs on or spraying fire you can't
  if(( (_shiftRegisterCurrentValue & rN.glowPlug) != rN.glowPlug) || 
     ( (_shiftRegisterCurrentValue & rN.oilSpray) != rN.oilSpray)){
      
    // submerge or inflate
    _shiftRegisterCurrentValue = _shiftRegisterCurrentValue | rN.relayReleaseValve | rN.relayInflateValue;
  }  
  
}


/*
every cycle there
*/
void Master::cycleSwitchRelay()
{
  //things that can't happen
  //change _shiftRegisterCurrentValue

  _checkConditionals();

  
  if( _shiftRegisterCurrentValue != _shiftRegisterOriginalValue )
  {
    Serial.println("__________shiftingBytes_________");
    
    _shiftInBytes(_shiftRegisterCurrentValue);  
  }
  //Serial.println("cycle");

  
  _shiftRegisterOriginalValue = _shiftRegisterCurrentValue;
  /* 
  i want it to check to see if it's changed so i don't have to keep wrighting to it
  */
}

void Master::_shiftInBytes(int value) {
  Serial.print("shift in  ");
  Serial.println(value);
  
  digitalWrite(_SRLatchPin, LOW);
  shiftOut(_SRDataPin, _SRClockPin, MSBFIRST, value);  
  digitalWrite(_SRLatchPin, HIGH);
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
    return _minParametersMaped;
  }
  else if(x > _mapedUpperBound)
  {
    return _maxParametersMaped;
  }
  
  return map(x,_mapedLowerBound, _mapedUpperBound, _minParametersMaped, _maxParametersMaped);
  
  //map(value, fromLow, fro-+mHigh,toLow, toHigh)
    
}

bool Master::marginError(int postion, int marginError)
{
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


/*
TestShiftRegister
has two inputs statements asking
for pins and if its on or off 
*/

void Master::testShiftRegister()
{
      // send data only when you receive data:
  //char bytes;

  Serial.print("original shift register Value ");
  Serial.println(_shiftRegisterOriginalValue, BIN);
  Serial.print("Current shift register Value ");
  Serial.println(_shiftRegisterCurrentValue, BIN);

  
  Serial.print("relay want to change ");
  int relayChangeNumber;
  while(Serial.available() <= 0){};
  if (Serial.available() > 0) {
          // read the incoming byte:
          
          char relayChange = Serial.read();
          Serial.println(relayChange);

          relayChangeNumber = (int)relayChange - 48;
  }
  Serial.print("turn Off On");

  int turnOnOffValue;
  
  while(Serial.available() <= 0){};
  if (Serial.available() > 0) {
          Serial.print("turn Off On");
          char onOff = Serial.read();
          Serial.println(onOff);
          

          turnOnOffValue = (int)onOff - 48;

  }  
  turnOnOffRelay(relayChangeNumber, turnOnOffValue);  
}

void Master::resetRelayes()
{
  _shiftRegisterCurrentValue = _shiftRegisterMaxValue;
  _shiftRegisterOriginalValue = _shiftRegisterMaxValue;
  _shiftInBytes(_shiftRegisterMaxValue); 
}



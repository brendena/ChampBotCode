  #include "fire.h"

Fire::Fire()
{
  
}

void Fire::pins(int glowPlug, int oilSpray, int relayGlowPlug, int relayOilSpray )
{ 
  pinMode(glowPlug, INPUT);
  _glowPlug = glowPlug; 
  pinMode(oilSpray, INPUT);
  _oilSpray = oilSpray;


  _relayGlowPlug = relayGlowPlug;
  _relayOilSpray = relayOilSpray;

}


void Fire::_testInputValues(int glow, int oil )
{
  Serial.print("glow plug switch value ");
  Serial.println(glow);

  Serial.print("oil switch value");
  Serial.println(oil);

};

void Fire::checkFireSwitch()
{
  int glowPlugRadioValue = pulseInPlus(_glowPlug);

  int oilSprayRadioValue = pulseInPlus(_oilSpray);
  
  //_testInputValues(glowPlugRadioValue, oilSprayRadioValue);
  
  _checkFireSwitchConditionals(glowPlugRadioValue, oilSprayRadioValue);
}

void Fire::_checkFireSwitchConditionals(int glowPlugRadioValue, int  oilSprayRadioValue)
{
  bool glowPlug_switchValue = returnSwitchValue(glowPlugRadioValue);
  bool oilSpray_switchValue = returnSwitchValue(oilSprayRadioValue);
  
  if (glowPlug_switchValue  == true)
  {
    Serial.println("Glow plug Switch is on!");
    turnOnOffRelay(_relayGlowPlug, 0);
  }
  else
  {
    Serial.println("Fire Switch is off!");
    turnOnOffRelay(_relayGlowPlug, 1);
  }

  if(oilSpray_switchValue == true){
    Serial.println("Oil Switch is on!");
    turnOnOffRelay(_relayOilSpray, 0);
  }
  else{
    Serial.println("Oil Switch is off!");
    turnOnOffRelay(_relayOilSpray, 1);
  } 
}

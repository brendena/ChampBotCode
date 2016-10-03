#include "motor.h"


Motor::Motor (){
  
}

int Motor::_marginErrorNumber = 5;

void Motor::_testInputValues(int upDown, int leftRight){
  Serial.print("left and right ");
  Serial.println(leftRight);
  Serial.print("up and down " );
  Serial.println(upDown);
  Serial.println(" ");
}


void Motor::pins(int xPin, int yPin, int slavePin, int leftMotorRelay, int rightMotorRelay, int pinTurnOffMotorBoards)
{
  pinMode(xPin, INPUT);
  _xPin = xPin;
  pinMode(yPin, INPUT);
  _yPin = yPin;
  pinMode(slavePin, OUTPUT);
  _slavePin = slavePin;
  pinMode(_pinTurnOffMotorBoards, OUTPUT);
  _pinTurnOffMotorBoards = pinTurnOffMotorBoards

  _leftMotorRelay = leftMotorRelay;
  _rightMotorRelay = rightMotorRelay;

    // initialize SPI:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
}
void Motor::readMotorsInputAndTurn(){

	int x = pulseInPlus(_xPin);
	int y = pulseInPlus(_yPin);

  // add (100) to fix the range for left and right movement
  y = y + 100;
  
  _testInputValues(x, y);

  /*Warning*/
  //for some weird reason x doesn't give a 0 value when not getting a signal
  
  //no signals turn off relays
  if(x == 0 || y == 0 || submerginOrRissing == true){
    Serial.print("turn off Motor Relays");
    turnOnOffRelay(_rightMotorRelay ,1);
    turnOnOffRelay(_leftMotorRelay ,1);
    //turn motors off
    digitalWrite(_pinTurnOffMotorBoards, LOW);
  }
  else{
    //turn motors off
    digitalWrite(_pinTurnOffMotorBoards, HIGH);
	  _figureOutDirectionEngine(x,y); // (upDown, leftRigh)
  }
}

void Motor::_figureOutDirectionEngine(int y, int x){

  // When there is no signal turn off motors
  if(y == 0 )
  {
    _digitalPotWrite(0,0);
    _digitalPotWrite(1,0);
    return;
  }
  
	//example what this is doing
	/*
	x and y are mapped between 0  and 100
	so dividing it by the max makes it easy to find the max/2 shift it to a graph 
	that mid point is 0,0
	
	And then i times it by 2 because i want both x and y range to be between -100 and 100.
	So 100 will be 100 percent forward
	and 
	-100 will be 100 percent backwards
	
	so the graph should look like this
	
	*/
 
  //Serial.println(x);
	y = changeRange(y);
	x = changeRange(x);
 
  
  
  
  //Serial.println(x);
  
  y = (y - maxParametersMaped/2) *2;
	x = (x - maxParametersMaped/2) *2;
  
  // I HATE THIS >...
  y =  - y; 
	//Serial.println(x);
 
        
  Serial.println("\n\n");
  
  //delay(2000);
  
  //checking marginError on both x and y will create circle for the center.
  if( (marginError(x,_marginErrorNumber)) && (marginError(y,_marginErrorNumber)) )
  {
      _speedLeftMotor = 0;
      _speedRightMotor = 0;
  }
  //donuts
	else if(marginError(y,_marginErrorNumber))
	{ 
	  //left donut
		if(x <= 0){
			_speedLeftMotor = -abs(x);
			_speedRightMotor = abs(x);
		}
		//right donut
		else {
			_speedLeftMotor = abs(x);
			_speedRightMotor = -abs(x);
		}
	
	}
  // Going Forward & Backward
  else if(marginError(x,_marginErrorNumber))
  {
    _speedLeftMotor = y;
    _speedRightMotor = y;
               
  }
	else{
		//So the idea is to mimic a joystick that is found on a playstation controller.
		/*
		the problem is that controlllers have much less controll then the joystick we have.
		A joystick can only rotate around a axis
		
		
		Key words
		Driving motor - is the motor that is going faster to make the motor turn.
		following motor - is the motor that is being turned on
		
		So the code bellow work like
		you allow the driving motor to be set by the y position and you have
		the following motor be a percent of that motor based on the position.
		
		So the top left position the gostick is going to be 50 percent of the right motor
		and 100 percent for the right motor.
		
		*/
		
		
		//case for something close in the middle
		/*
		reason for code
		(y * .5)
		is becasue the top left is 50, 100
		
		((x + maxParametersMaped)/1000) * y
		This make the number larger as it goes to the right.
		*/
		
		//turnning left
		if(x < 0){
			//forwards
			if(y > 0){
				_speedLeftMotor = (y  * .5) +  (x + maxParametersMaped)/2  ; //x needs to be subtracted because x is negative and we need to add number	
			}
			//backwards
			else{
				_speedLeftMotor = (y  * .5) - (x + maxParametersMaped)/2  ; //x needs to be subtracted because x is negative and we need to add number
					
			}
     _speedRightMotor = y;
			
		}
		//turnning right
		else{
      _speedLeftMotor = y;
			//forwards
			if(y > 0){
				
				_speedRightMotor = (y * .5)  - (x - maxParametersMaped) /2;
			}
			//backwards
			else {
				
				_speedRightMotor = (y * .5)  + (x - maxParametersMaped) /2;
			}
		}
	}

  /*
  1. this turn on or off relays if there going backwards or forwards
  2. it mappes speeds of the motors to -128 and 128 because the speed goes up logorithmicals so the space
  between 128 256 doesn't do much
  3. then we abs the speeds to the pots because they can't handle the nagative values, but we have to map negative
  values because if we don't the mapping of the values will be off. 
  
  */

  _relaySwitches();

  int mappedExtremes = 255;
  int mappedMinus = -255;
  
  int mappedRight = map(_speedRightMotor,-100, 100 , mappedMinus, mappedExtremes);

  Serial.print(_speedRightMotor);
  Serial.print(" right Motor - Maped ");
  Serial.println(mappedRight);


  int mappedLeft = map(_speedLeftMotor, -100, 100 , mappedMinus, mappedExtremes);
  Serial.print(_speedLeftMotor);
  Serial.print(" left Motor - Maped ");
  Serial.println(mappedLeft);

  
  _digitalPotWrite(0,abs(mappedRight));
  _digitalPotWrite(1,abs(mappedLeft));
  
  Serial.println("mappedright");
  Serial.println(abs(mappedRight));
  Serial.println("mappedLeft");
  Serial.println(abs(mappedLeft));
  //delay(100);

}

void Motor::_relaySwitches()
{
  if(_speedLeftMotor < 0)
  {
    turnOnOffRelay(_leftMotorRelay ,0);
  }
  else
  {
    turnOnOffRelay(_leftMotorRelay ,1);
  }

  if(_speedRightMotor < 0)
  {
    turnOnOffRelay(_rightMotorRelay ,0);
  }
  else
  {
    turnOnOffRelay(_rightMotorRelay ,1);
  }
}

void Motor::_digitalPotWrite(int address, int value){
    // take the SS pin low to select the chip:
  digitalWrite(_slavePin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(_slavePin, HIGH);
}

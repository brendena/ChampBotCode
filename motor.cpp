#include "motor.h"


Motor::Motor (){
  
}

int Motor::_marginErrorNumber = 2;

void Motor::_testInputValues(int leftRight, int upDown){
  Serial.print("left and right ");
  Serial.println(leftRight);
  Serial.print("up and down " );
  Serial.println(upDown);
  Serial.println(" ");
}


void Motor::pins(int xPin, int yPin, int slavePin)
{
  pinMode(xPin, INPUT);
  _xPin = xPin;
  pinMode(yPin, INPUT);
  _yPin = yPin;
  pinMode(slavePin, OUTPUT);
  _slavePin = slavePin;

    // initialize SPI:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
}
void Motor::readMotorsInputAndTurn(){

	int x = pulseInPlus(_xPin);
	int y = pulseInPlus(_yPin);

  _testInputValues(x, y);
  
	//_figureOutDirectionEngine(x,y);
	
}

void Motor::_figureOutDirectionEngine(int x, int y){
	
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
 

	y = changeRange(y);
	x = changeRange(x);

  y = (y - maxParametersMaped/2) *2;
	x = (x - maxParametersMaped/2) *2;
	
 
        
        Serial.println("");
        
        delay(2000);

	//donuts
	if(marginError(y,_marginErrorNumber)){
	        //left donut
		if(x <= 0){
			_speedLeftMotor = 0;
			_speedRightMotor = abs(x);
		}
		//right donut
		else {
			_speedLeftMotor = abs(x);
			_speedRightMotor = 0;
		}
	}
        //margin error y plan
        
        else if(marginError(x,_marginErrorNumber)){
	        // going Forward
               
		        _speedLeftMotor = y;
	          _speedRightMotor = y;
               
		// going backward
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
  
  int mappedRight = map(_speedRightMotor,0, 100 , 0, 255);
  //int mappedRight = map(_speedRightMotor,-100, 100 , 0, 255);
  
  Serial.print(_speedRightMotor);
  Serial.print(" right Motor - Maped ");
  Serial.println(mappedRight);


  //this is because currently we can't go backwards.
  //int mappedLeft = map(_speedLeftMotor, -100, 100 , 0, 255);
  int mappedLeft = map(_speedLeftMotor, 0, 100 , 0, 255);
  Serial.print(_speedLeftMotor);
  Serial.print(" left Motor - Maped ");
  Serial.println(mappedLeft);

  
  _digitalPotWrite(0,mappedRight);
  _digitalPotWrite(1,mappedLeft);

  delay(100);

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

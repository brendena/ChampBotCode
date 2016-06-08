int ledPin1 = 4;    // LED connected to digital pin 4
int ledPin2 = 5;    // LED connected to digital pin 5
int ledPin3 = 6;    // LED connected to digital pin 6

int pin7 = 7; // PWM signal arduino pin
int pin8 = 8; // PWM signal arduino pin
int pin9 = 9; // PWM signal arduino pin
int pin10 = 10; // PWM signal arduino pin
int pin11 = 11; // PWM signal arduino pin
int pin12 = 12; // PWM signal arduino pin

int ch1, ch2, ch3, ch4, ch5, ch6;    // Receiver channels pwm value

int high =1 ,low = 10000;

int minMaxMap(int x){
  return map(x,1000, 1950,0, 100);
  /*
  map(value, fromLow, fromHigh,toLow, toHigh)
  */  
}

void setup() {
  pinMode(pin7, INPUT);
  Serial.begin(9600);

  pinMode(pin8, INPUT);
  Serial.begin(9600);
  
  pinMode(pin9, INPUT);
  Serial.begin(9600);

  pinMode(pin10, INPUT);
  Serial.begin(9600);

  pinMode(pin11, INPUT);
  Serial.begin(9600);

  pinMode(pin12, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Read in the length of the signal in microseconds
  ch1 = pulseIn(pin12, HIGH, 25000);
  Serial.println(minMaxMap(ch1));
  
  /*
 if( high > ch1 )
 {
  Serial.print("Channel #1: ");
  Serial.println(ch1);
  high = ch1;
 }
 else if ( ( ch1 != 0) && (ch1 < low))
 {
  Serial.print("Channel #1: ");
  Serial.println(ch1);
  low = ch1;
 }
 */
/*
  ch2 = pulseIn(pin8, HIGH, 25000);
  Serial.print("Channel #2: ");
  Serial.println(ch2);

  ch3 = pulseIn(pin9, HIGH, 25000);
  Serial.print("Channel #3: ");
  Serial.println(ch3);

  ch4 = pulseIn(pin10, HIGH, 25000);
  Serial.print("Channel #4: ");
  Serial.println(ch4);

  ch5 = pulseIn(pin11, HIGH, 25000);
  Serial.print("Channel #5: ");
  Serial.println(ch5);

  ch6 = pulseIn(pin12, HIGH, 25000);
  Serial.print("Channel #6: ");
  Serial.println(ch6);
 */
}

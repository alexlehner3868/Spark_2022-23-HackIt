int dataPin = 4;	// data pin of shift register
int latchPin = 5;	// latch pin of shift register
int clockPin = 6;	// clock pin of shift register


byte leds1 = 0;		// each var controls leds in each shift register
byte leds2 = 0;	


void setup() 
{
  Serial.begin(9600);
  // set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}


void loop() 
{
  leds1 = 0;	// initialize leds
  leds2 = 0;
  updateShiftRegister();
  delay(2000);
  
  // turn on a given LED pattern
  int pattern1[] = {0, 1, 2, 3, 4, 5, 6, 7};
  int pattern2[] = {0, 1, 2, 3, 4, 5, 6, 7};
  /*
  bitSet(leds1, 5);
  updateShiftRegister();
  delay(5000);
  Serial.println(leds1);
  */
  
  for (int i = 0; i < sizeof(pattern1)/sizeof(pattern1[0]); i++){
    bitSet(leds1, pattern1[i]);
    updateShiftRegister();
//    delay(0);
  }
  
   for (int j = 0; j < sizeof(pattern2)/sizeof(pattern2[0]); j++){
    bitSet(leds2, pattern2[j]);
    updateShiftRegister();
//    delay(500);
  }
  
  //Serial.println(leds1, BIN);
  //Serial.println(leds2, BIN);
  delay(1000000);
}


// set the latchPin to low, then shift out contents of variable 
//	'leds' in the shift register before putting the 'latchPin' 
// 	high again

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds2);
   shiftOut(dataPin, clockPin, LSBFIRST, leds1);
   digitalWrite(latchPin, HIGH);
}

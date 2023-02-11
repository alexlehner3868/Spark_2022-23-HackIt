//TEST UPDATELIGHTS FUNCTION

/************global variables*************/
//led output variables
int latchPin = 5;  // latch pin of shift register
int clockPin = 6; // clock pin of shift register
int dataPin = 4;  // data pin of shift register

byte leds1 = 0;   // each var controls leds in each shift register
byte leds2 = 0; 

  int pattern1[] = {0, 1, 2, 3};
  int pattern2[] = {0, 1, 2, 3};

/************function*************/
void updateShiftRegister(){
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds2);
   shiftOut(dataPin, clockPin, LSBFIRST, leds1);
   digitalWrite(latchPin, HIGH);
}

void updateLights(int pattern1, int pattern2){
  leds1 = 0;  // initialize leds
  leds2 = 0;
  updateShiftRegister();

  for (int i = 0; i < sizeof(pattern1)/sizeof(pattern1); i++){
    bitSet(leds1, pattern1);
    updateShiftRegister();
  }
  
   for (int j = 0; j < sizeof(pattern2)/sizeof(pattern2); j++){
    bitSet(leds2, pattern2);
    updateShiftRegister();
  }


}

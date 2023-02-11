//TEST UPDATELIGHTS FUNCTION

/************global variables*************/
byte leds1 = 0;   // each var controls leds in each shift register
byte leds2 = 0; 

int pattern = 

/************function*************/
void updateLights(int pattern){
  leds1 = 0;  // initialize leds
  leds2 = 0;
  updateShiftRegister();

  int pattern1 = pattern[:8];
  int pattern2 = pattern[8:];

  for (int i = 0; i < sizeof(pattern1)/sizeof(pattern1[0]); i++){
    bitSet(leds1, pattern1[i]);
    updateShiftRegister();
  }
  
   for (int j = 0; j < sizeof(pattern2)/sizeof(pattern2[0]); j++){
    bitSet(leds2, pattern2[j]);
    updateShiftRegister();
  }


}

//TEST UPDATELIGHTS FUNCTION

/************global variables*************/
//led output variables
int dataPin = 4;  // data pin of shift register
int latchPin = 5;  // latch pin of shift register
int clockPin = 6; // clock pin of shift register

byte leds1 = 0;   // each var controls leds in each shift register
byte leds2 = 0; 

int pattern1[] = {0, 1, 2, 3};
int pattern2[] = {0, 1, 2, 3};

int pattern1_size = sizeof(pattern1)/sizeof(pattern1[0]);
int pattern2_size = sizeof(pattern1)/sizeof(pattern1[0]);

/************helper functions*************/
void updateShiftRegister(){
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds2);
   shiftOut(dataPin, clockPin, LSBFIRST, leds1);
   digitalWrite(latchPin, HIGH);
   delay(500);
}

void updateLights(int pattern1[], int pattern2[], int pattern1_size, int pattern2_size){
  leds1 = 0;  // initialize leds
  leds2 = 0;
  updateShiftRegister();

  for (int i = 0; i < pattern1_size; i++){
    bitSet(leds1, pattern1[i]);
    updateShiftRegister();
  }
  for (int j = 0; j < pattern2_size; j++){
    bitSet(leds2, pattern2[j]);
    updateShiftRegister();
  }
}

void setup() {
  Serial.begin(9600);
  // set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() {
  updateLights(pattern1, pattern2, pattern1_size, pattern2_size);
  delay(2000);
}


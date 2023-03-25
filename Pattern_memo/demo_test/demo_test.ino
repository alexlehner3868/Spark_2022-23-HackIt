int analogPin = A0;
int key;
float max;
int threshold;
float rawV;

int dataPin = 3;  // data pin of shift register
int latchPin = 5; // latch pin of shift register
int clockPin = 7; // clock pin of shift register

byte leds1;    // each var controls leds in each shift register
byte leds2; 
int cur_bitVal1;
int cur_bitVal2;

void setup() {
  Serial.begin(9600);
  
  // set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds2);
   shiftOut(dataPin, clockPin, LSBFIRST, leds1);
   digitalWrite(latchPin, HIGH);
}

void loop() {
  updateShiftRegister();
  // find key num
  max = 0;
  threshold = 50;
  for (int i = 0; i < 500; i++) { // measure
    rawV = analogRead(analogPin);
    if (rawV > max) max = rawV; // store max peak
  }
  if (max > threshold) {
    key = round((1073.6-max) / 63.3) - 1;
    Serial.print("Peak voltage: ");
    Serial.println(max);
    Serial.print("Key is: ");
    Serial.println(key);
    // set led
    if (key < 8){
      cur_bitVal1 = bitRead(leds1, 7-key);
      bitWrite(leds1, 7-key, !cur_bitVal1);
      updateShiftRegister();
    }
    else if (key == 16) {
    }
    else{
      cur_bitVal2 = bitRead(leds1, 15-key);
      bitWrite(leds2, 15-key, !cur_bitVal2);
      updateShiftRegister();
    }
    delay(1000);
  }
}


/*
1011 948 884 822
758 695 631 568
503 441 378 314
251 188 125 62
 
*/

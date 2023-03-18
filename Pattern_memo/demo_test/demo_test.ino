int analogPin = A0;
int v; // voltage input from input circuit
int key;

int dataPin = 3;  // data pin of shift register
int latchPin = 5; // latch pin of shift register
int clockPin = 7; // clock pin of shift register

byte leds1;    // each var controls leds in each shift register
byte leds2; 

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
  v = analogRead(analogPin);
  key = round((1073.6-v) / 63.3) - 1;
  Serial.print("v is: ");
  Serial.println(v);
  Serial.print("Key is: ");
  Serial.println(key);
  
  // set led
  if (key < 8){
    bitSet(leds1, (7-key));
    updateShiftRegister();
  }
  else if (key == 16) {
  }
  else{
    bitSet(leds2, (15-key));
    updateShiftRegister();
  }
  delay(500);
}


/*
1011 948 884 822
758 695 631 568
503 441 378 314
251 188 125 62
 
*/

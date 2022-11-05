
/*****************************PIN DECLARATIONS*****************************/

//this is the code for the follower arduino
//all it does is check for input from the leader arduino
//and update light array if necessary

#include <Wire.h>


//pins to check for communication
const int BIT0 = 0;
const int BIT1 = 1;
const int BIT2 = 2;
const int BIT3 = 3;




/*****************************GLOBAL VARIABLES*****************************/




/************************HELPER FUNCTION PROTOTYPES************************/
bool check_for_message();
void update_lights();
/**********************HELPER FUNCTION IMPLEMENTATIONS*********************/

//check if the arduino has sent a new pattern
bool check_for_message() {
  int output;
  //return true if new message is output
  if (digitalRead(BIT3)) {
    //fourth bit being 0 corresponds to no pattern being displayed
    return false;
  } else { 
    return true;
  }

  return false;
}
//if new pattern, update the light display (this updates the lights to a constant array)
void update_lights() {
  int pattern = digitalRead(BIT2)*4 + digitalRead(BIT1)*2 + digitalRead(BIT0);
  //get pattern arrays from Neo
  switch(pattern) {
    case(0):
      //this is the initial response by the leader arduino
      break;
    case(1):
      break;
    case(2):
      break;
    case(3):
      break;
    case(4):
      break;
    default:
      break;
  }

}

void setup() {
  // put your setup code here, to run once:
  pinMode(BIT0, INPUT);
  pinMode(BIT1, INPUT);
  pinMode(BIT2, INPUT);
  pinMode(BIT3, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (check_for_message()) {
    update_lights();
  }
}

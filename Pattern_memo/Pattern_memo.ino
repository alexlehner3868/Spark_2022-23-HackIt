
/*****************************PIN DECLARATIONS*****************************/
#include <Wire.h>

#define SENSORPIN 0; //an example




/*****************************GLOBAL VARIABLES*****************************/




/************************HELPER FUNCTION PROTOTYPES************************/
void waitToStartGame(); // wait and do nothing until 
void createRandomPattern(int size); // output binary n-by-n matrix for pattern
void updateLights(int pattern); //
void checkPattern(); // check if inputted Pattern matches the one given
void errorResponse(); // change LED to RED [& buzz motor] if user input is incorrect


void MAXColourGeneration(); //[output n-by-n matrix with RGB specifications]
void MAXupdateLights(int MAXpattern);
void MAXcheckColour();
void setScore(); // [we don't need to worry about this yet] calculate round score
void checkTimeLimit(); //[if time is up, output errorResponse]

/**********************HELPER FUNCTION IMPLEMENTATIONS*********************/






void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication

}

void loop() {
  // put your main code here, to run repeatedly:

}

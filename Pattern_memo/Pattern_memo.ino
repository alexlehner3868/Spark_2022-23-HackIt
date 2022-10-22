
/*****************************PIN DECLARATIONS*****************************/
#include <Wire.h>

#define SENSORPIN 0; //an example




/*****************************GLOBAL VARIABLES*****************************/




/************************HELPER FUNCTION PROTOTYPES************************/
void waitToStartGame(); // wait and do nothing until 
int createRandomPattern(int size){ // output binary n-by-n matrix for pattern
  int grid_length = (size/3)+2;
  int grid_size = grid_length*grid_length;
  bool marked[grid_size];
  for(int i = 0;i<grid_size;i++){
    marked[i] = false;
  }
  int pattern = 0; //Bitmask that represents the state of the grid
  for(int i = 0;i<size;i++){
    int next = random(0, grid_size);
    while(marked[next]==true){ //If bit has already been picked, pick a new bit
      next = random(0, grid_size);
    }
    pattern|=(1<<next);
    marked[next] = true; //Update as -1 to mark as picked
  }
  delete(marked);

  /******TESTING******
  // Print binary grid representation of pattern
  for(int i = 0;i<grid_size;i++){
      if(i%grid_length==0) Serial.println();
      Serial.print((pattern&(1<<i))>0);
  }
  Serial.println();

  // Print pattern
  Serial.println(pattern);
  */

  return pattern;
}
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


/*****************************PIN DECLARATIONS*****************************/
#include <Wire.h>

#define SENSORPIN 0; //an example




/*****************************GLOBAL VARIABLES*****************************/
int level = 0;



/************************HELPER FUNCTION PROTOTYPES************************/
void beginPattern(); // light up all LEDs within size of the level dimensions to indicate the grid size the pattern will be created in


long long createRandomPattern(int level){ // output binary n-by-n matrix for pattern
  int grid_length = (level/3)+2;
  int grid_size = grid_length*grid_length;
  bool marked[grid_size];
  for(int i = 0;i<grid_size;i++){
    marked[i] = false;
  }
  long long pattern = 0; //Bitmask that represents the state of the grid
  for(int i = 0;i<level;i++){
    int next = random(0, grid_size);
    while(marked[next]==true){ //If bit has already been picked, pick a new bit
      next = random(0, grid_size);
    }
    pattern|=(1LL<<next);
    marked[next] = true; //Update as -1 to mark as picked
  }
  delete(marked);

  /******TESTING******
  // Print binary grid representation of pattern
  for(int i = 0;i<grid_size;i++){
      if(i%grid_length==0) Serial.println();
      Serial.print((pattern&(1LL<<i))>0);
  }
  Serial.println();
  */
  return pattern;
}


void updateLights(int pattern); // light up the board based on pattern given – sustains pattern for 3 seconds



void readInput(); // read the user input, light up the correspond LED and sustain it
                  //    output the corresponding binary value



bool checkPattern(long long input_pattern, long long pattern){ // check if inputted values is 
	return input_pattern==pattern;
}


void errorResponse(); // if user input is incorrect (checkPattern returns False), output "X" pattern on entire grid
void setScore(); // calculate and output arbitrary score (+1 if won, +0 if lost)
void checkTimeLimit(); //if time is up, output errorResponse (incorporate global timer that starts whenever output pattern is removed)





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication

}

void loop() {
  // put your main code here, to run repeatedly:
  level += 1;

}

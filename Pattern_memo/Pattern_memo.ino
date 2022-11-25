
/*****************************PIN DECLARATIONS*****************************/
#include <Wire.h>

#define SENSORPIN 0; //an example




/*****************************GLOBAL VARIABLES*****************************/
int current_pattern = 0;
int correct_pattern = 0;

int level = 0;
int grid_length = 2;
int grid_size = 4;

double EPS = 5; // TEMPORARY
double[] input_readings = {256, 511, 767, 1023};
int[] analogPinRows = {A0};


/************************HELPER FUNCTION PROTOTYPES************************/
void beginPattern(){ // light up all LEDs within size of the level dimensions to indicate the grid size the pattern will be created in
  int all_light_pattern = (1<<grid_size)-1;
  updateLights(all_light_pattern);
}

long long createRandomPattern(){ // output binary n-by-n matrix for pattern
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


void readInput(){ // read the user input, light up the correspond LED and sustain it
                  //    output the corresponding binary value
  int input_pattern = 0;
  for(int i = 0;i<1;i++){ //TEMPORARY replace 1 with grid_length
    val_row = analogRead(analogPinRows[i]);
    for(int j = 0;j<grid_length;j++){
      if(inRange(val_row, input_readings[j])){
        input_pattern = (1<<(i*grid_length)+j);
        break;
      }
    }
  }
  /******TESTING******
  //Output input binary
  Serial.println(input_pattern);
  */
  if(checkPattern(input_pattern, correct_pattern)){
    //Update lights
    current_pattern|=input_pattern;
    updateLights(current_pattern);
  }else{
    // Incorrect input animation here
  }
}
bool inRange(int reading, int value){
  return abs(reading-value)<=EPS;
}


bool checkPattern(long long input_pattern, long long correct_pattern){ // check if inputted values is 
  return input_pattern&correct_pattern!=0;
}


void errorResponse(); // if user input is incorrect (checkPattern returns False), output "X" pattern on entire grid
void setScore(); // calculate and output arbitrary score (+1 if won, +0 if lost)
void checkTimeLimit(); //if time is up, output errorResponse (incorporate global timer that starts whenever output pattern is removed)
void nextLevel(){ //move to the next level and update grid_length and grid_size accordingly
  level++;
  grid_length = (level/3)+2;
  grid_size = grid_length*grid_length;
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication

}

void loop() {
  // put your main code here, to run repeatedly:
  readInput();
}

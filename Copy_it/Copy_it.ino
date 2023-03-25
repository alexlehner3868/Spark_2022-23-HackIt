int selected_image_index = 0;
int current_user_x = 0;
int current_user_y = 0;
bool currently_playing = true;
bool start_game = false;

// Color Macros
#define N 0b0000 // N(o color)
#define R 0b0100
#define G 0b0010
#define B 0b0001
#define Y 0b0110 // Y(ellow)
#define C 0b0001 // C(yan)
#define M 0b0101 // M(agenta)
#define W 0b0111 // W(hite)


const int JOYSTICK_UP_PIN = 0;
const int JOYSTICK_DOWN_PIN = 1;
const int JOYSTICK_LEFT_PIN = 2;
const int JOYSTICK_RIGHT_PIN = 3;


const int RED_PIN = 4;
const int BLUE_PIN = 5;
const int GREEN_PIN = 6;

const int CHECK_BUTTON_PIN = 7;
const int DELETE_COLOR_PIN = 8;

// const int ARRAY_SIZE = 8;  
const int ARRAY_SIZE = 2;  
const int LATCH_PIN = 11;
const int CLOCK_PIN = 9;
const int DISPLAY_GRID_PIN = 12;
const int COPY_GRID_PIN = 8;

int updown = ARRAY_SIZE - 1;
int leftright = ARRAY_SIZE - 1;


int display_grid[ARRAY_SIZE][ARRAY_SIZE] = {{R, G},
                                            {B, G}};
int copy_grid[ARRAY_SIZE][ARRAY_SIZE] = {{B, G},
                                        {G, B}};
/*
int display_grid[ARRAY_SIZE][ARRAY_SIZE] = {{R, G, B, N, R, G, B, N},
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}};

int copy_grid[ARRAY_SIZE][ARRAY_SIZE] =    {{R, G, B, N, R, G, B, N},
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}, 
                                            {R, G, B, N, R, G, B, N}};
*/

int current_position_color = copy_grid[updown][leftright];
double time_last_flash;

// shift int grid values to shift registers
void setLED(int latch_pin, int clock_pin, int data_pin, int grid[][ARRAY_SIZE]) {
    digitalWrite(latch_pin, LOW);
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j += 2) {
            shiftOut(data_pin, clock_pin, latch_pin, (grid[i][j] << 4) + grid[i][j + 1]);
        }
    }
    
    digitalWrite(latch_pin, HIGH);
}

// Outputs grid to physical circuit
void show_image(int data_pin, int grid[][ARRAY_SIZE]){
    setLED(LATCH_PIN, CLOCK_PIN, data_pin, grid);
}

bool compare_images(){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            if (display_grid[i][j] != copy_grid[i][j]) return false;
        }
    }
    return true;
}

// Reset all of the leds on the output board and put the cursor in the top right again 
void clear_output(){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            copy_grid[i][j] = N;
        }
    }
    current_user_x = 0;
    current_user_y = 0;
}

void load_image(){
    // Select a random image from the array of images
    // Display the image on the image reference led grid 
}

void setup(){
    // Set up pins for shift registers
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DISPLAY_GRID_PIN, OUTPUT);
    pinMode(COPY_GRID_PIN, OUTPUT);
    // May need to change INPUT to INPUT_PULLUP
    // Setup joystick 
    pinMode(JOYSTICK_DOWN_PIN, INPUT_PULLUP);
    pinMode(JOYSTICK_UP_PIN, INPUT_PULLUP);
    pinMode(JOYSTICK_LEFT_PIN, INPUT_PULLUP);
    pinMode(JOYSTICK_RIGHT_PIN, INPUT_PULLUP);
    // Set up color buttons 
    pinMode(RED_PIN, INPUT_PULLUP);
    pinMode(GREEN_PIN, INPUT_PULLUP);
    pinMode(BLUE_PIN, INPUT_PULLUP);
    pinMode(CHECK_BUTTON_PIN, INPUT_PULLUP);
    time_last_flash = millis();

    Serial.begin(9600);

}

void move_up() {
   Serial.println("UP");
  updown--;
  if (updown == -1) {
    updown = ARRAY_SIZE - 1;
  }
}
void move_down() {
   Serial.println("DOWN");
  updown++;
  if (updown == ARRAY_SIZE) {
    updown = 0;
  }
}
void move_left() {
  Serial.println("LEFT");
  leftright--;
  if (leftright == -1) {
    leftright = ARRAY_SIZE - 1;
  }
}
void move_right() {
   Serial.println("RIGHT");
  leftright++;
  if (leftright == ARRAY_SIZE) {
    leftright = 0;
  }
}

void check_joystick_movement() {
  if (digitalRead(JOYSTICK_UP_PIN)) {
    // move_up();
  } else if (digitalRead(JOYSTICK_DOWN_PIN)) {
    move_down();
  } else if (digitalRead(JOYSTICK_LEFT_PIN)) {
    move_left();
  } else if (digitalRead(JOYSTICK_RIGHT_PIN)) {
    move_right();
  } else {
  }
}

void flash_current_location(){
    // flash the output led at current_user_x, current_user_y
    if ((millis() - time_last_flash ) > 500 || (millis() - time_last_flash) < 0) {
      if (copy_grid[leftright][updown] == current_position_color) {
        copy_grid[leftright][updown] = N;
        // Serial.println("Flash dark");
        // Serial.println(time_last_flash);
      } else {
        copy_grid[leftright][updown] = current_position_color;
        // Serial.println("Flash bright");
        // Serial.println(time_last_flash);
      }
      time_last_flash = millis();
    }
}

void check_for_color_change(){
    //check if a color button has been pressed
    // if yes, update the output led's color at current_user_x, current_user_y
    // if (digitalRead(RED_PIN) == LOW) {
    //     copy_grid[leftright][updown] = R;
    //     current_position_color = R;
    // }
    // if (digitalRead(BLUE_PIN)) {
    //     copy_grid[leftright][updown] = B;
    //     current_position_color = B;
    // }
    // if (digitalRead(GREEN_PIN)) {
    //     copy_grid[leftright][updown] = G;
    //     current_position_color = G;
    // }
    if (digitalRead(RED_PIN) == LOW) {
      // int current_time_diff = millis() - time_last_flash;
      while (digitalRead(RED_PIN) == LOW); //Wait for button to be released
      // time_last_flash = millis() + current_time_diff;
      /*
      Serial.print("button pressed: ");
      Serial.print(current_position_color);
      Serial.print( updown);
      Serial.print(leftright);
      Serial.println();
      */
      switch (current_position_color) {
       
        case R:
          copy_grid[leftright][updown] = G;
          current_position_color = G;
          break;
        case G:
          copy_grid[leftright][updown] = B;
          current_position_color = B;
          break;
        case B:
          copy_grid[leftright][updown] = R;
          current_position_color = R;
          break;
        
        default:
          break;
      }
    }
}

void check_for_image_verify(){
    // check if the verify button has been pressed.
    // if pressed -> compare_images() 
    if (digitalRead(CHECK_BUTTON_PIN)) {
        compare_images();
    }
}

void loop(){
  show_image(COPY_GRID_PIN, copy_grid);
  flash_current_location();
  check_for_color_change();
  check_joystick_movement();
  /*
  Serial.print("Printing position");
  Serial.print(updown);
  Serial.print(leftright);
  Serial.println("");
  */
  delay(100);
  /*
    if(start_game){
        clear_output();
        load_image();
        start_game = false;
        currently_playing = true;
    }

    if(currently_playing){
        show_image(DISPLAY_GRID_PIN, display_grid);
        show_image(COPY_GRID_PIN, copy_grid);
        check_joystick_movement();
        flash_current_location();
        check_for_color_change(); 
        check_for_image_verify();
    }
  */
}
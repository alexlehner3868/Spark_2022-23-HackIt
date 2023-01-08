// TODO 
// Brian -> set up real arrays 8x8, picture and output, 


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


const int JOYSTICK_UP = 0;
const int JOYSTICK_DOWN = 1;
const int JOYSTICK_LEFT = 2;
const int JOYSTICK_RIGHT = 3;


const int RED = 4;
const int BLUE = 5;
const int GREEN = 6;

const int CHECK_BUTTON = 7;
const int DELETE_COLOR = 8;

const int ARRAY_SIZE = 8;  
const int LATCH_PIN = 11;
const int CLOCK_PIN = 9;
const int DISPLAY_GRID_PIN = 12;
const int COPY_GRID_PIN = 8;
const int REG_NUM = ARRAY_SIZE * ARRAY_SIZE / 2; // Number of shift registers to be used per grid

int updown;
int leftright;

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

// Create byte array for shifting out
void gridToBytes(int grid[][ARRAY_SIZE], byte byte_array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j += 2) {
        byte_array[(i * ARRAY_SIZE + j) / 2] = ((grid[i][j] << 4) + grid[i][j + 1]);
        }
    }
}

// Shift out byte array to shift registers
void setLED(int latch_pin, int clock_pin, int data_pin, byte byte_array[]){
    digitalWrite(latch_pin, LOW);
    
    for (int i = 0; i < REG_NUM; i++) {
        shiftOut(data_pin, clock_pin, MSBFIRST, byte_array[i]);
    }
    
    digitalWrite(latch_pin, HIGH);
}

// Outputs grid to physical circuit
void show_image(int grid[][ARRAY_SIZE]){
    byte byte_array[REG_NUM];
    gridToBytes(grid, byte_array);
    setLED(LATCH_PIN, CLOCK_PIN, DATA_PIN, byte_array);
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
    // Setup joystick 
    // Set up color buttons 

}


void move_up() {
  updown--;
  if (updown == -1) {
    updown = 7;
  }
}
void move_down() {
  updown++;
  if (updown == 8) {
    updown = 0;
  }
}
void move_left() {
  leftright--;
  if (leftright == -1) {
    leftright = 7;
  }
}
void move_right() {
  leftright++;
  if (leftright == 8) {
    leftright = 0;
  }
}

void check_joystick_movement() {
  if (digitalRead(JOYSTICK_UP)) {
    move_up();
  } else if (digitalRead(JOYSTICK_DOWN)) {
    move_down();
  } else if (digitalRead(JOYSTICK_LEFT)) {
    move_left();
  } else if (digitalRead(JOYSTICK_RIGHT)) {
    move_right();
  } else {
  }
}

void flash_current_location(){
    // flash the output led at current_user_x, current_user_y
}

void check_for_color_change(){
    //check if a color button has been pressed
    // if yes, update the output led's color at current_user_x, current_user_y
}

void check_for_image_verify(){
    // check if the verify button has been pressed.
    // if pressed -> compare_images() 
}

void loop(){
    if(start_game){
        clear_output();
        load_image();
        start_game = false;
        currently_playing = true;
    }

    if(currently_playing){
        show_image(display_grid);
        show_image(copy_grid);
        check_joystick_movement();
        flash_current_location();
        check_for_color_change(); 
        check_for_image_verify();
    }
}



/*** TEMPORARY holding for patterns
* patterns are 8x8 and use only 3 colors each
* given that the buttons are blue+red+green, the colors will 
* each [] is one "pixel" and holds info for red, green, and blue
* the array goes left to right, top to bottom
* [R, G, B]
* empty array means [0,0,0]
* R means [1, 0, 0]
* G means [0, 1, 0]
* B means [0, 0, 1]
* Y(ellow) means [1, 1, 0]
* C(yan) means [0, 1, 1]
* M(agenta) means [1, 0, 1]
* W(hite) means [1, 1, 1]
// apple

heart_pattern = [
  [], [], [], [], [], [], [], [],
  [], R, [R], [], [R], [R], [], [],
  [R], [W], [M], [R], [R], [R], [R], [],
  [R], [M], [R], [R], [R], [M], [R], [],

  [], [R], [R], [R], [M], [R], [], [],
  [], [], [R], [R], [R], [], [], [],
  [], [], [], [R], [], [], [], [],
  [], [], [], [], [], [], [], []
]
key_pattern = [
  [], [], [W], [Y], [Y], [], [], [],
  [], [W], [], [], [], [Y], [], [],
  [], [W], [], [], [], [Y], [], [],
  [], [], [Y], [Y], [Y], [], [], [],

  [], [], [], [Y], [], [], [], [],
  [], [], [], [Y], [Y], [], [], [],
  [], [], [], [Y], [], [], [], [],
  [], [], [], [Y], [Y], [], [], []
]
skull_pattern = [
  [], [], [], [], [], [], [], [],
  [], [W], [W], [W], [W], [W], [], [],
  [W], [], [], [W], [], [], [W], [],
  [W], [], [R], [W], [], [R], [W], [],

  [W], [W], [W], [W], [W], [W], [W], [],
  [W], [W], [W], [], [W], [W], [W], [],
  [], [W], [W], [W], [W], [W], [], [],
  [], [W], [], [W], [], [W], [], []
]
lock_pattern = [
  [], [], [W], [W], [W], [], [], [],
  [], [W], [], [], [], [W], [], [],
  [], [Y], [], [], [], [Y], [], [],
  [Y], [Y], [Y], [Y], [Y], [Y], [Y], [],

  [Y], [Y], [Y], [], [Y], [Y], [Y], [],
  [Y], [Y], [Y], [], [Y], [Y], [Y], [],
  [Y], [Y], [Y], [Y], [Y], [Y], [Y], [],
  [], [Y], [Y], [Y], [Y], [Y], [], []
]
flask_pattern = [
  [], [], [W], [W], [W], [W], [], [],
  [], [], [], [W], [W], [], [], [],
  [], [], [], [W], [W], [], [], [],
  [], [], [W], [B], [B], [W], [], [],

  [], [W], [B], [B], [B], [B], [W], [],
  [W], [B], [B], [B], [B], [B], [B], [W],
  [], [W], [W], [W], [W], [W], [W], [],
  [], [], [], [], [], [], [], []
]
moon_pattern = [
  [], [], [W], [W], [W], [W], [], [],
  [], [W], [W], [W], [W], [W], [W], [],
  [W], [W], [W], [W], [], [], [], [],
  [W], [W], [W], [], [], [], [], [],

  [W], [W], [W], [], [], [], [], [],
  [W], [W], [W], [W], [], [], [], [],
  [], [W], [W], [W], [W], [W], [W], [],
  [], [], [W], [W], [W], [W], [], []
]
gun_pattern = [
  [R], [R], [R], [R], [R], [R], [R], [R],
  [R], [ ], [ ], [ ], [ ], [ ], [ ], [R],
  [R], [ ], [R], [R], [R], [R], [R], [R],
  [R], [ ], [R], [ ], [R], [ ], [ ], [ ],
  [R], [ ], [R], [R], [R], [ ], [ ], [ ],
  [R], [ ], [R], [ ], [ ], [ ], [ ], [ ],
  [R], [ ], [R], [ ], [ ], [ ], [ ], [ ],
  [R], [R], [R], [ ], [ ], [ ], [ ], [ ]
]
magnifying_glass_pattern = [
  [ ], [W], [W], [W], [ ], [ ], [ ], [ ],
  [W], [ ], [ ], [ ], [W], [ ], [ ], [ ], 
  [W], [ ], [ ], [ ], [W], [ ], [ ], [ ], 
  [W], [ ], [ ], [ ], [W], [ ], [ ], [ ], 
  [W], [ ], [ ], [ ], [W], [ ], [ ], [ ], 
  [ ], [W], [W], [W], [ ], [W], [ ], [ ],
  [ ], [ ], [ ], [ ], [ ], [ ], [W], [ ],
  [W], [ ], [ ], [ ], [ ], [ ], [ ], [W]
]
key_pattern = [
  [ ], [ ], [ ], [W], [W], [ ], [ ], [ ],
  [ ], [ ], [W], [ ], [ ], [W], [ ], [ ],
  [ ], [ ], [W], [ ], [ ], [W], [ ], [ ],
  [ ], [ ], [ ], [W], [W], [ ], [ ], [ ],
  [ ], [ ], [ ], [W], [W], [ ], [ ], [ ],
  [ ], [ ], [ ], [W], [W], [ ], [ ], [ ],
  [ ], [ ], [ ], [W], [W], [W], [ ], [ ],
  [ ], [ ], [ ], [W], [W], [W], [ ], [ ]
]
// key 


*/
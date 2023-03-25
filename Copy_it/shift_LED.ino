// This program contains functions for bitshifting a 2D grid of LEDs
// The LED grid is represented by a 2D int array, which is converted to a 1D byte array. 
// The 1D byte array is used to shift out bits with shift registers

// Several assumptions are made:
// 1. Grid dimensions are even numbers;
// 2. LEDs are represented by 4 bits in the form of 0rgb. 
// 3. The 2D int array is mapped to the 1D byte array in the following fashion:
//        Eg. (4x4 grid)
//        00 01 02 03              0    1
//        10 11 12 13       ->     2    3
//        20 21 22 23              4    5
//        30 31 32 33              6    7
//        The actual circuit will be Arduino - Shift Reg 7 - SR6 - SR5 - ... - SR0
//        Note that the shift register closest to the arduino will display the last byte in the array
//        Each SR will display 1 byte (0rgb0rgb), the LED with the smaller col num is on the right.
// 4. LED to register output connection is as follows:
//        0rgb0rgb
//        76543210
 
// const int LATCH_PIN = 11;
// const int CLOCK_PIN = 9;
// const int DATA_PIN = 12;
// const int OUTPUT_PIN = 8;

// const int ROW_NUM = 2;
// const int COL_NUM = ROW_NUM;
// const int BYTE_NUM = ROW_NUM * ROW_NUM / 2; // Number of bytes to be shifted out aka length of byte array

// // LED_grid variable is for testing and demo purposes
// int LED_grid[ROW_NUM][COL_NUM] = {{0b0111, 0b0010}, {0b0001, 0b0100}};
// byte byte_array[BYTE_NUM];
// //for grid

// // gridToBytes function converts 2D int array into 1D byte array
// // COL_NUM should be used as grid dimension, 2 is used here due to tinkedcad limitations
// // Note that gridToBytes asks for 2 input, the grid and an empty byte array for output
// void gridToBytes(int grid[][2], byte byte_array[]) {
//   for (int i = 0; i < ROW_NUM; i++) {
//     for (int j = 0; j < COL_NUM; j += 2) {
//       byte_array[(i * ROW_NUM + j) / 2] = ((grid[i][j] << 4) + grid[i][j + 1]);
//     }
//   }
// }

// // setLED function takes in the 3 pins and byte array to shift out all the bits
// void setLED(int latch_pin, int clock_pin, int data_pin, byte byte_array[]){
//   digitalWrite(latch_pin, LOW);
  
//   for (int i = 0; i < BYTE_NUM; i++) {
//     shiftOut(data_pin, clock_pin, MSBFIRST, byte_array[i]);
//   }
  
//   digitalWrite(latch_pin, HIGH);
// }

// // setup and loop is mainly for testing and demo purposes


// void show_image(){
//   gridToBytes(LED_grid, byte_array);
//   setLED(LATCH_PIN, CLOCK_PIN, DATA_PIN, byte_array);
  
//   for (int i = 0; i < ROW_NUM; i++) {
//     for (int j = 0; j < ROW_NUM; j++) {
//       LED_grid[i][j] = (LED_grid[i][j] + 1) % 0b111;
//     }
//   }
//   delay(1000);
// }
// /*
// void setup()
// {
//   pinMode(LATCH_PIN, OUTPUT);
//   pinMode(CLOCK_PIN, OUTPUT);
//   pinMode(DATA_PIN, OUTPUT);
//   updown = 0;
//   leftright = 0;
// }
// void loop()
// {
  
// }
// */
#include <FastLED.h>

// CONSTANTS/GLOBAL DECLARATIONS
struct CRGB leds[24];
CRGB *pastLed = NULL;
int delaySpeed = 175;
int currLed = 0;
bool clockwise = true;
int randElement;

void setup() {
  LEDS.addLeds<WS2812B, 11, GRB>(leds, 24);
  pinMode(12, INPUT_PULLUP);

  Serial.begin(9600);
  randomSeed(analogRead(0));
  randElement = random(0,24);
}

// Function to select a new random target led
void reset() {
  leds[randElement] = CRGB::Black;
  FastLED.show();
  randElement = random(0,24);
  Serial.println(randElement);
  clockwise = !clockwise;
}

// Function to run clockwise/left to right direction
void clockwiseCycle() {

  // Local variables
  long checkTime = 0;
  long currTime = 0;
  bool repeat = true;

  for (int i = currLed; i < 24; i ++) {
    currTime = millis();
    // Indicate which led is currently selected
    // Vary indication based on if target led is selected
    if (i == randElement) {
      leds[i] = CRGB::LawnGreen;
      checkTime = millis();
    } else {
      leds[i] = CRGB::Blue;
    }

    // Return previous led to its non-selected colour
    if (pastLed != NULL) {
      if (*pastLed == leds[randElement]) {
        *pastLed = CRGB::Yellow;
      } else {
        *pastLed = CRGB::Black;
      }
    }
    pastLed = &leds[i];
    FastLED.show();

    while(millis() < currTime + delaySpeed) {
      // Check if user input was instated during correct time frame
      if ((millis() - checkTime <= delaySpeed) && digitalRead(12) == LOW) {
        Serial.println("pressed");
        reset();
        // Adjust trackers
        currLed = i;
        checkTime = 0;
        repeat = false;
        break;
      }
    }
    if (!repeat) {
      break;
    }
  }

  // Reset index if target was not correctly pressed
  if (repeat) {
    currLed = 0;
  }
}

// Function to run counterclockwise/right to left direction
void counterclockwiseCycle() {

  // Local variables
  long checkTime = 0;
  long currTime = 0;
  bool repeat = true;

  for (int i = currLed; i >= 0; i --) {
    currTime = millis();
    // Indicate which led is currently selected
    // Vary indication based on if target led is selected
    if (i == randElement) {
      leds[i] = CRGB::LawnGreen;
      checkTime = millis();
    } else {
      leds[i] = CRGB::Blue;
    }

    // Return previous led to its non-selected colour
    if (pastLed != NULL) {
      if (*pastLed == leds[randElement]) {
        *pastLed = CRGB::Yellow;
      } else {
        *pastLed = CRGB::Black;
      }
    }
    pastLed = &leds[i];
    FastLED.show();

    while(millis() < currTime + delaySpeed) {
      // Check if user input was instated during correct time frame
      if ((millis() - checkTime <= delaySpeed) && digitalRead(12) == LOW) {
        Serial.println("pressed");
        reset();
        // Adjust trackers
        currLed = i;
        checkTime = 0;
        repeat = false;
        break;
      }
    }
    if (!repeat) {
      break;
    }
  }
  
  // Reset index if target was not correctly pressed
  if (repeat) {
    currLed = 23;
  }
}

void loop() {
  leds[randElement] = CRGB::Yellow;
  FastLED.show();
  if (clockwise) { 
    clockwiseCycle();
  } else {
    counterclockwiseCycle();
  }
}


// State machine and display settings
///////////////////////////////////////////////////////////////////////////////////
enum State {
   ON,
   PLAYING,
   DEBUG,
   WAKEUP,
   SLEEP,
   INSLEEP
};

int globalState = INSLEEP;

enum InputCommands {
  CLEAR,
  CENTER,
  RIGHT,
  LEFT,
  TOP,
  DOWN,
  MENU,
  PLAY
};

int inputCommand = CLEAR;


volatile unsigned char displayFramerateDivider;

#define FPS_15  0x0F  // 0x0F means 66 miliseconds in between frames, so 15 frames a second
#define FPS_30  0x07  // 0x07 means 33 miliseconds in between frames, 30 frames a second
#define FPS_60  0x03  // 0x03 means 16 or 17 miliseconds in between frames so 60 frames a second

long countdownFrames = 0;



// IR Remote
///////////////////////////////////////////////////////////////////////////////////
#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;



// LED Strip
///////////////////////////////////////////////////////////////////////////////////
#include <FastLED.h>
#define LEDS_NUM          18
#define LEDS_NUM_MIDDLE   9

#define LEDS_DATA         5
#define LEDS_CLOCK        4
#define LEDS_BRIGHTNESS_1   80
#define LEDS_BRIGHTNESS_2   130
#define LEDS_BRIGHTNESS_3   200
#define LEDS_BRIGHTNESS_4   255
#define FRAMES_PER_SECOND 60


#define BRIGHT_MAX  180
#define BRIGHT_MIN  0
#define DOWN -5
#define UP    5

//#define BIGGER    1
//#define SMALLER  -1

//int leds_brightness = 100;
//int eeprom_addr_brightness = 0x00; //0x00;
#define BRIGHT_LEVEL_NUM  6
int brightnessLevels[BRIGHT_LEVEL_NUM] = {0,20,50,80,100,160};
int brightLevel = BRIGHT_LEVEL_NUM - 1;


CRGB leds[LEDS_NUM];


/*
#define ADVANCE 1
#define RETURN -1
#define SCENEMAX 3

int sceneNum = 0;
*/


// Debug LED
///////////////////////////////////////////////////////////////////////////////////
#define DEBUG_LED		A0 //13
#define DEBUG_ENABLED

//#define debug(a)                      // enable this one if debug is off
#define debug(a) (Serial.println(a))  // enable this one if debug is on

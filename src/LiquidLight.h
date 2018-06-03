

// State machine and display settings
///////////////////////////////////////////////////////////////////////////////////
enum State {
   WAITING,
   PLAYING,
   DEBUG
};

int globalState = WAITING;

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
#define LEDS_NUM          10

#define LEDS_DATA         5
#define LEDS_CLOCK        4
#define LEDS_BRIGHTNESS_1   80
#define LEDS_BRIGHTNESS_2   130
#define LEDS_BRIGHTNESS_3   200
#define LEDS_BRIGHTNESS_4   255
#define FRAMES_PER_SECOND 60

int leds_brightness;
int eeprom_addr_brightness = 0x00;
CRGB leds[LEDS_NUM];



// Debug LED
///////////////////////////////////////////////////////////////////////////////////
#define DEBUG_LED		13
#define DEBUG_ENABLED

//#define debug(a)                      // enable this one if debug is off
#define debug(a) (Serial.println(a))  // enable this one if debug is on

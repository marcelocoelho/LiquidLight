



// LED Strip
///////////////////////////////////////////////////////////////////////////////////
#include <FastLED.h>
#define LEDS_NUM          3

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

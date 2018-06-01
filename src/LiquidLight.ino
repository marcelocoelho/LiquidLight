
#include "LiquidLight.h"





void setup() {


  #ifdef DEBUG_ENABLED
  initSerial();
  #endif


  initLEDStrip();

  LEDStripFullOn();

}





/*//////////////////////////////////////////////////////////////////////////////////
    DEBUG
//////////////////////////////////////////////////////////////////////////////////*/
void initSerial() {
  Serial.begin(115200);
  //delay(3000);
  debug("Liquid Light v1.0");
}


/*//////////////////////////////////////////////////////////////////////////////////
    LED STRIP
//////////////////////////////////////////////////////////////////////////////////*/
void initLEDStrip()
{
  FastLED.addLeds<APA102, LEDS_DATA, LEDS_CLOCK, BGR>(leds, LEDS_NUM);
  //leds_brightness = EEPROM.read(eeprom_addr_brightness);
  //if (leds_brightness == 0x00) leds_brightness = LEDS_BRIGHTNESS_4;
	//FastLED.setBrightness( leds_brightness );
	LEDStripFullOff();
}

void LEDStripFullOn()
{
  for (int j = 0; j < LEDS_NUM; j++)
	{
    leds[j] = CRGB(255);
  }
  FastLED.show();
  FastLED.show();
}

void LEDStripFullOff()
{
  for (int j = 0; j < LEDS_NUM; j++)
	{
    leds[j] = CRGB(0);
  }
  FastLED.show();
  FastLED.show();
}





/*//////////////////////////////////////////////////////////////////////////////////
    LOOP
//////////////////////////////////////////////////////////////////////////////////*/
void loop()
{
  // does nothing

}

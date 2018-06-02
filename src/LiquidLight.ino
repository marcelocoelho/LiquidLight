
#include "LiquidLight.h"





void setup() {


  #ifdef DEBUG_ENABLED
  initSerial();
  #endif

  irrecv.enableIRIn(); // Start the receiver

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



void getInput() {

  if (irrecv.decode(&results)) {

    unsigned long command; //stores the latest input command

    command = results.value;

    //Serial.println(results.value, HEX);
    //Serial.println(results.value);

    switch (command) {
      case 2011249228:  //CENTER
        Serial.println("center");
        //displayAnimation();
      break;

      case 2011254860: // TOP
        Serial.println("top");
        break;

      case 2011258956: // RIGHT
        Serial.println("right");
        break;

      case 2011271244: // LEFT
        Serial.println("left");
        break;

      case 2011246668: // BOTTOM
        Serial.println("bottom");
        break;

      case 2011283532: // MENU
        Serial.println("menu");
        break;

      case 2011298380: // PLAY
        Serial.println("play");
        break;

      default:
        //Serial.println(command);
        break;
    }

    irrecv.resume(); // Receive the next value
  }


}



/*//////////////////////////////////////////////////////////////////////////////////
    LOOP
//////////////////////////////////////////////////////////////////////////////////*/
void loop()
{
  // does nothing
  getInput();

}

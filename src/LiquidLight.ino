
// FOR SOME REASON, MAIN INTERRUPT ROUTINE STOPPED RUNNING AND IR STOPPED RUNNING AS WELL

#include "LiquidLight.h"



void setup() {

  initDebugLED();

  #ifdef DEBUG_ENABLED
  initSerial();
  #endif

  irrecv.enableIRIn(); // Start the receiver

  initLEDStrip();

  globalState = WAKEUP;

  displayStartFrameInterrupt();

}



/*//////////////////////////////////////////////////////////////////////////////////
    TIMER INTERRUPT AND MAIN ROUTINES
    Time gets called repeatedly, every 4 ms.
//////////////////////////////////////////////////////////////////////////////////*/
ISR(TIMER1_OVF_vect) {

  //debugOn();
  //debugOff();

  // GO GET INPUT
  getInput();

  // THEN DEAL WITH OUTPUT
  displayFramerateDivider = (++displayFramerateDivider) & FPS_30; // this counts from 0 incrementally by 1

  if(displayFramerateDivider == 0)   // this counts frames
  {

    if (countdownFrames > 0) {            // If there is a time, count down to zero
      countdownFrames--;
    } else if (countdownFrames == 0) {   // When it gets to 0, then play animation
      setDisplay();
    } else if (countdownFrames < 0) {   // But if it's -1, then ignore this animation and don't play anything
      // do nothing
    }
  }
}



/*//////////////////////////////////////////////////////////////////////////////////
    TIMER INTERRUPTS
//////////////////////////////////////////////////////////////////////////////////*/

//
// displayStartFrameInterrupt() : Sets up the microcontroller to interrupt when Timer1 overflows.
//
void displayStartFrameInterrupt()
{
   TIMSK1 = _BV(TOIE1);
   //sei();
   TCCR1B |= 0x02;

   sei();
}


//
// displayStopFrameInterrupt() : Keeps the microcontroller from interrupting on Timer1 overflow.
//
void displayStopFrameInterrupt()
{
   TIMSK1 = ~_BV(TOIE1);
}




/*//////////////////////////////////////////////////////////////////////////////////
    DEBUG
//////////////////////////////////////////////////////////////////////////////////*/
void initSerial() {
  Serial.begin(115200);
  //delay(3000);
  debug("Liquid Light v1.0");
}

void initDebugLED()
{
	pinMode(DEBUG_LED, OUTPUT);
	debugOff();
}

void debugOn()
{
	digitalWrite(DEBUG_LED, HIGH);
}


void debugLow() {
  digitalWrite(DEBUG_LED, LOW);
}

void debugOff()
{
  digitalWrite(DEBUG_LED, LOW);
}

void debugFlicker() {
  digitalWrite(DEBUG_LED, HIGH);
  delay(5);
  digitalWrite(DEBUG_LED, LOW);
}


/*//////////////////////////////////////////////////////////////////////////////////
    LED STRIP
//////////////////////////////////////////////////////////////////////////////////*/
void initLEDStrip()
{
  FastLED.addLeds<APA102, LEDS_DATA, LEDS_CLOCK, BGR>(leds, LEDS_NUM);
  //leds_brightness = EEPROM.read(eeprom_addr_brightness);
  //if (leds_brightness == 0x00) leds_brightness = LEDS_BRIGHTNESS_4;
	FastLED.setBrightness( leds_brightness );
	LEDStripFullOff();
}

void LEDStripFullOn()
{
  for (int j = 0; j < LEDS_NUM; j++)
	{
    leds[j] = CRGB(255);
  }
  FastLED.show();
  //FastLED.show();
}

void LEDStripFullOff()
{
  for (int j = 0; j < LEDS_NUM; j++)
	{
    leds[j] = CRGB(0);
  }
  FastLED.show();
  //FastLED.show();
}


/*//////////////////////////////////////////////////////////////////////////////////
    GET INPUT
    This runs as much as possible so we don't lose remote input
//////////////////////////////////////////////////////////////////////////////////*/
void getInput() {

  if (irrecv.decode(&results)) {

    unsigned long command; //stores the latest input command

    command = results.value;

    //Serial.println(results.value, HEX);
    //Serial.println(results.value);

    switch (command) {
      case 2011249228:  //CENTER
        Serial.println("center");
        inputCommand = CENTER;
      break;

      case 2011254860: // TOP
        Serial.println("up");
        inputCommand = UP;
        break;

      case 2011258956: // RIGHT
        Serial.println("right");
        inputCommand = RIGHT;
        //changeBrightness(UP);
        break;

      case 2011271244: // LEFT
        Serial.println("left");
        inputCommand = LEFT;
        //changeBrightness(DOWN);
        break;

      case 2011246668: // BOTTOM
        Serial.println("down");
        inputCommand = DOWN;
        break;

      case 2011283532: // MENU
        Serial.println("menu");
        inputCommand = MENU;
        //globalState = PLAYING;
        break;

      case 2011298380: // PLAY
        Serial.println("play");
        inputCommand = PLAY;
        break;

      default:
        //Serial.println(command);
        break;
    }

    irrecv.resume(); // Receive the next value
  }


}



/*//////////////////////////////////////////////////////////////////////////////////
    DISPLAY LOGIC
    This decides what to do with input: change state, change properties, etc
//////////////////////////////////////////////////////////////////////////////////*/

int positionCounter = 0;
int slower = 0; // weird hack to slow down animation by skipping frames

void setDisplay() {

  // regardless of state, adjust brigthness when needed
  /////////////////////////////////////////////////////
  if (inputCommand == UP) {
    inputCommand = CLEAR;
    changeBrightness(UP);
  }

  if (inputCommand == DOWN) {
    inputCommand = CLEAR;
    changeBrightness(DOWN);
  }


  // Now go work on states
  /////////////////////////////////////////////////////
  switch(globalState) {
    case ON:

      if (inputCommand == CENTER) {
        inputCommand = CLEAR;
        globalState = SLEEP;
      }


      break;

    case WAKEUP:
      wakeup();
      break;

    case SLEEP:
      sleep();
      break;

    case INSLEEP:
      // do nothing, mostly

      if (inputCommand == CENTER) {
        inputCommand = CLEAR;
        globalState = WAKEUP;
      }
      break;

    case PLAYING:
      playing();
      break;

    default:
      break;

  }
}


/*//////////////////////////////////////////////////////////////////////////////////
    FUNCTIONS FOR DIFFERENT STATES
//////////////////////////////////////////////////////////////////////////////////*/
void playing() {

    slower++;

    if (slower > 100) {

      for (int i = 0; i < LEDS_NUM; i++) {    //clear strip
        leds[i] =  CRGB(0);
      }

      leds[positionCounter] =  CRGB(255);
      positionCounter++;

      if(positionCounter >= LEDS_NUM - 1) {
        positionCounter = 0;
        globalState = ON;
      }

      FastLED.show();

      slower = 0;
    }
}



void wakeup() {

  slower++;

  if (slower > 5) {

    leds[LEDS_NUM_MIDDLE + positionCounter] =  CRGB(255);
    leds[LEDS_NUM_MIDDLE - positionCounter] =  CRGB(255);
    positionCounter++;

    if(positionCounter >= LEDS_NUM_MIDDLE - 1) {
      positionCounter = 0;
      globalState = ON;
    }

    FastLED.show();

    slower = 0;
  }
}


void sleep() {

  slower++;

  if (slower > 5) {

    Serial.println(positionCounter);

    leds[positionCounter] =  CRGB(0);
    leds[LEDS_NUM - positionCounter] =  CRGB(0);
    positionCounter++;

    if(positionCounter > LEDS_NUM_MIDDLE) {
      positionCounter = 0;
      globalState = INSLEEP;
    }

    FastLED.show();

    slower = 0;
  }
}



void changeBrightness(int _value) {

  leds_brightness = leds_brightness + _value;     // set new value


  if (leds_brightness >= BRIGHT_MAX)
    leds_brightness = BRIGHT_MAX;

  if (leds_brightness <= BRIGHT_MIN)
    leds_brightness = BRIGHT_MIN;

  Serial.println(leds_brightness);

  FastLED.setBrightness( leds_brightness );     // display
  FastLED.show();

}









/*//////////////////////////////////////////////////////////////////////////////////
    LOOP
//////////////////////////////////////////////////////////////////////////////////*/
void loop()
{
  // does nothing
  //getInput();

}

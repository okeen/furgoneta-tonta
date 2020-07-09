
#define NUM_LEDS    26
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 8

#define NORMAL_MODE 0
#define RESCUE_MODE 1
#define PARTY_MODE 2
#define OFF_MODE 3

# define BLUE_COLOR 160
# define RED_COLOR 0
# define YELLOW_COLOR 64
# define GREEN_COLOR 96
# define ORANGE_COLOR 32

# define NUMBER_OF_COLORS 26
#define MAX_POWER_MILLIAMPS 500

byte ledMode = NORMAL_MODE;

CRGB frontLeds[5];
CRGB rearLeftLeds[2];
CRGB rearRightLeds[2];
CRGB aroundLeds[NUM_LEDS];

byte baseColorIndex = 0;
bool needsUpdate = true;

int baseColor;

void initLeds() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(aroundLeds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, FRONT_LED_PIN, COLOR_ORDER>(frontLeds, 5).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, REAR_LEFT_LED_PIN, COLOR_ORDER>(rearLeftLeds, 2).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, REAR_RIGHT_LED_PIN, COLOR_ORDER>(rearRightLeds, 2).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);

  baseColor = CRGB::Red;
  ledsTimer.every(1000 / UPDATES_PER_SECOND, incrementBaseColorIndex);

  # if defined(DEBUG_MODE)
    Serial.println("LEDS: Init OK");
  # endif
}

void switchLeds() {
  if (ledMode != OFF_MODE) {
    ledMode = OFF_MODE;
  } else {
    ledMode = NORMAL_MODE;
  }
  
  # if defined(DEBUG_MODE)
    Serial.print("LEDS: Power -> ");
    Serial.println(ledMode != OFF_MODE);
  # endif
}

void blinkLeftLED() {
  # if defined(DEBUG_MODE)
    Serial.println("LEDS: Blink Left");
  # endif
  static bool leftLedStatus = false;
  leftLedStatus = !leftLedStatus;

}

void blinkRightLED() {
  # if defined(DEBUG_MODE)
    Serial.println("LEDS: Blinking Right");
  # endif

  static bool ledStatus = false;
  ledStatus = !ledStatus;
}

void updateLeds() { 
  // Do nothing if no state change and nothing else happened
  if ((lastJoystickState == joystickState) && (lastModesState == modesState) && (lastControlsState == controlsState) && !needsUpdate) { 
    # if defined(DEBUG_MODE)
      Serial.println("LEDS: Nothing to update");
    # endif        
  
    return;
  }

  # if defined(DEBUG_MODE)
    Serial.println("LEDS: Updating");
  # endif
  
  if (ledMode == OFF_MODE) {
    turnOffLights();
    return;
  }

  if (joystickState == ST_IDLE) {
    setFrontLeds(CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White);
    setRearLeds(CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red);
    lightAroundLeds(baseColor);

  } else  { 
    if (joystickState == ST_MOVING_FORWARD) {
      setFrontLeds(CRGB::White,CRGB::Black,CRGB::Green,CRGB::Black,CRGB::White);
      setRearLeds(CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red);
  
    } else if (joystickState == ST_MOVING_BACKWARDS) {
      setFrontLeds(CRGB::Red,CRGB::Black,CRGB::Red,CRGB::Black,CRGB::Red);
      setRearLeds(CRGB::White, CRGB::Red, CRGB::Red, CRGB::White);
  
    } else if (joystickState == ST_MOVING_LEFT) {
      setFrontLeds(CRGB::Orange, CRGB::White, CRGB::Green, CRGB::White, CRGB::White);
      setRearLeds( CRGB::Orange, CRGB::Red, CRGB::Red, CRGB::Red);
  
    } else if (joystickState == ST_MOVING_RIGHT) {
      setFrontLeds(CRGB::White, CRGB::White, CRGB::Green, CRGB::White, CRGB::Orange);
      setRearLeds( CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Orange);
  
    } else if (joystickState == ST_TURNING_LEFT) {
      setFrontLeds(CRGB::Orange, CRGB::Orange, CRGB::White, CRGB::White, CRGB::White);
      setRearLeds(CRGB::Orange, CRGB::Orange, CRGB::Red, CRGB::Red);
  
    } else if (joystickState == ST_TURNING_RIGHT) {
      setFrontLeds(CRGB::White, CRGB::White, CRGB::White, CRGB::Orange, CRGB::Orange);
      setRearLeds(CRGB::Orange, CRGB::Red, CRGB::Orange, CRGB::Red);
  
    } else if (joystickState == ST_MOVING_LEFT_BACKWARDS) {
      setFrontLeds(CRGB::Orange, CRGB::Orange, CRGB::Red, CRGB::Red, CRGB::Red);
      setRearLeds( CRGB::Orange, CRGB::Red, CRGB::Red, CRGB::Red);
  
    } else if (joystickState == ST_MOVING_RIGHT_BACKWARDS) {
      setFrontLeds(CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Orange, CRGB::Orange);
      setRearLeds( CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Orange);  
    }
    lightAroundLeds(CRGB::Black);
  }  

  lastJoystickState = joystickState;
  lastModesState = modesState;
  
  FastLED.show();
  needsUpdate = false;
}

void fadeall() {
  for (byte i = 0; i < 5; i++) {
    aroundLeds[i].nscale8(250);
  }
}

void setFrontLeds(CRGB led0, CRGB led1, CRGB led2, CRGB led3, CRGB led4) {
  frontLeds[0] = led0;
  frontLeds[1] = led1;
  frontLeds[2] = led2;
  frontLeds[3] = led3;
  frontLeds[4] = led4;
}

void setRearLeds(CRGB led0, CRGB led1, CRGB led2, CRGB led3) {
  rearLeftLeds[0] = led0;
  rearLeftLeds[1] = led1;
  rearRightLeds[0] = led2;
  rearRightLeds[1] = led3;
}

void turnOffLights() {
  frontLeds[0] = CRGB::Black;
  frontLeds[1] = CRGB::Black;
  frontLeds[2] = CRGB::Black;
  frontLeds[3] = CRGB::Black;
  frontLeds[4] = CRGB::Black;

  rearLeftLeds[0] = CRGB::Black;
  rearLeftLeds[1] = CRGB::Black;
  rearRightLeds[0] = CRGB::Black;
  rearRightLeds[1] = CRGB::Black;

  lightAroundLeds(CRGB::Black);
  FastLED.show();
}

void switchLedMode() {
  # if defined(DEBUG_MODE)
    Serial.print("LEDS mode -> ");
  # endif

  if (bitRead(modesState, 0)) {
    // Yellow mode
    baseColor = YELLOW_COLOR;

  # if defined(DEBUG_MODE)
      Serial.println("YELLOW");
  # endif

  } else if (bitRead(modesState, 1)) {
    // Red mode
    baseColor = RED_COLOR;

  # if defined(DEBUG_MODE)
      Serial.println("RED");
  # endif

  } else if (bitRead(modesState, 2)) {
    // Red mode
    baseColor = GREEN_COLOR;

  # if defined(DEBUG_MODE)
      Serial.println("GREEN");
  # endif

  } else {
    // Blue mode
    baseColor = BLUE_COLOR;

  # if defined(DEBUG_MODE)
      Serial.println("BLUE");
  # endif
  }

  ledMode = NORMAL_MODE;
}

void lightAroundLeds(CRGB color) {
  byte delta = 255 / NUM_LEDS;
  byte rescueColorIndex;
  byte normalColorIndex;
  
  for (byte i = 0; i < NUM_LEDS; i++) {
        
    switch (ledMode) {
      case PARTY_MODE:
        aroundLeds[i] = CHSV(baseColor + baseColorIndex * delta + i * delta, 255, 255);    
        break;  
      case OFF_MODE:
        aroundLeds[i] = CRGB::Black;    
        break;    
      case RESCUE_MODE:
        rescueColorIndex = (i + baseColorIndex) % 2; 
        aroundLeds[i] = rescueColorIndex == 0 ? CHSV(baseColor,255,255) : CHSV(0, 0, 255);
        break;    
      case NORMAL_MODE:
        normalColorIndex = (i + baseColorIndex) % 4; 
        aroundLeds[i] = normalColorIndex == 0 ? CHSV(baseColor,255,255) : normalColorIndex == 2 ? CHSV(0, 0, 255) : CHSV(0, 0, 0);    
       //aroundLeds[i] = CHSV(baseColor, 255, 255).fadeLightBy(baseColorIndex * delta + i * delta);    
    }    
  }
  
}

void setLedsRescueMode(bool state) {
  # if defined(DEBUG_MODE)
    Serial.print("LEDS: rescue mode -> ");
    Serial.println(state);
  # endif
  
  if (state) {
    baseColor = ORANGE_COLOR;
    ledMode = RESCUE_MODE;
  }
}

void setLedsPartyMode(bool state) {
  # if defined(DEBUG_MODE)
    Serial.print("LEDS: party mode -> ");
    Serial.println(state);
  # endif
    
  if (state) {
    ledMode = PARTY_MODE;
  }
}

void incrementBaseColorIndex() {
  baseColorIndex = (baseColorIndex + 1) % NUMBER_OF_COLORS;
  
  # if defined(DEBUG_MODE)
    Serial.print("LEDS: Increment Base Color Index to ");
    Serial.println(baseColorIndex);
  # endif

  needsUpdate = true;
  return true;
}

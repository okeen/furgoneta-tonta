// Controller Buttons positions in radio datagrams
#define YELLOW_BUTTON  0
#define RED_BUTTON     1
#define GREEN_BUTTON   2
#define BLUE_BUTTON    3
#define OPTIONS_BUTTON 4
#define SW_BUTTON      5 

// Actions triggered and their respective buttons
#define SOUND_BUZZER  YELLOW_BUTTON
#define LIGHTS_SWITCH BLUE_BUTTON
#define RESCUE_MODE   GREEN_BUTTON
#define PARTY_MODE   RED_BUTTON


void handleControlsState() {
  if (lastControlsState == controlsState) {
    return;
  }

  if (bitRead(lastControlsState, SOUND_BUZZER) != bitRead(controlsState, SOUND_BUZZER)) {
    // Buzzer  
    powerBuzzer(bitRead(controlsState, SOUND_BUZZER));
  }
  
    // Turn LEDs ON/OFF
  if (bitRead(controlsState, LIGHTS_SWITCH)) {
      switchLeds();      
  } 
  
  if (bitRead(controlsState, RESCUE_MODE)) {
    switchRescueMode();  
  }
  
  if (bitRead(controlsState, PARTY_MODE)) {
    switchPartyMode();  
  }    
}

void handleModeState() {
  static byte lastMode;
  
  if ((modesState == 0x0) || (lastMode == modesState)) {
    return;
  }
  switchLedMode(); 
  powerBuzzer(false);
  lastMode = modesState;
}

void switchRescueMode() {
  setLedsRescueMode(true);  
  setBuzzerRescueMode(true);  
}

void switchPartyMode() {
  setLedsPartyMode(true);  
  setBuzzerPartyMode(true);  
}

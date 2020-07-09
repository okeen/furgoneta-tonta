#include "pitches.h"

#define SEMI_CORCHEA 1
#define CORCHEA 2
#define NEGRA 4
#define BLANCA 8
#define REDONDA 16

#define HORNET_MODE 0
#define RESCUE_MODE 1
#define PARTY_MODE 2
#define OFF_MODE 3

byte buzzerMode = OFF_MODE;

void initBuzzer() {
  buzzerTimer.every(SEMI_CORCHEA * 100, updateBuzzer);
}

const byte rescueModeTones[2] = {NOTE_D5, NOTE_A2};
const byte partyModeTones[6] = {NOTE_B3, NOTE_A3, NOTE_F2, NOTE_B3, NOTE_A3, NOTE_F2};
bool rescueModeToneIndex = 0;

void updateBuzzer() {
  static byte toneIndex = 0;

  # if defined(DEBUG_MODE)  
    Serial.print("BUZZER: Update ");
    Serial.print(toneIndex);
    Serial.print(" - ");
    Serial.println(buzzerMode);    
  # endif    
  
  switch (buzzerMode) {
    case HORNET_MODE:
      tone(BUZZER_PIN, NOTE_C4, CORCHEA * 100);    
      break;  
    case OFF_MODE:
      noTone(BUZZER_PIN);        
      break;    
    case RESCUE_MODE:
      if (toneIndex % NEGRA == 0) {
        tone(BUZZER_PIN, rescueModeTones[rescueModeToneIndex], NEGRA * 100);      
        rescueModeToneIndex = !rescueModeToneIndex;
      }        
      break;    
    case PARTY_MODE:
      tone(BUZZER_PIN, partyModeTones[toneIndex], SEMI_CORCHEA * 100);      
      break;
   }
   if (++toneIndex == 64) {
    toneIndex = 0;
   }
}

void powerBuzzer(bool isActive) {
  
  if (isActive) {
    # if defined(DEBUG_MODE)  
      Serial.println("BUZZER -> ON");      
    # endif  
      
    buzzerMode = HORNET_MODE;
  } else {
    # if defined(DEBUG_MODE)  
      Serial.println("BUZZER -> OFF");      
    # endif    
    
    buzzerMode = OFF_MODE;
  }  
}

void setBuzzerRescueMode(bool state) {
  # if defined(DEBUG_MODE)  
    Serial.print("BUZZER: rescue mode -> ");
    Serial.println(state);
  # endif    
  buzzerMode = RESCUE_MODE;
}

void setBuzzerPartyMode(bool state) {
  # if defined(DEBUG_MODE)  
    Serial.print("BUZZER: party mode -> ");
    Serial.println(state);
  # endif    
  buzzerMode = PARTY_MODE;
}

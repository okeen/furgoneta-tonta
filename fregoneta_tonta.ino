#include <L298N.h>
#include <FastLED.h>
#include <SoftwareSerial.h>
#include <arduino-timer.h>


#define ENABLE_LEFT_MOTOR_PIN A1
#define FORWARD_LEFT_MOTOR_PIN 6
#define BACKWARD_LEFT_MOTOR_PIN 7

#define ENABLE_RIGHT_MOTOR_PIN A2
#define FORWARD_RIGHT_MOTOR_PIN 5 
#define BACKWARD_RIGHT_MOTOR_PIN 4

#define LED_PIN            8
#define FRONT_LED_PIN      9
#define REAR_LEFT_LED_PIN  10
#define REAR_RIGHT_LED_PIN 12

#define BUZZER_PIN 11

// Direction states
#define ST_IDLE 0x8

#define ST_MOVING_FORWARD 0x0
#define ST_MOVING_RIGHT 0x1
#define ST_TURNING_RIGHT 0x2
#define ST_MOVING_RIGHT_BACKWARDS 0x3
#define ST_MOVING_BACKWARDS 0x4
#define ST_MOVING_LEFT_BACKWARDS 0x5
#define ST_TURNING_LEFT 0x6
#define ST_MOVING_LEFT 0x7


// Radio Pins
#define RADIO_RX_PIN       2   
#define RADIO_TX_PIN       3   

#define DEBUG_DELAY 20
//#define DEBUG_MODE 1   

L298N leftMotors(ENABLE_LEFT_MOTOR_PIN, FORWARD_LEFT_MOTOR_PIN, BACKWARD_LEFT_MOTOR_PIN);
L298N rightMotors(ENABLE_RIGHT_MOTOR_PIN, FORWARD_RIGHT_MOTOR_PIN, BACKWARD_RIGHT_MOTOR_PIN);

SoftwareSerial radioSerial(RADIO_RX_PIN, RADIO_TX_PIN);

auto ledsTimer = timer_create_default();
auto buzzerTimer = timer_create_default();

byte modesState = 0x0;
byte controlsState = 0x0;
byte joystickState = 0x0;

byte lastJoystickState;
byte lastControlsState;
byte lastModesState;
  
void setup() {
  # if defined(DEBUG_MODE)  
    Serial.begin(9600);
  # endif  
  
  delay(DEBUG_DELAY); // power-up safety delay
  initRadio();
  initLeds();
  initBuzzer();
  # if defined(DEBUG_MODE)  
    Serial.println("MAIN: Init OK");
  # endif  
  
  joystickState = ST_IDLE;
}

void loop() {
  lastJoystickState = joystickState;
  lastControlsState = controlsState;
  lastModesState = modesState;
  
  readStateFromRadio();
   
  handleModeState();
  handleControlsState();
  handleMotorsState();
  updateLeds();    
  
  ledsTimer.tick();
  buzzerTimer.tick();
  
  # if defined(DEBUG_DELAY) 
    Serial.println("MAIN: LOOP ENDS");      
    delay(DEBUG_DELAY);
  # endif    
}



void setSpeed(L298N motor, byte level) {
  motor.setSpeed(level);
}

void handleMotorsState() {
  static byte lastJoysticState;

  if (lastJoysticState == joystickState) {
    return;
  }
  
  # if defined(DEBUG_MODE)  
    Serial.print("MOTORS: Handle motor state -> ");
  # endif

  switch (joystickState) {
      case ST_MOVING_FORWARD:
        center();
        break;
      case ST_MOVING_RIGHT:
        moveRight();
        break;
      case ST_TURNING_RIGHT:
        turnRight();
        break;
      case ST_MOVING_RIGHT_BACKWARDS:
        moveRightBackwards();
        break;
      case ST_MOVING_BACKWARDS:
        centerBackwards();
        break;
      case ST_MOVING_LEFT_BACKWARDS:
        moveLeftBackwards();
        break;
      case ST_TURNING_LEFT:
        turnLeft();    
        break;
      case ST_MOVING_LEFT:
        moveLeft();    
        break;        
      case ST_IDLE:
        fullStop();    
        break;          
    }
    lastJoysticState = joystickState;
    
    # if defined(DEBUG_MODE)  
      Serial.println("MOTORS: Done");
  # endif  
}

void moveLeft() {
  # if defined(DEBUG_MODE)  
    Serial.println("Left");
  # endif

  leftMotors.stop();
  rightMotors.forward();
}

void moveRight() {
  # if defined(DEBUG_MODE)  
    Serial.println("Right");
  # endif

  leftMotors.forward();
  rightMotors.stop();      
}

void center() {
  # if defined(DEBUG_MODE)  
    Serial.println("Forward");
  # endif

  leftMotors.forward();
  rightMotors.forward();      
}

void moveLeftBackwards() {
  # if defined(DEBUG_MODE)  
    Serial.println("Left Back");
  # endif

  leftMotors.stop();
  rightMotors.backward();
  
}

void moveRightBackwards() {
  # if defined(DEBUG_MODE)  
    Serial.println("Right Back");
  # endif

  leftMotors.backward();
  rightMotors.stop();      
}

void centerBackwards() {
  # if defined(DEBUG_MODE)  
    Serial.println("Center Back");
  # endif

  leftMotors.backward();
  rightMotors.backward();      
}

void fullStop() {
  # if defined(DEBUG_MODE)  
    Serial.println("Stop");
  # endif

  leftMotors.stop();
  rightMotors.stop();      
}

void turnLeft() {
  # if defined(DEBUG_MODE)  
    Serial.println("Turn Left");
  # endif

  leftMotors.backward();
  rightMotors.forward();      
}

void turnRight() {
  # if defined(DEBUG_MODE)  
    Serial.println("Turn right");
  # endif

  leftMotors.forward();
  rightMotors.backward();      
}

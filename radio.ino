void initRadio() {
  radioSerial.begin(9600);  
  # if defined(DEBUG_MODE)
    Serial.println("RADIO: Init OK");
  # endif
}

void readStateFromRadio() {
  int buff;
  static int8_t tokenNumberInDatagram;
  
  while(radioSerial.available() > 0) {
    buff = radioSerial.read();
    switch (tokenNumberInDatagram) {
      case 0x0:
        // Protocol init byte - ignore
        if (buff == 0xAF) {
          # if defined(DEBUG_MODE)  
              Serial.println("RADIO: START--");
          # endif

          tokenNumberInDatagram++; 
        }
        break;
      case 0x1:
        // Mode buttons status        
        setModeStatus(buff);
        tokenNumberInDatagram++;
        break;
      case 0x2:
        // Control buttons status        
        setControlsStatus(buff);
        tokenNumberInDatagram++;
        break;
      case 0x3:
        setDirection(buff);
        tokenNumberInDatagram++;
        break;
      case 0x4:
        // Protocol end byte - SEND ACK????
        if (buff == 0xFA) {
          # if defined(DEBUG_MODE)  
            Serial.println("RADIO: --END");
        # endif
          tokenNumberInDatagram = 0;        
        }        
    }
  }
}

void setDirection(byte buf) {
  # if defined(DEBUG_MODE)  
      Serial.print("RADIO: Joystick -> ");
      Serial.println(buf, HEX);
  # endif

  joystickState = buf;
}


void setControlsStatus(byte buf) {
  # if defined(DEBUG_MODE)  
      Serial.print("RADIO: Controls -> ");
      Serial.println(buf, BIN);
  # endif

  controlsState = buf;
}

void setModeStatus(byte buf) {
  # if defined(DEBUG_MODE)  
      Serial.print("RADIO: Mode -> ");
      Serial.println(buf, BIN);
  # endif

  modesState = buf;
}

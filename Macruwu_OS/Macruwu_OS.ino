#include <Wire.h>
//#ifdef USE_TINYUSB
//#include <Adafruit_TinyUSB.h>
//#endif

#define DEBUG false

#include "Expander.h"
#include "Mapping.h"
#include "Keyboard.h"

//#define ADDone 0b0100000        //to be added
//#define ADDtwo 0b0100001
//#define DB_TIME 10              //in ms
//#include "Expander.cpp"

Expander Expander1;
Expander Expander2;



void setup() {
  Serial.begin(115200);
  Wire.begin();
  Expander1.init(ADDone);
  Expander2.init(ADDtwo);

  flash_setup();
  keyboardSetup();
}

void loop() {
  //debug_serial();
  for(int i = 0; i < 16; i++){
    if(Expander1.getState(i)){
      action(i);
    }
  }
  for(int i = 0; i < 16; i++){
    if(Expander2.getState(i)){
      action(i+16);
    }
  }
  flash_loop();
  delay(1);
}

void debug_serial(){
  for(int i = 0; i < 16; i++){
    if(Expander1.getState(i) == 1){
      Serial.print("Button ");
      Serial.println(i);
      }  
  }
  for(int i = 0; i < 16; i++){
    if(Expander2.getState(i) == 1){
      Serial.print("Button ");
      Serial.println(i+16);
      }  
  }


  
  }

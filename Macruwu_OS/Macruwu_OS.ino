//DISCLAIMER:
//My spelling is shit, so please ignore the spelling mistakes in the comments.
//Thx uwu

#include <Wire.h>

#define DEBUG false

#include "Expander.h"
#include "Mapping.h"
#include "Keyboard.h"
#include "Neopixel.h"


#define ADDone 0b0100000        
#define ADDtwo 0b0100001

Expander Expander1(ADDone);
Expander Expander2(ADDtwo);


//default Constructor. Initialises the Keyboard with: layout file: "macroLayout.txt", Layers: 5, Buttons: 32
Keyboard Macruwu;

// To change default parameters, call the constructor with arguments: 
// Keyboard Keyboard_Name("FILENAME", AMMOUNT_LAYERS, AMMOUNT_KEYS);
// For Example:
// Keyboard Macruwu("macroLayout.txt", 5, 32);           


void setup() {
  Serial.begin(115200);       //Open Serial Port at 115200 baud
  Wire.begin();               //start I²C for I/O expanders
  flash_setup();              //Setup flash storage as mounted drive
  //flash_test();             //try running if flsh storage won´t work. will try to create File and run some Tests.
                              //concider running it in loop(), due to a bug, where Serial prints are not sent from setup()
  //keyboardSetup();          //use this, if you with to use the Hardcoded Mapping
  Macruwu.init();             //Setup code for file mapped Keyboard
  neopixelSetup();            //Setup code for Neopixels

  Serial.print("done innit?");
}

void loop() {
  //debug_serial();           //Meant for testing the switches via the Serial Monitor
  //flash_loop();             //Try running this if you are having problems with the flash storage
  
  if(Macruwu.fsChanged()){
    Macruwu.readFile();
  }

  run();
  testNeopixel();
  delay(1);
}

void debug_serial(){              //For testing the Inputs
  for(int i = 0; i < 16; i++){
    if(Expander1.getState(i)){
      Serial.print("Button ");
      Serial.println(i);
      }  
  }
  for(int i = 0; i < 16; i++){
    if(Expander2.getState(i)){
      Serial.print("Button ");
      Serial.println(i+16);
      }  
  }
}

void run(){
  for(int i = 0; i < 16; i++){
    if(Expander1.getState(i)){
      //action(i);              //enable if you wish to run hardcoded mapping
      Macruwu.interpret(1, i);
    }
  }
  for(int i = 0; i < 16; i++){
    if(Expander2.getState(i)){
      //action(i+16);
      Macruwu.interpret(1, i+16);
    }
  }
  
  
}
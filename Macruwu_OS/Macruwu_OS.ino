#include <Wire.h>
//#ifdef USE_TINYUSB
//#include <Adafruit_TinyUSB.h>
//#endif

#define DEBUG false

#include "Expander.h"
#include "Mapping.h"
#include "Keyboard.h"
#include "Neopixel.h"

//#define ADDone 0b0100000        //to be added
//#define ADDtwo 0b0100001
//#define DB_TIME 10              //in ms
//#include "Expander.cpp"

Expander Expander1;
Expander Expander2;

//Keyboard Macruwu;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  Expander1.init(ADDone);
  Expander2.init(ADDtwo);
  //flash_setup();
  keyboardSetup();
  //Macruwu.init();
  Serial.print("done init");
  //Macruwu.readFile();
  neopixelSetup();
  //keyboardSetup();
}

void loop() {
  //debug_serial();
  
  //flash_loop();
  run();
  testNeopixel();
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

void run(){
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
  
}



/*TODO
Filesystem Read test and implementation.
Try Examples/SD_Fat_full_usage (from line 129)

File32 readFile = fatfs.open("/test/test.txt", FILE_READ);
  if (!readFile) {
    Serial.println("Error, failed to open test.txt for reading!");
    while(1) yield();
  }

  // Read data using the same read, find, readString, etc. functions as when using
  // the serial class.  See SD library File class for more documentation:
  //   https://www.arduino.cc/en/reference/SD
  // Read a line of data:
  String line = readFile.readStringUntil('\n');
  Serial.print("First line of test.txt: "); Serial.println(line);

  // You can get the current position, remaining data, and total size of the file:
  Serial.print("Total size of test.txt (bytes): "); Serial.println(readFile.size(), DEC);
  Serial.print("Current position in test.txt: "); Serial.println(readFile.position(), DEC);
  Serial.print("Available data to read in test.txt: "); Serial.println(readFile.available(), DEC);

  // And a few other interesting attributes of a file:
  char readName[64];
  readFile.getName(readName, sizeof(readName));
  Serial.print("File name: "); Serial.println(readName);
  Serial.print("Is file a directory? "); Serial.println(readFile.isDirectory() ? "Yes" : "No");

  // You can seek around inside the file relative to the start of the file.
  // For example to skip back to the start (position 0):
  if (!readFile.seek(0)) {
    Serial.println("Error, failed to seek back to start of file!");
    while(1) yield();
  }

  // And finally to read all the data and print it out a character at a time
  // (stopping when end of file is reached):
  Serial.println("Entire contents of test.txt:");
  while (readFile.available()) {
    char c = readFile.read();
    Serial.print(c);
  }

  // Close the file when finished reading.
  readFile.close();

*/




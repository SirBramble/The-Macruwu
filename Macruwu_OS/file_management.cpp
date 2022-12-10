#include "file_management.h"

#include "SPI.h"
#include <SdFat.h>
#include "Adafruit_SPIFlash.h"
#include "Adafruit_TinyUSB.h"

#include "flash_config.h"

// for flashTransport definition

Adafruit_SPIFlash flash(&flashTransport);

// file system object from SdFat
FatVolume fatfs;

FatFile root;
FatFile file;

// USB Mass Storage object
Adafruit_USBD_MSC usb_msc;

// Check if flash is formatted
bool fs_formatted;

// Set to true when PC write to flash
bool fs_changed;

// Callback invoked when received READ10 command.
// Copy disk's data to buffer (up to bufsize) and 
// return number of copied bytes (must be multiple of block size) 
int32_t msc_read_cb (uint32_t lba, void* buffer, uint32_t bufsize)
{
  // Note: SPIFLash Block API: readBlocks/writeBlocks/syncBlocks
  // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
  return flash.readBlocks(lba, (uint8_t*) buffer, bufsize/512) ? bufsize : -1;
}

// Callback invoked when received WRITE10 command.
// Process data in buffer to disk's storage and 
// return number of written bytes (must be multiple of block size)
int32_t msc_write_cb (uint32_t lba, uint8_t* buffer, uint32_t bufsize)
{
  digitalWrite(LED_BUILTIN, HIGH);

  // Note: SPIFLash Block API: readBlocks/writeBlocks/syncBlocks
  // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
  return flash.writeBlocks(lba, buffer, bufsize/512) ? bufsize : -1;
}

// Callback invoked when WRITE10 command is completed (status received and accepted by host).
// used to flush any pending cache.
void msc_flush_cb (void)
{
  // sync with flash
  flash.syncBlocks();

  // clear file system's cache to force refresh
  fatfs.cacheClear();

  fs_changed = true;

  digitalWrite(LED_BUILTIN, LOW);
}


// the setup function runs once when you press reset or power the board
void flash_setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  flash.begin();

  // Set disk vendor id, product id and revision with string up to 8, 16, 4 characters respectively
  usb_msc.setID("Macruwu", "BIG DICK FLASH", "6.9");

  // Set callback
  usb_msc.setReadWriteCallback(msc_read_cb, msc_write_cb, msc_flush_cb);

  // Set disk size, block size should be 512 regardless of spi flash page size
  usb_msc.setCapacity(flash.size()/512, 512);

  // MSC is ready for read/write
  usb_msc.setUnitReady(true);

  usb_msc.begin();

  // Init file system on the flash
  fs_formatted = fatfs.begin(&flash);

  //Serial.begin(115200);
  //while ( !Serial ) delay(10);   // wait for native usb

  if ( !fs_formatted )
  {
    Serial.println("Failed to init files system, flash may not be formatted");
  }

  Serial.println("Adafruit TinyUSB Mass Storage External Flash example");
  Serial.print("JEDEC ID: 0x"); Serial.println(flash.getJEDECID(), HEX);
  Serial.print("Flash size: "); Serial.print(flash.size() / 1024); Serial.println(" KB");

  fs_changed = true; // to print contents initially
}



void flash_loop()
{
  if ( fs_changed )
  {
    fs_changed = false;

    // check if host formatted disk
    if (!fs_formatted)
    {
      fs_formatted = fatfs.begin(&flash);
    }

    // skip if still not formatted
    if (!fs_formatted) return;

    Serial.println("Opening root");

    if ( !root.open("/") )
    {
      Serial.println("open root failed");
      return;
    }

    Serial.println("Flash contents:");

    // Open next file in root.
    // Warning, openNext starts at the current directory position
    // so a rewind of the directory may be required.



    while ( file.openNext(&root, O_RDONLY) )
    {
      file.printFileSize(&Serial);
      Serial.write(' ');
      file.printName(&Serial);
      if ( file.isDir() )
      {
        // Indicate a directory.
        Serial.write('/');
      }
      Serial.println();
      file.close();
    }

    root.close();
    flash_test();

    Serial.println();
    delay(1000); // refresh every 1 second
  }
}

void flash_test(){
  Serial.println("Creating deep folder structure...");
  if ( !fatfs.exists("/test/foo/bar") ) {
    Serial.println("Creating /test/foo/bar");
    fatfs.mkdir("/test/foo/bar");

    if ( !fatfs.exists("/test/foo/bar") ) {
      Serial.println("Error, failed to create directory!");
      while(1) yield();
    }else {
      Serial.println("Created directory!");
    }
  }
  String filename_to_open = "macroLayout.txt";
  File32 readFile = fatfs.open(filename_to_open, FILE_READ);
  if (!readFile) {
    Serial.println("Error, failed to open test.txt for reading!");
    while(1) yield();
  }

  String file;
  while (readFile.available()) {
    file.concat((char)readFile.read());
  }
  Serial.println("file at 3:");
  Serial.println(file.charAt(3));
  if(file.indexOf('\n') != -1){
    Serial.println("found some shit");
  }

  if (!readFile.seek(0)) {
    Serial.println("Error, failed to seek back to start of file!");
    while(1) yield();
  }

  Serial.println("Entire contents of file:");
  while (readFile.available()) {
    char c = (char)readFile.read();
    Serial.print(c);
  }
  String sub;
  Serial.println("Entire contents of file from string:");
  Serial.println(file);
  Serial.println("linewise:");
    if (!readFile.seek(0)) {
      Serial.println("Error, failed to seek back to start of file!");
      while(1) yield();
    }
    while(readFile.available()){
      sub = readFile.readStringUntil('\n');
      Serial.println(sub);
    }
    readFile.close();

    Serial.println("Test for File Readin:");
    String tmp;
    String filename = "macroLayout.txt";
    File32 macroLayout = fatfs.open(filename, FILE_READ);
    if (!macroLayout.seek(0)) {
    Serial.println("Error, failed to seek back to start of file!");
    while(1) yield();
    }
    if (!macroLayout) {
      Serial.println("Error, failed to open file for reading!");
      while(1){
        delay(10);
        //yield();
      }
    }
    

    while (macroLayout.available()) {
      tmp = macroLayout.readStringUntil('\n');
      Serial.println(tmp);
      if(tmp.indexOf("Layer") != -1){
          //currentLayer = getNum(tmp) - 1;
      }
      if(tmp.indexOf("Button") != -1){
          //set(currentLayer, getNum(tmp) - 1 , getString(tmp));
      }
    }
  macroLayout.close();
}



const char* digits = "0123456789";




/////////
//Layer//
/////////
Layer::Layer(){
    for(int i = 0; i < AMMOUNT_KEYS; i++){
        Button.push_back("");
    }
}
String Layer::get(int indexButton){
    return Button.at(indexButton);
}
void Layer::set(int indexButton, String funktionString){
    Button.at(indexButton) = funktionString;
    Serial.println("Layer::set");
}

//////////
//Keymap//
//////////
Keymap::Keymap(String filename, int ammountLayers){
    this->filename = filename;
    this->ammountLayers = ammountLayers;
    //flash_setup();
}

void Keymap::init(){
  Layers.reserve(ammountLayers);
  for(int i = 0; i < ammountLayers; i++){
    Layers.push_back(Layer());
  }
}

String Keymap::get(int indexLayer, int indexButton){
    indexLayer--;
    //indexButton--;
    if((indexLayer>=ammountLayers)||(indexLayer < 0)){return "";}
    if((indexButton>=AMMOUNT_KEYS)||(indexButton < 0)){return "";}
    return (&Layers.at(indexLayer))->get(indexButton);
}

void Keymap::set(int indexLayer, int indexButton, String funktionString){
  Serial.println("Setting Start:");
  Serial.print("indeyLayer: "); Serial.println(indexLayer);
  Serial.print("indeyButton: "); Serial.println(indexButton);
  Serial.print("funktionString: "); Serial.println(funktionString);
    if(ammountLayers < indexLayer){
      //Layer newOne;
      //Layer *newLayer = new Layer();
      //Layers.push_back(newLayer);
      //ammountLayers++;
      //(&Layers.at(indexLayer))->set(indexButton, funktionString);
      Serial.println("Big Shit hit Fan. You no make Layers Vektor big enough in Keymap.");
    }
    else{
      Serial.println("Keymap::set -> Layer::set");
      Serial.print("Layers.size(): "); Serial.println(Layers.size());
      Serial.print("Layers.capacity(): "); Serial.println(Layers.capacity());
      (&Layers.at(indexLayer))->set(indexButton, funktionString);
    }
  Serial.println("Setting end:");
}

void Keymap::import(){
  Serial.println("Keymap Import:");
    String tmp;
    File32 macroLayout = fatfs.open(filename, FILE_READ);
    if (!macroLayout.seek(0)) {
    Serial.println("Error, failed to seek back to start of file!");
    while(1) yield();
    }
    if (!macroLayout) {
      Serial.println("Error, failed to open file for reading!");
      while(1){
        delay(10);
        //yield();
      }
    }
    

    while (macroLayout.available()) {
      tmp = macroLayout.readStringUntil('\n');
      Serial.println("...................................");
      Serial.println("print tmp");
      Serial.println(tmp);
      Serial.println("...................................");
      
      Serial.println("...................................");
      Serial.println("print getString(tmp)");
      Serial.println(getString(tmp));
      Serial.println("...................................");

      Serial.println("...................................");
      Serial.println("print getNum(tmp)");
      Serial.println(getNum(tmp));
      Serial.println("...................................");
      if(tmp.indexOf("Layer") != -1){
        Serial.println("Setting Layer");
        currentLayer = getNum(tmp) - 1;
      }
      if(tmp.indexOf("Button") != -1){
        Serial.println("Setting Button");
        set(currentLayer, getNum(tmp) - 1 , getString(tmp));
        //set(currentLayer, getNum(tmp) - 1 , "test");
      }
    }
  macroLayout.close();
}

int Keymap::getNum(String tmp){
    //Tipp: NEVER FUCKING USE ARDUINO STRINGS!!!! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH!
    Serial.println("getNum start:");
    Serial.print("print String tmp: "); Serial.println(tmp);
    int tmpPos_first = 0;
    int tmpPos_first_tmp = 0;
    bool found_first_first = 0;
    int tmpPos_last = 0;
    int tmpPos_last_tmp = 0;
    int returnNumber = 0;
    for(int i = 0; i < 10; i++){
      tmpPos_first_tmp = tmp.indexOf(digits[i]);
      if((tmpPos_first_tmp != -1)&&(found_first_first == 0)){
        tmpPos_first = tmpPos_first_tmp;
        found_first_first = 1;
      }
      if((tmpPos_first_tmp < tmpPos_first) && (tmpPos_first_tmp > 0)&&(found_first_first == 1)){
        tmpPos_first = tmpPos_first_tmp;
      }
      tmpPos_last_tmp = tmp.lastIndexOf(digits[i]);
      if(tmpPos_last_tmp > tmpPos_last){
        tmpPos_last = tmpPos_last_tmp;
      }
    }
    //tmpPos_first = tmp.indexOf(digits);                                               //Possible Error Spot
    //tmpPos_last = tmp.lastIndexOf(digits);
    Serial.print("tmpPos_first: "); Serial.println(tmpPos_first);
    Serial.print("tmpPos_last: "); Serial.println(tmpPos_last);
    String returnString = tmp.substring(tmpPos_first, (tmpPos_last + 1));
    Serial.print("returnString: "); Serial.println(returnString);
    Serial.print("returnString.length(): "); Serial.println(returnString.length());
    for(int i = 0; i < returnString.length(); i++){
        Serial.print("Conversion char (as Number): "); Serial.println(returnString.charAt(i) - 48);
        returnNumber *= 10;
        returnNumber += returnString.charAt(i) - 48;
    }
    Serial.print("returnNumber: "); Serial.println(returnNumber);
    //char num[tmpPos_last - tmpPos_first + 1] = {0};
    //tmp.copy(num, (tmpPos_last - tmpPos_first + 1), tmpPos_first);


    //returnNumber = returnString.toInt();
    Serial.println("getNum end:");
    return returnNumber;
}

String Keymap::getString(String tmp){
    //return tmp.substring(tmp.lastIndexOf(":") + 2);
    return tmp.substring(tmp.lastIndexOf(":") + 2);
}


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


    Serial.println();
    delay(1000); // refresh every 1 second
  }
}


const char* digits = "0123456789";




/////////
//Layer//
/////////
String Layer::get(int indexButton){
    return Button.at(indexButton);
}
void Layer::set(int indexButton, String funktionString){
    Button.at(indexButton) = funktionString;
}

//////////
//Keymap//
//////////
Keymap::Keymap(String filename){
    this->filename = filename;
    //flash_setup();
    ammountLayers = 0;
}

String Keymap::get(int indexLayer, int indexButton){
    indexLayer--;
    indexButton--;
    if(indexLayer>=ammountLayers){return "";}
    return (&Layers.at(indexLayer))->get(indexButton);
}

void Keymap::set(int indexLayer, int indexButton, String funktionString){
    if(ammountLayers < indexLayer){
      Layer newOne;
      Layers.push_back(newOne);
      ammountLayers++;
    }
    else{
        (&Layers.at(indexLayer))->set(indexButton, funktionString);
    }
    
}

void Keymap::import(){
    String tmp;
    File32 macroLayout = fatfs.open(filename, FILE_READ);
    if (!macroLayout) {
      Serial.println("Error, failed to open file for reading!");
      while(1){
        delay(10);
        //yield();
      }
    }
    
    //ifstream macroLayout;
    //macroLayout.open(filename);
    while (macroLayout.available()) {
      while(String tmp = macroLayout.readStringUntil('\n')){
        if(tmp.indexOf("Layer") != -1){
            currentLayer = getNum(tmp) - 1;
        }
        if(tmp.indexOf("Button") != -1){
            set(currentLayer, getNum(tmp) - 1 , getString(tmp));
        }
      }
    }
  macroLayout.close();
}

int Keymap::getNum(String tmp){
    int tmpPos_first = 0;
    int tmpPos_last = 0;
    int returnNumber = 0;
    tmpPos_first = tmp.indexOf(digits);                                               //Possible Error Spot
    tmpPos_last = tmp.lastIndexOf(digits);
    String returnString = tmp.substring(tmpPos_first, tmpPos_last);
    returnNumber = returnString.toInt();
    //char num[tmpPos_last - tmpPos_first + 1] = {0};
    //tmp.copy(num, (tmpPos_last - tmpPos_first + 1), tmpPos_first);
    //for(int i = 0; i < sizeof(num); i++){
    //    returnNumber *= 10;
    //    returnNumber = num[i] - 48;
    //}
    return returnNumber;
}

String Keymap::getString(String tmp){
    int tmpPos_first;
    return tmp.substring(tmp.lastIndexOf(":") + 2);
}

Layer::Layer(){
    for(int i = 0; i < AMMOUNT_KEYS; i++){
        Button.push_back("");
    }
}
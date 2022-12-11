#include "Keyboard.h"

uint8_t const conv_table[128][2] =  { HID_ASCII_TO_KEYCODE };
uint8_t const desc_hid_report[] ={ TUD_HID_REPORT_DESC_KEYBOARD() };
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD, 2, false);

Keyboard::Keyboard(String filename, int ammountLayers, int ammountKeys){
    this->filename = filename;
    this->ammountLayers = ammountLayers;
    this->ammountKeys = ammountKeys;
}

void Keyboard::readFile(){
    keymap_ptr->import();
}

String Keyboard::get_string_from_file(int layer, int button){
    return keymap_ptr->get(layer, button);
}

void Keyboard::set_string_in_file(int layer, int button, String string_to_write){
    keymap_ptr->set(layer, button, string_to_write);
}
void Keyboard::interpret(int layer, int button){
  String stringToInterpret = keymap_ptr->get(layer,button);
  char charToInterpret;
  bool inBuffer = 0;
  String bufferString;
  for(uint32_t i = 0; i<stringToInterpret.length(); i++){
    charToInterpret = stringToInterpret.charAt(i);
    if(((charToInterpret >= 65)&&(charToInterpret <= 90))||((charToInterpret >= 97)&&(charToInterpret <= 122))||(charToInterpret == ' ')){    //checks for printable Letters with the write funktion
        inBuffer = 1;               //fill up the bufferString until the nect character is not part if the printable characters of the write() funktion
        bufferString += charToInterpret;
        continue;
    }
    else if(inBuffer){              //if the read character is no longer part of the printable write() characters, send the bufferString
        this->write(bufferString);
        bufferString.remove(0, (bufferString.length()));
        inBuffer = 0;
        
    }
    if(charToInterpret == 36){                  //checks for '$'
      this->write("$");
      continue;
    }
    if(charToInterpret == '<'){                 //checks for '<' and triggers the left arrow key
      this->goLeft(1);
    }
    if(charToInterpret == '>'){                 //checks for '>' and triggers the right arrow key
      this->goRight(1);
    }
    if(charToInterpret == 92){                  //checks for '\'
      this->backslash();
      continue;
    }
    if(charToInterpret == '_'){                  //checks for '_'
      this->writeKeycode(56, KEYBOARD_MODIFIER_LEFTSHIFT);
      continue;
    }
    if(charToInterpret == '{'){                 //checks for '{'
      if(stringToInterpret.charAt(i+1) == 125){   //checks next character for '}' and if found, sends both brackets at once (to save time)
        this->brackets();
        i++;
      }
      else{
        this->writeKeycode(HID_KEY_7, KEYBOARD_MODIFIER_RIGHTALT);  //if second bracket not found, send single bracket
      }
      continue;
    }
    if(charToInterpret == '}'){                 //checks for '}'
      this->writeKeycode(HID_KEY_0, KEYBOARD_MODIFIER_RIGHTALT);
      continue;
    }
    if(charToInterpret == '['){                 //checks for '['
        if(stringToInterpret.charAt(i+1) == ']'){   //checks next character for ']' and if found, sends both square brackets at once (to save time)
            this->bracketsSquare();
            i++;
        }
        else{
            this->writeKeycode(HID_KEY_8, KEYBOARD_MODIFIER_RIGHTALT);  //if second square bracket not found, send single bracket
        }
        continue;
    }
    if(charToInterpret == ']'){                 //checks for ']'
        this->writeKeycode(HID_KEY_9, KEYBOARD_MODIFIER_RIGHTALT);
        continue;
    }
    if(charToInterpret == '^'){                 //checks for '^'
      writeKeycode(HID_KEY_GRAVE);     
      //cout<<"send funny to the power of symbol thingymabob"<<endl;
        continue;
    }
  }
  if(inBuffer){                       //runs, if last character war part of the printable characters from write()
      write(bufferString);
      bufferString.remove(0, (bufferString.length()));
      inBuffer = 0;
  }
}

void Keyboard::init(){          //sets up flash and runs initial read of file
  usb_hid.begin();
  while( !TinyUSBDevice.mounted() ){
    delay(100);
    Serial.print("Crashing");
  } 
  keymap_ptr = std::unique_ptr<Keymap>(new Keymap(filename, ammountLayers, ammountKeys));
  keymap_ptr->init();
  flash_setup();
  readFile();
}

void Keyboard::write(String text){
  if ( TinyUSBDevice.suspended())
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }
  modifier = 0;
  uint8_t n = 0;
  uint8_t c;
  while(n < text.length()){
    
    for(int i = 0; i < 6; i++){
      if(n < text.length()){
        c = (uint8_t) text.charAt(n);
        #ifdef SERIAL_DEBUG
        Serial.print((char)c);
        #endif
      }
      else{
        send();
        break;
      }
      if(c == (uint8_t)'y'){              //y and z had to be swapped, due to my German Keyboard Layout
        c = (uint8_t)'z';                 //this may be addressed in the future...
      }
      else if(c == (uint8_t)'z'){
        c = (uint8_t)'y';
      }
      if(c == (uint8_t)'Y'){
        c = (uint8_t)'Z';
      }
      else if(c == (uint8_t)'Z'){
        c = (uint8_t)'Y';
      }
      if(isLetterSmall(c)){
        setBuffer(i, conv_table[c][1]);
      }
      else{
        send();
        if ( conv_table[c][0] ){
          modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        }
        setBuffer(0, conv_table[c][1]);
        send(modifier);
        modifier = 0;
        i = 0;
      }
      if(c == (uint8_t) text.charAt(n+1)){
        send();
        modifier = 0;
        i = 0;
      }
      n++;
    }
    send();
  }
  
}

void Keyboard::setBuffer(uint8_t index, uint8_t value){
  if(index < 6){
    buffer[index] = value;
    bufferSetFlag = 1;
  }
  else{
    #ifdef SERIAL_DEBUG
    Serial.println("out of range in buffer set");
    #endif
  }
}

bool Keyboard::bufferClear(){
  if(bufferSetFlag){
    return 0;
  }
  return 1;
}

void Keyboard::clearBuffer(){
  for(int i = 0; i < 6; i++){
    buffer[i] = 0;
  }
  bufferSetFlag = 0;
}

void Keyboard::send(uint8_t mod){
  #ifdef SERIAL_DEBUG
    Serial.print("Buffer: ");
    for(int i = 0; i < 6; i++){
      Serial.print(buffer[i]); Serial.print(" ");
    }
    Serial.println("");
  #endif
  
  if(!bufferClear()){
    #ifdef SERIAL_DEBUG
      Serial.println("send called");
    #endif
    usb_hid.keyboardReport(report_id, mod, buffer);
    delay(SEND_DELAY);
    usb_hid.keyboardRelease(report_id);
    delay(SEND_DELAY);
  }
  clearBuffer();
  #ifdef SERIAL_DEBUG
    Serial.print("Buffer after clear: ");
    for(int i = 0; i < 6; i++){
      Serial.print(buffer[i]); Serial.print(" ");
    }
    Serial.println("");
  #endif
}

bool Keyboard::isLetterSmall(char c){
  if((c >= 97)&&(c <= 122)){
    return 1;
  }
  return 0;
}

void Keyboard::backslash(){
  this->setBuffer(0, HID_KEY_MINUS);
  this->send(KEYBOARD_MODIFIER_RIGHTALT);
}

void Keyboard::goLeft(uint8_t ammount){
  for(int i = 0; i < ammount; i++){
    setBuffer(0, HID_KEY_ARROW_LEFT);
    send(0);                          //Send with Modifier 0 (NULL/No Modifier)
  }
}

void Keyboard::goRight(uint8_t ammount){
  for(int i = 0; i < ammount; i++){
    setBuffer(0, HID_KEY_ARROW_RIGHT);
    send(0);                          //Send with Modifier 0 (NULL/No Modifier)
  }
}

void Keyboard::brackets(bool goToMiddle){
  this->setBuffer(0, HID_KEY_7);
  this->setBuffer(1, HID_KEY_0);
  this->send(KEYBOARD_MODIFIER_RIGHTALT); //Send with Modifier Right_Alt
  if(goToMiddle){
    this->goLeft(1);
  }
}

void Keyboard::bracketsSquare(bool goToMiddle){
  this->setBuffer(0, HID_KEY_8);
  this->setBuffer(1, HID_KEY_9);
  this->send(KEYBOARD_MODIFIER_RIGHTALT); //Send with Modifier Right_Alt
  if(goToMiddle){
    this->goLeft(1);
  }
}

void Keyboard::writeKeycode(uint8_t Keycode, uint8_t Modifier){
  setBuffer(0, Keycode);
  this->send(Modifier);
}

bool Keyboard::fsChanged(){
  if(check_fs_changed()){
    set_fs_changed(0);
    return 1;
  }
  return 0;
}

#include "Keyboard.h"

uint8_t const conv_table[128][2] =  { HID_ASCII_TO_KEYCODE };
uint8_t const desc_hid_report[] ={ TUD_HID_REPORT_DESC_KEYBOARD() };
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD, 2, false);

Keyboard::Keyboard(String filename, int ammountLayers){
    this->filename = filename;
    this->ammountLayers = ammountLayers;
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
    bool skipClosingBracket = 0;
    String bufferString;
    for(uint32_t i = 0; i<stringToInterpret.length(); i++){
        charToInterpret = stringToInterpret.charAt(i);
        Serial.print("charToInterpret: ");Serial.println(charToInterpret);
        if(((charToInterpret >= 65)&&(charToInterpret <= 90))||((charToInterpret >= 97)&&(charToInterpret <= 122))||(charToInterpret == ' ')){
            Serial.println("Found shit to write");
            inBuffer = 1;
            bufferString += charToInterpret;
            continue;
        }
        else if(inBuffer){
            Serial.println("Sending Buffer");
            write(bufferString);
            bufferString.remove(0, (bufferString.length()));
            inBuffer = 0;
            
        }
        if(charToInterpret == 36){                  //'$'
          Serial.println("Dollar");
          write("$");
          continue;
        }
        if(charToInterpret == '<'){
          goLeft(1);
        }
        if(charToInterpret == '>'){
          goRight(1);
        }
        if(charToInterpret == 92){                  // '\'
            Serial.println("sending Backslash");
            backslash();
            continue;
        }
        if(charToInterpret == 95){                  //'_'
          Serial.println("Sending underscore");
          writeKeycode(56, KEYBOARD_MODIFIER_LEFTSHIFT);
          continue;
        }
        if(charToInterpret == 123){                 // '{'
          if(stringToInterpret.charAt(i+1) == 125){   // '}'
            Serial.println("Sending double Brackets");
            brackets();
            skipClosingBracket = 1;
          }
          else{
            Serial.println("sending single Bracket open");
            clearBuffer();
            buffer[0] = HID_KEY_7;
            usb_hid.keyboardReport(report_id, KEYBOARD_MODIFIER_RIGHTALT, buffer);
            delay(SEND_DELAY);
            usb_hid.keyboardRelease(report_id);
            delay(SEND_DELAY);
            clearBuffer();
          }
          continue;
        }
        if((charToInterpret == 125)&&(skipClosingBracket == 0)){                 // '}'
          Serial.println("Sending single Bracket close");
          clearBuffer();
          buffer[0] = HID_KEY_0;
          usb_hid.keyboardReport(report_id, KEYBOARD_MODIFIER_RIGHTALT, buffer);
          delay(SEND_DELAY);
          usb_hid.keyboardRelease(report_id);
          delay(SEND_DELAY);
          clearBuffer();
          continue;
        }
        if(charToInterpret == 91){                 // '['
            if(stringToInterpret.charAt(i+1) == 93){   // ']'
                //cout<<"send double square brace"<<endl;
            }
            else{
                //cout<<"send single square brace open"<<endl;
            }
            continue;
        }
        if((charToInterpret == 93)&&(skipClosingBracket == 0)){                 // ']'
            //cout<<"send single suqare brace closed"<<endl;
            continue;
        }
        if(charToInterpret == 94){                 // '^'
          writeKeycode(HID_KEY_GRAVE);     
          //cout<<"send funny to the power of symbol thingymabob"<<endl;
            continue;
        }
        else{
          Serial.print("The Funktion you have called is not available. Please call another.");
          //cout<<"you forgot to implement something you dummy"<<endl;
        }
    }
    if(inBuffer){
        Serial.println("Sending Buffer");
        write(bufferString);
        bufferString.remove(0, (bufferString.length()));
        //cout<<"sending Buffer: "<<buffer<<endl;
        inBuffer = 0;
    }
    if(skipClosingBracket == 1){
      skipClosingBracket = 0;
    }
  
  //interpreter_ptr->interpret(keymap_ptr->get(layer,button));
}

void Keyboard::init(){
  usb_hid.begin();
  while( !TinyUSBDevice.mounted() ){
    delay(100);
    Serial.print("Crashing");
  } 
  //interpreter_ptr = std::unique_ptr<Interpreter>(new Interpreter());
  keymap_ptr = std::unique_ptr<Keymap>(new Keymap(filename, ammountLayers));
  keymap_ptr->init();
  flash_setup();
  //readFile();
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
        Serial.print((char)c);
      }
      else{
        send();
        Serial.print("broken");
        break;
      }
      if(c == (uint8_t)'y'){
        c = (uint8_t)'z';
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
        buffer[i] = conv_table[c][1];
      }
      else{
        send();
        if ( conv_table[c][0] ){
          modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
        }
        buffer[0] = conv_table[c][1];
        //delay(SEND_DELAY);
        send();
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

void Keyboard::send(){
  Serial.print("send");
  Serial.println("buffer: ");
  for(int i = 0; i < 6; i++){
      Serial.println(buffer[i]);
  } 

  usb_hid.keyboardReport(report_id, modifier, buffer);
  delay(SEND_DELAY);
  usb_hid.keyboardRelease(report_id);
  delay(SEND_DELAY);
  clearBuffer();
}

bool Keyboard::isLetterSmall(char c){
  if((c >= 97)&&(c <= 122)){
    return 1;
  }
  return 0;
}

void Keyboard::backslash(){
  clearBuffer();
  buffer[0] = HID_KEY_MINUS;
  usb_hid.keyboardReport(report_id, KEYBOARD_MODIFIER_RIGHTALT, buffer);
  delay(SEND_DELAY);
  usb_hid.keyboardRelease(report_id);
  delay(SEND_DELAY);
  clearBuffer();
}

void Keyboard::goLeft(uint8_t ammount){
  clearBuffer();
  buffer[0] = HID_KEY_ARROW_LEFT;
  for(int i = 0; i < ammount; i++){
    usb_hid.keyboardReport(report_id, modifier, buffer);
    delay(SEND_DELAY);
    usb_hid.keyboardRelease(report_id);
    delay(SEND_DELAY);
  }
  clearBuffer();
}

void Keyboard::goRight(uint8_t ammount){
  clearBuffer();
  buffer[0] = HID_KEY_ARROW_RIGHT;
  for(int i = 0; i < ammount; i++){
    usb_hid.keyboardReport(report_id, modifier, buffer);
    delay(SEND_DELAY);
    usb_hid.keyboardRelease(report_id);
    delay(SEND_DELAY);
  }
  clearBuffer();
}

void Keyboard::brackets(bool goToMiddle){
  clearBuffer();
  buffer[0] = HID_KEY_7;
  buffer[1] = HID_KEY_0;
  usb_hid.keyboardReport(report_id, KEYBOARD_MODIFIER_RIGHTALT, buffer);
    delay(SEND_DELAY);
    usb_hid.keyboardRelease(report_id);
    delay(SEND_DELAY);
  if(goToMiddle){
    goLeft(1);
  }
  clearBuffer();
}

void Keyboard::clearBuffer(){
  for(int i = 0; i < 6; i++){
    buffer[i] = 0;
  }
}

void Keyboard::writeKeycode(uint8_t Keycode, uint8_t Modifier){
  clearBuffer();
  buffer[0] = Keycode;
  usb_hid.keyboardReport(report_id, Modifier, buffer);
  delay(SEND_DELAY);
  usb_hid.keyboardRelease(report_id);
  delay(SEND_DELAY);
  clearBuffer();

}
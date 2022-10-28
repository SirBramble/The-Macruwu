#include "Keyboard.h"

uint8_t const conv_table[128][2] =  { HID_ASCII_TO_KEYCODE };
uint8_t const desc_hid_report[] ={ TUD_HID_REPORT_DESC_KEYBOARD() };
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD, 2, false);

void Keyboard::init(){
  usb_hid.begin();
  while( !TinyUSBDevice.mounted() ) delay(1);
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
        Serial.print(c);
      }
      else{
        send();
        Serial.print("broken");
        break;
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
        delay(5);
        send();
        modifier = 0;
        //i = 0;
      }
      n++;
    }
  }
  send();
}

void Keyboard::send(){
  Serial.print("send");
  usb_hid.keyboardReport(report_id, modifier, buffer);
  delay(3);
  usb_hid.keyboardRelease(report_id);
  delay(3);
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
  delay(3);
  usb_hid.keyboardRelease(report_id);
  delay(3);
  clearBuffer();
}

void Keyboard::goLeft(uint8_t ammount){
  clearBuffer();
  buffer[0] = HID_KEY_ARROW_LEFT;
  for(int i = 0; i < ammount; i++){
    usb_hid.keyboardReport(report_id, modifier, buffer);
    delay(3);
    usb_hid.keyboardRelease(report_id);
    delay(3);
  }
  clearBuffer();
}

void Keyboard::goRight(uint8_t ammount){
  clearBuffer();
  buffer[0] = HID_KEY_ARROW_RIGHT;
  for(int i = 0; i < ammount; i++){
    usb_hid.keyboardReport(report_id, modifier, buffer);
    delay(3);
    usb_hid.keyboardRelease(report_id);
    delay(3);
  }
  clearBuffer();
}

void Keyboard::brackets(bool goToMiddle){
  clearBuffer();
  buffer[0] = HID_KEY_7;
  buffer[1] = HID_KEY_0;
  usb_hid.keyboardReport(report_id, KEYBOARD_MODIFIER_RIGHTALT, buffer);
    delay(3);
    usb_hid.keyboardRelease(report_id);
    delay(3);
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
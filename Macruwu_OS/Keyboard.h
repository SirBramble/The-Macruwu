#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#ifdef USE_TINYUSB
#include <Adafruit_TinyUSB.h>
#endif
//#include <string>
#include <memory>
#include <Arduino.h>
#include "file_management.h"

#define SEND_DELAY 3                        //USB Send Delay(in ms). Needed due to Instability while sending USB Commands
//#define SERIAL_DEBUG                      //Uncomment to enable Debugging

//uint8_t hidcode[] = { HID_KEY_ARROW_RIGHT, HID_KEY_ARROW_LEFT, HID_KEY_ARROW_DOWN, HID_KEY_ARROW_UP };

class Keyboard{
public:
  String get_string_from_file(int layer, int button);                         //Mainly for debugging
  void set_string_in_file(int layer, int button, String string_to_write);     //Mainly for debugging
  void readFile();                          //Read File in to structure
  void interpret(int layer, int button);    //write Characters from file Setup
  void write(String text);                  //write any(isch) Character as a String
  void backslash();                         //prints a backslash
  void goLeft(uint8_t ammount);             //presses the left arrow key 'ammount' times
  void goRight(uint8_t ammount);            //presses the right arrow key 'ammount' times
  void init();                              //setup shit. Call in setup()
  void brackets(bool goToMiddle = 0);       //prints brackets "{}" and jumps the coursor to the middle of them if wanted
  void bracketsSquare(bool goToMiddle = 0);      //prints square brackets "[]" and jumps the coursor to the middle of them if wanted
  void writeKeycode(uint8_t Keycode, uint8_t Modifier = 0); //write a Keycode eather as a Number or as the predefined Keycode Keywords
  bool fsChanged();       //returns file system change status and resets Change Status on call
  Keyboard(String filename = "macroLayout.txt", int ammountLayers = 5, int ammountKeys = 32);
private:
  std::unique_ptr<Keymap> keymap_ptr;
  String sendString;
  String filename;                                //The Layout File ascociated with the Keyboard Object
  int ammountLayers;                              //ammount of Layers controlled by the Keyboard Object
  int ammountKeys;                                //the ammount of Keys controled by the Keyboard object
  uint8_t modifier;                               //intermethod modifier storage. may get removed in future
  uint8_t const report_id = 0;
  uint8_t buffer[6] = {0};                        //send buffer. is limited to size 6 by USB Keyboard protokoll
  bool bufferSetFlag = 0;                         //is set, when buffer has sendable characters
  bool plainFlag = 0;                             //triggers, when \plain command with brackets is opened (\plain{stuff to write in plain text}<- until here)
  void send(uint8_t mod = 0);                     //sends buffer[] with Modifier Key 0 (NULL/no modifier) by default
  bool isLetterSmall(char c);                     //checks if a Character is small
  void clearBuffer();                             //clears buffer and resets bufferSetFlag
  void setBuffer(uint8_t index, uint8_t value);   //sets buffer at index 'index' with value 'value' and sets bufferSetFlag
  bool bufferClear();                             //returns bufferSetFlag
};

#define HID_ASCII_TO_KEYCODE \
    {0, 0                     }, /* 0x00 Null      */ \
    {0, 0                     }, /* 0x01           */ \
    {0, 0                     }, /* 0x02           */ \
    {0, 0                     }, /* 0x03           */ \
    {0, 0                     }, /* 0x04           */ \
    {0, 0                     }, /* 0x05           */ \
    {0, 0                     }, /* 0x06           */ \
    {0, 0                     }, /* 0x07           */ \
    {0, HID_KEY_BACKSPACE     }, /* 0x08 Backspace */ \
    {0, HID_KEY_TAB           }, /* 0x09 Tab       */ \
    {0, HID_KEY_ENTER         }, /* 0x0A Line Feed */ \
    {0, 0                     }, /* 0x0B           */ \
    {0, 0                     }, /* 0x0C           */ \
    {0, HID_KEY_ENTER         }, /* 0x0D CR        */ \
    {0, 0                     }, /* 0x0E           */ \
    {0, 0                     }, /* 0x0F           */ \
    {0, 0                     }, /* 0x10           */ \
    {0, 0                     }, /* 0x11           */ \
    {0, 0                     }, /* 0x12           */ \
    {0, 0                     }, /* 0x13           */ \
    {0, 0                     }, /* 0x14           */ \
    {0, 0                     }, /* 0x15           */ \
    {0, 0                     }, /* 0x16           */ \
    {0, 0                     }, /* 0x17           */ \
    {0, 0                     }, /* 0x18           */ \
    {0, 0                     }, /* 0x19           */ \
    {0, 0                     }, /* 0x1A           */ \
    {0, HID_KEY_ESCAPE        }, /* 0x1B Escape    */ \
    {0, 0                     }, /* 0x1C           */ \
    {0, 0                     }, /* 0x1D           */ \
    {0, 0                     }, /* 0x1E           */ \
    {0, 0                     }, /* 0x1F           */ \
                                                      \
    {0, HID_KEY_SPACE         }, /* 0x20           */ \
    {1, HID_KEY_1             }, /* 0x21 !         */ \
    {1, HID_KEY_APOSTROPHE    }, /* 0x22 "         */ \
    {1, HID_KEY_3             }, /* 0x23 #         */ \
    {1, HID_KEY_4             }, /* 0x24 $         */ \
    {1, HID_KEY_5             }, /* 0x25 %         */ \
    {1, HID_KEY_7             }, /* 0x26 &         */ \
    {0, HID_KEY_APOSTROPHE    }, /* 0x27 '         */ \
    {1, HID_KEY_9             }, /* 0x28 (         */ \
    {1, HID_KEY_0             }, /* 0x29 )         */ \
    {1, HID_KEY_8             }, /* 0x2A *         */ \
    {1, HID_KEY_EQUAL         }, /* 0x2B +         */ \
    {0, HID_KEY_COMMA         }, /* 0x2C ,         */ \
    {0, HID_KEY_MINUS         }, /* 0x2D -         */ \
    {0, HID_KEY_PERIOD        }, /* 0x2E .         */ \
    {0, HID_KEY_SLASH         }, /* 0x2F /         */ \
    {0, HID_KEY_0             }, /* 0x30 0         */ \
    {0, HID_KEY_1             }, /* 0x31 1         */ \
    {0, HID_KEY_2             }, /* 0x32 2         */ \
    {0, HID_KEY_3             }, /* 0x33 3         */ \
    {0, HID_KEY_4             }, /* 0x34 4         */ \
    {0, HID_KEY_5             }, /* 0x35 5         */ \
    {0, HID_KEY_6             }, /* 0x36 6         */ \
    {0, HID_KEY_7             }, /* 0x37 7         */ \
    {0, HID_KEY_8             }, /* 0x38 8         */ \
    {0, HID_KEY_9             }, /* 0x39 9         */ \
    {1, HID_KEY_SEMICOLON     }, /* 0x3A :         */ \
    {0, HID_KEY_SEMICOLON     }, /* 0x3B ;         */ \
    {1, HID_KEY_COMMA         }, /* 0x3C <         */ \
    {0, HID_KEY_EQUAL         }, /* 0x3D =         */ \
    {1, HID_KEY_PERIOD        }, /* 0x3E >         */ \
    {1, HID_KEY_SLASH         }, /* 0x3F ?         */ \
                                                      \
    {1, HID_KEY_2             }, /* 0x40 @         */ \
    {1, HID_KEY_A             }, /* 0x41 A         */ \
    {1, HID_KEY_B             }, /* 0x42 B         */ \
    {1, HID_KEY_C             }, /* 0x43 C         */ \
    {1, HID_KEY_D             }, /* 0x44 D         */ \
    {1, HID_KEY_E             }, /* 0x45 E         */ \
    {1, HID_KEY_F             }, /* 0x46 F         */ \
    {1, HID_KEY_G             }, /* 0x47 G         */ \
    {1, HID_KEY_H             }, /* 0x48 H         */ \
    {1, HID_KEY_I             }, /* 0x49 I         */ \
    {1, HID_KEY_J             }, /* 0x4A J         */ \
    {1, HID_KEY_K             }, /* 0x4B K         */ \
    {1, HID_KEY_L             }, /* 0x4C L         */ \
    {1, HID_KEY_M             }, /* 0x4D M         */ \
    {1, HID_KEY_N             }, /* 0x4E N         */ \
    {1, HID_KEY_O             }, /* 0x4F O         */ \
    {1, HID_KEY_P             }, /* 0x50 P         */ \
    {1, HID_KEY_Q             }, /* 0x51 Q         */ \
    {1, HID_KEY_R             }, /* 0x52 R         */ \
    {1, HID_KEY_S             }, /* 0x53 S         */ \
    {1, HID_KEY_T             }, /* 0x55 T         */ \
    {1, HID_KEY_U             }, /* 0x55 U         */ \
    {1, HID_KEY_V             }, /* 0x56 V         */ \
    {1, HID_KEY_W             }, /* 0x57 W         */ \
    {1, HID_KEY_X             }, /* 0x58 X         */ \
    {1, HID_KEY_Y             }, /* 0x59 Y         */ \
    {1, HID_KEY_Z             }, /* 0x5A Z         */ \
    {0, HID_KEY_BRACKET_LEFT  }, /* 0x5B [         */ \
    {0, HID_KEY_BACKSLASH     }, /* 0x5C '\'       */ \
    {0, HID_KEY_BRACKET_RIGHT }, /* 0x5D ]         */ \
    {1, HID_KEY_6             }, /* 0x5E ^         */ \
    {1, HID_KEY_MINUS         }, /* 0x5F _         */ \
                                                      \
    {0, HID_KEY_GRAVE         }, /* 0x60 `         */ \
    {0, HID_KEY_A             }, /* 0x61 a         */ \
    {0, HID_KEY_B             }, /* 0x62 b         */ \
    {0, HID_KEY_C             }, /* 0x63 c         */ \
    {0, HID_KEY_D             }, /* 0x66 d         */ \
    {0, HID_KEY_E             }, /* 0x65 e         */ \
    {0, HID_KEY_F             }, /* 0x66 f         */ \
    {0, HID_KEY_G             }, /* 0x67 g         */ \
    {0, HID_KEY_H             }, /* 0x68 h         */ \
    {0, HID_KEY_I             }, /* 0x69 i         */ \
    {0, HID_KEY_J             }, /* 0x6A j         */ \
    {0, HID_KEY_K             }, /* 0x6B k         */ \
    {0, HID_KEY_L             }, /* 0x6C l         */ \
    {0, HID_KEY_M             }, /* 0x6D m         */ \
    {0, HID_KEY_N             }, /* 0x6E n         */ \
    {0, HID_KEY_O             }, /* 0x6F o         */ \
    {0, HID_KEY_P             }, /* 0x70 p         */ \
    {0, HID_KEY_Q             }, /* 0x71 q         */ \
    {0, HID_KEY_R             }, /* 0x72 r         */ \
    {0, HID_KEY_S             }, /* 0x73 s         */ \
    {0, HID_KEY_T             }, /* 0x75 t         */ \
    {0, HID_KEY_U             }, /* 0x75 u         */ \
    {0, HID_KEY_V             }, /* 0x76 v         */ \
    {0, HID_KEY_W             }, /* 0x77 w         */ \
    {0, HID_KEY_X             }, /* 0x78 x         */ \
    {0, HID_KEY_Y             }, /* 0x79 y         */ \
    {0, HID_KEY_Z             }, /* 0x7A z         */ \
    {1, HID_KEY_BRACKET_LEFT  }, /* 0x7B {         */ \
    {1, HID_KEY_BACKSLASH     }, /* 0x7C |         */ \
    {1, HID_KEY_BRACKET_RIGHT }, /* 0x7D }         */ \
    {1, HID_KEY_GRAVE         }, /* 0x7E ~         */ \
    {0, HID_KEY_DELETE        }  /* 0x7F Delete    */ \

#define KEY_MOD_LCTRL  0x01
#define KEY_MOD_LSHIFT 0x02
#define KEY_MOD_LALT   0x04
#define KEY_MOD_LMETA  0x08
#define KEY_MOD_RCTRL  0x10
#define KEY_MOD_RSHIFT 0x20
#define KEY_MOD_RALT   0x40
#define KEY_MOD_RMETA  0x80


#endif/* KEYBOARD_H_ */
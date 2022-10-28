#ifndef MAPPING_H_
#define MAPPING_H_

#include <stdbool.h>
#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>
#ifdef USE_TINYUSB
#include <Adafruit_TinyUSB.h>
#endif

void keyboardSetup();

void button1();
void button2();
void button3();
void button4();
void button5();
void button6();
void button7();
void button8();
void button9();
void button10();
void button11();
void button12();
void button13();
void button14();
void button15();
void button16();
void button17();
void button18();
void button19();
void button20();
void button21();
void button22();
void button23();
void button24();
void button25();
void button26();
void button27();
void button28();
void button29();
void button30();
void button31();
void button32();
void action(uint8_t button);
#endif/* MAPPING_H_ */
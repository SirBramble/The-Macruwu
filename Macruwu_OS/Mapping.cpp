#include "Mapping.h"
#include "Keyboard.h"


Keyboard Keyboard1;

void keyboardSetup(){
  Keyboard1.init();
}

void button1(){
  Keyboard1.write("$$");
  Keyboard1.goLeft(1);
	Serial.println("Button1");
}

void button2(){
	Keyboard1.backslash();
  Keyboard1.write("infty");
  Serial.println("Button2");
}

void button3(){
  Keyboard1.backslash();
	Keyboard1.write("sqrt");
  Keyboard1.brackets(1);
	Serial.println("Button3");
}

void button4(){
	Keyboard1.writeKeycode(56, KEYBOARD_MODIFIER_LEFTSHIFT);
  Keyboard1.brackets(1);
	Serial.println("Button4");
}

void button5(){
	Keyboard1.backslash();
  Keyboard1.write("underline");
  Keyboard1.brackets(1);
	Serial.println("Button5");
}

void button6(){
	Keyboard1.writeKeycode(HID_KEY_GRAVE);
  Keyboard1.brackets(1);
	Serial.println("Button6");
}

void button7(){
	Keyboard1.write("e");
	Serial.println("Button7");
}

void button8(){
	Keyboard1.backslash();
	Keyboard1.write("frac");
  Keyboard1.brackets(0);
  Keyboard1.brackets(0);
  Keyboard1.goLeft(3);
	Serial.println("Button8");
}

void button9(){
	
	Serial.println("Button9");
}

void button10(){
	
	Serial.println("Button10");
}

void button11(){
	
	Serial.println("Button11");
}

void button12(){
	Keyboard1.backslash();
  Keyboard1.write("left");
  Keyboard1.writeKeycode(0x64, KEY_MOD_RALT);
  Keyboard1.backslash();
  Keyboard1.write("right");
  Keyboard1.writeKeycode(0x64, KEY_MOD_RALT);
  Keyboard1.goLeft(7);
	Serial.println("Button12");
}

void button13(){
  Keyboard1.backslash();
  Keyboard1.write("times ");
	Serial.println("Button13");
}

void button14(){
	Keyboard1.backslash();
  Keyboard1.write("vec ");
	Serial.println("Button14");
}

void button15(){
  Keyboard1.backslash();
  Keyboard1.write("left");
  Keyboard1.writeKeycode(0x25, KEY_MOD_RALT);
  Keyboard1.backslash();
  Keyboard1.write("begin");
  Keyboard1.brackets(1);
  Keyboard1.write("array");
  Keyboard1.goRight(1);
  Keyboard1.brackets(1);
  Keyboard1.write("c c");
  Keyboard1.goRight(1);
  Keyboard1.backslash();
  Keyboard1.backslash();
  Keyboard1.write(" ");
  Keyboard1.backslash();
  Keyboard1.write("end");
  Keyboard1.brackets(1);
  Keyboard1.write("array");
  Keyboard1.goRight(1);
  Keyboard1.backslash();
  Keyboard1.write("right");
  Keyboard1.writeKeycode(0x26, KEY_MOD_RALT);
  Keyboard1.goLeft(21);
	Serial.println("Button15");
}

void button16(){
  Keyboard1.backslash();
  Keyboard1.write("begin");
  Keyboard1.brackets(1);
  Keyboard1.write("pmatrix");
  Keyboard1.goRight(1);
  Keyboard1.backslash();
  Keyboard1.write("end");
  Keyboard1.brackets(1);
  Keyboard1.write("pmatrix");
  Keyboard1.goLeft(12);
	Serial.println("Button16");
}

void button17(){
	
	Serial.println("Button17");
}

void button18(){
	
	Serial.println("Button18");
}

void button19(){
	
	Serial.println("Button19");
}

void button20(){
	
	Serial.println("Button20");
}

void button21(){
  Keyboard1.backslash();
  Keyboard1.write("overbrace");
  Keyboard1.brackets();
  Keyboard1.writeKeycode(HID_KEY_GRAVE);
  Keyboard1.brackets();
  Keyboard1.goLeft(4);
	Serial.println("Button21");
}

void button22(){
	Keyboard1.backslash();
  Keyboard1.write("underbrace");
  Keyboard1.brackets();
  Keyboard1.writeKeycode(56, KEYBOARD_MODIFIER_LEFTSHIFT);
  Keyboard1.brackets();
  Keyboard1.goLeft(4);
	Serial.println("Button22");
}

void button23(){
  Keyboard1.backslash();
  Keyboard1.write("left.");
  Keyboard1.backslash();
  Keyboard1.write("begin");
  Keyboard1.brackets(1);
  Keyboard1.write("array");
  Keyboard1.goRight(1);
  Keyboard1.brackets(1);
  Keyboard1.write("c");
  Keyboard1.goRight(1);
  Keyboard1.backslash();
  Keyboard1.write("end");
  Keyboard1.brackets(1);
  Keyboard1.write("array");
  Keyboard1.goRight(1);
  Keyboard1.backslash();
  Keyboard1.write("right");
  Keyboard1.backslash();
  Keyboard1.writeKeycode(HID_KEY_0,KEYBOARD_MODIFIER_RIGHTALT);
  Keyboard1.goLeft(19);
	Serial.println("Button23");
}

void button24(){
	Keyboard1.backslash();
  Keyboard1.write("left");
  Keyboard1.backslash();
  Keyboard1.writeKeycode(HID_KEY_7,KEYBOARD_MODIFIER_RIGHTALT);
  Keyboard1.backslash();
  Keyboard1.write("begin");
  Keyboard1.brackets(1);
  Keyboard1.write("array");
  Keyboard1.goRight(1);
  Keyboard1.brackets(1);
  Keyboard1.write("c");
  Keyboard1.goRight(1);
  Keyboard1.backslash();
  Keyboard1.write("end");
  Keyboard1.brackets(1);
  Keyboard1.write("array");
  Keyboard1.goRight(1);
  Keyboard1.backslash();
  Keyboard1.write("right.");
  Keyboard1.goLeft(18);
	Serial.println("Button23");
	Serial.println("Button24");
}

void button25(){
	Keyboard1.backslash();
  Keyboard1.write("longmapsto ");
	Serial.println("Button25");
}

void button26(){
	Keyboard1.backslash();
  Keyboard1.write("Rightarrow ");
	Serial.println("Button26");
}

void button27(){
	Keyboard1.backslash();
  Keyboard1.write("overset");
  Keyboard1.brackets(1);
  Keyboard1.writeKeycode(HID_KEY_1, KEYBOARD_MODIFIER_LEFTSHIFT);
  Keyboard1.goRight(1);
  Keyboard1.brackets(1);
  Keyboard1.writeKeycode(HID_KEY_0, KEYBOARD_MODIFIER_LEFTSHIFT);
  Keyboard1.goRight(1);
  Keyboard1.write(" ");
	Serial.println("Button27");
}

void button28(){
	
	Serial.println("Button28");
}

void button29(){
	
	Serial.println("Button29");
}

void button30(){
	Keyboard1.backslash();
  Keyboard1.write("lim");
  Keyboard1.backslash();
  Keyboard1.write("limits");
  Keyboard1.writeKeycode(56, KEYBOARD_MODIFIER_LEFTSHIFT);
  Keyboard1.brackets(1);
	Serial.println("Button30");
}

void button31(){
	Keyboard1.backslash();
  Keyboard1.write("int");
  Keyboard1.backslash();
  Keyboard1.write("limits");
  Keyboard1.writeKeycode(56, KEYBOARD_MODIFIER_LEFTSHIFT);
  Keyboard1.brackets();
  Keyboard1.writeKeycode(HID_KEY_GRAVE);
  Keyboard1.brackets();
  Keyboard1.goLeft(4);
	Serial.println("Button31");
}

void button32(){
	Keyboard1.backslash();
  Keyboard1.write("sum");
  Keyboard1.backslash();
  Keyboard1.write("limits");
  Keyboard1.writeKeycode(56, KEYBOARD_MODIFIER_LEFTSHIFT);
  Keyboard1.brackets();
  Keyboard1.writeKeycode(HID_KEY_GRAVE);
  Keyboard1.brackets();
  Keyboard1.goLeft(4);
	Serial.println("Button32");
}

void action(uint8_t button){
	button++;
	switch(button){
		case 1:
			button1();
		break;

		case 2:
			button2();
		break;

		case 3:
			button3();
		break;

		case 4:
			button4();
		break;

		case 5:
			button5();
		break;

		case 6:
			button6();
		break;

		case 7:
			button7();
		break;

		case 8:
			button8();
		break;

		case 9:
			button9();
		break;

		case 10:
			button10();
		break;

		case 11:
			button11();
		break;

		case 12:
			button12();
		break;

		case 13:
			button13();
		break;

		case 14:
			button14();
		break;

		case 15:
			button15();
		break;

		case 16:
			button16();
		break;

		case 17:
			button17();
		break;

		case 18:
			button18();
		break;

		case 19:
			button19();
		break;

		case 20:
			button20();
		break;

		case 21:
			button21();
		break;

		case 22:
			button22();
		break;

		case 23:
			button23();
		break;

		case 24:
			button24();
		break;

		case 25:
			button25();
		break;

		case 26:
			button26();
		break;

		case 27:
			button27();
		break;

		case 28:
			button28();
		break;

		case 29:
			button29();
		break;

		case 30:
			button30();
		break;

		case 31:
			button31();
		break;

		case 32:
			button32();
		break;

	}
}
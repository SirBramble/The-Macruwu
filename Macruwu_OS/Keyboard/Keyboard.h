#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Interpreter.h"
#include "file_management.h"
#include <memory>


class Keyboard{
public:
    Keyboard(string filename = "macroLayout.txt");
    string get_string_from_file(int layer, int button);                         //Mainly for debugging
    void set_string_in_file(int layer, int button, string string_to_write);     //Mainly for debugging
    void readFile();
    void write(int layer, int button);
private:
    std::unique_ptr<Interpreter> interpreter_ptr;
    std::unique_ptr<Keymap> keymap_ptr;
};


#endif //KEYBOARD_H
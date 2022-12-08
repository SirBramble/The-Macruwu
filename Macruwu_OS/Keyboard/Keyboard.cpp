#include "Keyboard.h"

Keyboard::Keyboard(string filename){
    interpreter_ptr = std::unique_ptr<Interpreter>(new Interpreter());
    keymap_ptr = std::unique_ptr<Keymap>(new Keymap(filename));
    readFile();
}

void Keyboard::readFile(){
    keymap_ptr->import();
}

string Keyboard::get_string_from_file(int layer, int button){
    return keymap_ptr->get(layer, button);
}

void Keyboard::set_string_in_file(int layer, int button, string string_to_write){
    keymap_ptr->set(layer, button, string_to_write);
}
void Keyboard::write(int layer, int button){
    interpreter_ptr->interpret(keymap_ptr->get(layer,button));
}
#include "Keyboard.h"

Keyboard Macruwu;

int main(){
    

    cout << "Layer 1, Button 1: "<< Macruwu.get_string_from_file(1,1)<<endl;
    Macruwu.write(1,1);
    cout << "Layer 2, Button 1: "<< Macruwu.get_string_from_file(2,1)<<endl;
    Macruwu.write(2,1);
    cout << "Layer 3, Button 2: "<< Macruwu.get_string_from_file(3,2)<<endl;
    Macruwu.write(3,2);
    cout << "done" << endl;
    return 0;

}
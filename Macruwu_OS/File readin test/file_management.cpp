#include "file_management.h"

const char* digits = "0123456789";

//Layer
string Layer::get(int indexButton){
    return Button.at(indexButton);
}
void Layer::set(int indexButton, string funktionString){
    try {
        Button.at(indexButton) = funktionString;
    } catch (std::out_of_range const& exc) {
    }
    //Button.at(indexButton) = funktionString;
}


//Keymap

Keymap::Keymap(string filename){
    this->filename = filename;
}

string Keymap::get(int indexLayer, int indexButton){
    indexLayer--;
    indexButton--;
    if(indexLayer>=ammountLayers){return "";}
    return (&Layers.at(indexLayer))->get(indexButton);
}

void Keymap::set(int indexLayer, int indexButton, string funktionString){
    try {
        Layer *tmp = &Layers.at(indexLayer);
    } catch (std::out_of_range const& exc) {
        Layer newOne;
        Layers.push_back(newOne);
        ammountLayers++;
    }
    (&Layers.at(indexLayer))->set(indexButton, funktionString);
}

void Keymap::import(){
    string tmp;
    ifstream macroLayout;
    macroLayout.open(filename);

    while(getline(macroLayout, tmp)){
            if(tmp.find("Layer") != string::npos){
                currentLayer = getNum(tmp) - 1;
            }
            if(tmp.find("Button") != string::npos){
                set(currentLayer, getNum(tmp) - 1 , getString(tmp));
            }
    }

}

int Keymap::getNum(string tmp){
    int tmpPos_first = 0;
    int tmpPos_last = 0;
    int returnNumber = 0;
    tmpPos_first = tmp.find_first_of(digits);
    tmpPos_last = tmp.find_last_of(digits);
    char num[tmpPos_last - tmpPos_first + 1] = {0};
    tmp.copy(num, (tmpPos_last - tmpPos_first + 1), tmpPos_first);
    for(int i = 0; i < sizeof(num); i++){
        returnNumber *= 10;
        returnNumber = num[i] - 48;
    }
    return returnNumber;
}

string Keymap::getString(string tmp){
    int tmpPos_first;
    return tmp.substr(tmp.find_last_of(":") + 2);
}

Layer::Layer(){
    for(int i = 0; i < AMMOUNT_KEYS; i++){
        Button.push_back("");
    }
}
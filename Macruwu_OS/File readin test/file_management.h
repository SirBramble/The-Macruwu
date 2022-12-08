#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include "Interpreter.h"

#define AMMOUNT_KEYS 32

using namespace std;

class Layer{
    public:
        Layer();
        void set(int indexButton, string funktionString);
        string get(int indexButton);
    private:
        vector <string> Button;
};

class Keymap{
    public:
        Keymap(string filename);
        void import();
        string get(int indexlayer, int indexButton);    //für Bessere Verarbeitung sind übergabewerte nach der Textdatei angelegt
        void set(int Layer, int indexButton, string funktion_string);
    private:
        vector <Layer> Layers;
        int getNum(string tmp);
        string getString(string tmp);

        int currentLayer;
        int ammountLayers = 0;
        string filename;
};



#endif //FILE_MANAGEMENT_H
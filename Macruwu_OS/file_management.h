#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H
//#include <iostream>
//#include <fstream>
#include <vector>
#include <Arduino.h>


#define AMMOUNT_KEYS 32

void flash_setup();
void flash_loop();          //Returns contens of drive, when it is updated
void flash_test();          //debug funktion to test, if the filesystem works properly

bool check_fs_changed();
void set_fs_changed(bool fs_changed_in);

class Layer{
    public:
        Layer();
        void set(int indexButton, String funktionString);
        String get(int indexButton);
    private:
        std::vector <String> Button;
};

class Keymap{
    public:
        Keymap(String filename, int ammountLayers);
        void import();
        String get(int indexlayer, int indexButton);    //für Bessere Verarbeitung sind übergabewerte nach der Textdatei angelegt
        void set(int Layer, int indexButton, String funktion_string);
        void init();
    private:
        std::vector <Layer> Layers;
        int getNum(String tmp);
        String getString(String tmp);

        int currentLayer;
        int ammountLayers;
        String filename;
};



#endif //FILE_MANAGEMENT_H
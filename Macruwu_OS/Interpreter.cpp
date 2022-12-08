#include "Interpreter.h"

using namespace std;

void Interpreter::interpret(String stringToInterpret){
    stringToInterpret;
    char charToInterpret;
    bool inBuffer = 0;
    string buffer;
    for(uint32_t i = 0; i<stringToInterpret.length(); i++){
        charToInterpret = stringToInterpret.charAt(i);
        if(((charToInterpret >= 65)&&(charToInterpret <= 90))||((charToInterpret >= 97)&&(charToInterpret <= 122))){
            inBuffer = 1;
            buffer += charToInterpret;
            continue;
        }
        else if(inBuffer){
            //cout<<"send Buffer: "<<buffer<<endl;
            inBuffer = 0;
            continue;
        }
        if(charToInterpret == 92){                  // '\'
            //cout<<"Backslash"<<endl;
            continue;
        }
        if(charToInterpret == 123){                 // '{'
            if(stringToInterpret.charAt(i+1) == 125){   // '}'
                //cout<<"send double curly brace"<<endl;
            }
            else{
                //cout<<"send single curly brace open"<<endl;
            }
            continue;
        }
        if(charToInterpret == 125){                 // '}'
            //cout<<"send single curly brace closed"<<endl;
            continue;
        }
        if(charToInterpret == 91){                 // '['
            if(stringToInterpret.charAt(i+1) == 93){   // ']'
                //cout<<"send double square brace"<<endl;
            }
            else{
                //cout<<"send single square brace open"<<endl;
            }
            continue;
        }
        if(charToInterpret == 93){                 // ']'
            //cout<<"send single suqare brace closed"<<endl;
            continue;
        }
        if(charToInterpret == 94){                 // '^'     
            //cout<<"send funny to the power of symbol thingymabob"<<endl;
            continue;
        }
        else{
            //cout<<"you forgot to implement something you dummy"<<endl;
        }
    }
    if(inBuffer){
        //cout<<"sending Buffer: "<<buffer<<endl;
        inBuffer = 0;
    }
        
}
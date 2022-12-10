
#include "Expander.h"


bool Expander::getState(uint8_t pin){           //call with debounce time intervals and update first
  if(debounce()){
    if(state_db[pin] == 1){
      state_db[pin] = 0;
      //state_prev[pin] = 0;
      return 1;
    }
    else{
      return 0;  
    }
  }
  else if(state_db[pin] == 1){
    state_db[pin] = 0;
    //state_prev[pin] = 0;
    return 1;
  }
  else{
    return 0;
  }
}

Expander::Expander(uint8_t address_get){
  address = address_get;
  }

void Expander::update(){
  int i = 0;
  Wire.beginTransmission(address);
  Wire.write(0);                            //Send Register Byte
  Wire.endTransmission();
  Wire.requestFrom(address, 2, true);       //According to Datasheet, I/O Expander will send both Input registers, when one is Requested and the Master does not break the connection
  while(Wire.available()){
    input_reg[i] = Wire.read();
    i++;
    }
  splice();
  i = 0;
  }

bool Expander::debounce(){
  if((db_time_prev + DB_TIME) < millis()){
    db_time_prev = millis();
    update();
    for(uint8_t pin = 0; pin < 16; pin++){
      if((state_prev[pin] == 0) && (state[pin] == 0)){
        state_db[pin] = 0;
        }
      else if((state_prev[pin] == 0) && (state[pin] == 1)){
        state_prev[pin] = 1;
        state_db[pin] = 1;
        }
      else if((state_prev[pin] == 1) && (state[pin] == 0)){
        state_prev[pin] = 0;
        state_db[pin] = 0;
        }
      else if((state_prev[pin] == 1) && (state[pin] == 1)){
        state_db[pin] = 0;
        }
      }
      return 1;
    }
  else{
    return 0;
    }
  }

void Expander::splice(){
  for(int n = 0; n < 2; n++){
    for(int i = 0; i < 8; i++){
      state[i + (n*8)] = !(input_reg[n] & (1 << i));       //DENK DRAN: Switches werden auf 0 gezogen!!!!!!!! Hab dran gedacht :)
      }
    }
  }
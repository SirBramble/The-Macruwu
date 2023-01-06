
#include "Expander.h"


bool Expander::getState(uint8_t pin){           //call with debounce time intervals and update first
  if(pin >= PINCOUNT){
    return 0;
  }
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

bool Expander::getStatePulse(uint8_t pin){           //call with debounce time intervals and update first
  if(pin >= PINCOUNT){
    return 0;
  }
  if(debounce()){
    if(state_db_pulse[pin] == 1){
      state_db_pulse[pin] = 0;
      //state_prev[pin] = 0;
      return 1;
    }
    else{
      return 0;  
    }
  }
  else if(state_db_pulse[pin] == 1){
    state_db_pulse[pin] = 0;
    //state_prev[pin] = 0;
    return 1;
  }
  else{
    return 0;
  }
}


Expander::Expander(uint8_t address){
  this->address = address;
  }

void Expander::update(){
  int i = 0;
  Wire.beginTransmission(address);
  Wire.write(0);                            //Send Register Byte
  Wire.endTransmission();
  Wire.requestFrom(address, REGISTERCOUNT, true);       //According to Datasheet, I/O Expander will send both Input registers, when one is Requested and the Master does not break the connection
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
    for(uint8_t pin = 0; pin < PINCOUNT; pin++){
      switch(sm_state[pin]){
        case 0:
          if(state[pin] == 1){
            state_db[pin] = 0;
            state_db_pulse[pin] = 0;
            sm_state[pin] = 1;
          }
          break;
        case 1:
          if(state[pin] == 1){
            state_db[pin] = 0;
            state_db_pulse[pin] = 0;
            sm_state[pin] = 2;
          }
          else{
            sm_state[pin] = 0;
          }
          break;
        case 2:
          if(state[pin] == 1){
            state_db[pin] = 1;
            state_db_pulse[pin] = 1;
            sm_state[pin] = 3;
          }
          else{
            sm_state[pin] = 0;
          }
          break;
        case 3:
          if(state[pin] == 1){
            state_db[pin] = 1;
            state_db_pulse[pin] = 0;
          }
          else{
            state_db[pin] = 0;
            state_db_pulse[pin] = 0;
            sm_state[pin] = 0;
          }
          break;
        default:
          sm_state[pin] = 0;
          state_db[pin] = 0;
          break;
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
      state[i + (n*8)] = !(input_reg[n] & (1 << i));       //REMEMBER: Switches are pulled to GND/logic 0!!!!!!!! Edit: I remembered :)
      }
    }
  }
class Expander{
  public:
    uint8_t address;
    uint8_t state[16];
    uint8_t state_prev[16];
    uint8_t state_db[16];
    uint8_t input_reg[2];
    uint64_t db_time_prev = millis();
    bool getState(uint8_t pin){           //call with debounce time intervals and update first
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
    void init(uint8_t address_get){
      address = address_get;
      if(DEBUG == true){
        Serial.print("Initialised Expander on: ");
        Serial.println(address);
        }
      }
    void update(){
      if(DEBUG == true){
        Serial.print("called Expander ");
        Serial.print(address);
        Serial.println(" update");
        }
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
  private:
    bool debounce(){
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
    void splice(){
      if(DEBUG == true){
            Serial.println("Splice Funktion Output:");
            }
      for(int n = 0; n < 2; n++){
        for(int i = 0; i < 8; i++){
          state[i + (n*8)] = !(input_reg[n] & (1 << i));       //DENK DRAN: Switches werden auf 0 gezogen!!!!!!!!
          if(DEBUG == true){
            Serial.print(state[i + (n*8)]);
            Serial.print(" ");
            }
          }
        if(DEBUG == true){
          Serial.println("");
          }
        }
      }
   
    
  };
#include <Wire.h>

#define ADDone        //to be added
#define ADDtwo

class Expander{
  public:
    uint8_t address;
    uint8_t state[16];
    uint8_t input_reg[2];
    void init(uint8_t address_get){
      address = address_get;
      }
    void update(){
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
    void splice(){
      for(int n = 0; n < 2; n++){
        for(int i = 0; i < 8; i++){
          state[i + (n*8)] = input_reg[n] & (1 << i);       //DENK DRAN: Switches werden auf 0 gezogen!!!!!!!!
          }
        }
      }
   
    
  };

Expander Expander1
Expander Expander2


void setup() {
  Wire.begin();
  Expander1.init(ADDone);
  Expander2.init(ADDtwo);


}

void loop() {


  
}

#ifndef EXPANDER_H_
#define EXPANDER_H_

//#include <stdbool.h>
//#include <stdint.h>
//#ifdef USE_TINYUSB
//#include <Adafruit_TinyUSB.h>
//#endif
#include <Arduino.h>
#include <Wire.h>


#define DB_TIME 10              //in ms

// forward declaration
class Expander{
  public:
    Expander(uint8_t address_get);
    uint8_t address;
    uint8_t state[16];
    uint8_t state_prev[16];
    uint8_t state_db[16];
    uint8_t input_reg[2];
    uint64_t db_time_prev = millis();
    bool getState(uint8_t pin);
    void update();
     
  private:
    bool debounce();
     
    void splice();

};

#endif /* ADAFRUIT_FLASHCACHE_H_ */
#ifndef EXPANDER_H_
#define EXPANDER_H_

#include <Arduino.h>
#include <Wire.h>

#define PINCOUNT 16
#define REGISTERCOUNT 2
#define DB_TIME 5              //in ms

// forward declaration
class Expander{
  public:
    Expander(uint8_t address);
    bool getState(uint8_t pin);
    bool getStatePulse(uint8_t pin);
    void update();
     
  private:
    uint8_t address;
    uint8_t state[PINCOUNT];
    //uint8_t state_prev[16];
    uint8_t sm_state[PINCOUNT] = {0};
    uint8_t state_db[PINCOUNT] = {0};
    uint8_t state_db_pulse[PINCOUNT] = {0};
    uint8_t input_reg[REGISTERCOUNT];
    bool debounce();
    uint64_t db_time_prev = millis();
    void splice();
};

#endif /* ADAFRUIT_FLASHCACHE_H_ */
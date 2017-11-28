#pragma once

#include <Arduino.h>

class sensor {
private:
    volatile uint16_t counter = 0;
    volatile uint16_t temp_counter = 0;
    volatile uint16_t value = 0;
public:
    sensor(){};
    ~sensor(){};
    void event();
    void average();
    uint16_t getvalue();
};

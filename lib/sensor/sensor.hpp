#pragma once

#include <Arduino.h>

class sensor {
private:
    volatile int counter = 0;
    volatile int temp_counter = 0;
    volatile int value = 0;
public:
    sensor(){};
    ~sensor(){};
    void event();
    void average();
    uint16_t getvalue();
};

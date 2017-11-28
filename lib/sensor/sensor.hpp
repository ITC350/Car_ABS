#pragma once

#include <Arduino.h>

class sensor {
private:
    volatile int counter = 0;
    volatile int temp_counter = 0;
public:
    sensor();
    ~sensor();
    void event();
    uint16_t average();
};

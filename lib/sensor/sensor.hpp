#pragma once

#include <Arduino.h>

#ifndef MAXDATAINPUT
  #define MAXDATAINPUT 1024
#endif


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
    bool Datacollector();
    bool dataCorrupt;
    volatile uint8_t dataArr[MAXDATAINPUT]={0};
    volatile uint16_t dataArrItt = 0;
};

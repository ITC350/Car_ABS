#include "sensor.hpp"

void sensor::event() { 
    counter++;
} 
 
uint16_t sensor::average() { 
    temp_counter = counter;
    counter = 0;
    return temp_counter;
} 

#include "sensor.hpp"

void sensor::event() { 
    counter++;
} 
 
void sensor::average() { 
    value = counter;
    counter = 0;
} 

uint16_t sensor::getvalue() { 
    return value;
} 

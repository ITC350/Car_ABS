//
//  sensor.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#include "sensor.hpp"

sensor::sensor()  {}
sensor::~sensor() {}

void event(){ 
    ring_buffer[counter]=(TCNT5 - in_interval); 
    in_interval = TCNT5; 
    counter++; 
    if (counter == maxsize) { 
    counter = 0; 
    } 
} 
 
uint16_t average(){ 
    for (int i = 0; i < maxsize; i++) { 
        sum = sum + ring_buffer[i]; 
    } 
    return sum/maxsize; 
} 

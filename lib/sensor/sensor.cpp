//
//  sensor.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#include "sensor.hpp"

void sensor::event(){ 
    ring_buffer[counter]=(TCNT5 - in_interval); 
    in_interval = TCNT5; 
    counter++; 
    if (counter == MAXSIZE) { 
    counter = 0; 
    } 
} 
 
uint16_t sensor::average(){ 
    for (int i = 0; i < MAXSIZE; i++) { 
        sum = sum + ring_buffer[i]; 
    } 
    return sum/MAXSIZE; 
} 

#include "sensor.hpp"

void sensor::event() { 
    ring_buffer[counter]=(TCNT5 - in_interval); 
    in_interval = TCNT5;
    
    if (++counter == MAXSIZE) counter = 0;
}
 
uint16_t sensor::average() { 
    for (int i = 0; i < MAXSIZE; i++) { 
        sum += ring_buffer[i]; 
    }

    return sum/MAXSIZE; 
} 

//
//  sensor.hpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#ifndef sensor_hpp
#define sensor_hpp

#define MAXSIZE 5

#include <Arduino.h>

class sensor { 
private:
    uint16_t ring_buffer[MAXSIZE];
    volatile int counter = 0; 
    volatile uint16_t in_interval; 
    uint16_t sum; 
public: 
    sensor() {sum = 0;}
    ~sensor() {} 
    void event(); 
    uint16_t average(); 
protected: 
 
}; 


#endif /* sensor_hpp */

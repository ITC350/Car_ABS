//
//  sensor.hpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#ifndef sensor_hpp
#define sensor_hpp



class sensor { 
private: 
    const int maxsize = 5; 
    int ring_buffer[maxsize]; 
    volatile int counter = 0; 
    volatile uint16_t in_interval; 
    uint16_t sum; 
public: 
    sensor(); 
    ~sensor(); 
    void event(); 
    uint16_t average(); 
protected: 
 
}; 


#endif /* sensor_hpp */

//
//  servo.hpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//
#include <Arduino.h>
#ifndef servo_hpp
#define servo_hpp



class servo {
private:
  const int m_servoPin = 5;

public:
    typedef enum {LEFT=32, RIGHT=64, HALEFT=40, HARIGHT=56, CENTRUM=52}turn_val;
    servo();
    ~servo();
    void Servo_turn(turn_val dir);
protected:

};


#endif /* servo_hpp */

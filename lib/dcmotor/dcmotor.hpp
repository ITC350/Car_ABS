//
//  dcmotor.hpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//
#pragma once
//#ifndef dcmotor_hpp
//#define dcmotor_hpp
#include <Arduino.h>
//#include <stdint.h>


class dcmotor {
private:
  const uint8_t m_has_pin=10;
  const uint8_t m_reta_pin=11;
  const uint8_t m_retb_pin=12;
public:
    dcmotor();
    ~dcmotor();
    void Forward(uint8_t fwd_speed);
    void Backward(uint8_t bwd_speed);
    void Accelerator(uint8_t acc_to_spd);
protected:

};


//#endif /* dcmotor_hpp */

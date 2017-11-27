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
#include <PID_v1.h>
#include <sensor.hpp>

class dcmotor {
private:
  const uint8_t m_has_pin=10;
  const uint8_t m_reta_pin=11;
  const uint8_t m_retb_pin=12;
  double Setpoint, Input, Output;
  double Kp=2, Ki=5, Kd=1;
  PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  sensor m_sensors[4];
  void triggerISR1();
  void triggerISR2();
  void triggerISR3();
  void triggerISR4();
public:
    dcmotor(sensor sensors[4]);
    ~dcmotor();
    void Forward(uint8_t fwd_speed);
    void Backward(uint8_t bwd_speed);
    void Accelerator(uint8_t acc_to_spd, uint16_t acc_const);
protected:

};


//#endif /* dcmotor_hpp */

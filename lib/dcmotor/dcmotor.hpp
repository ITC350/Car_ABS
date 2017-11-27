//  dcmotor.hpp
//  Car_ABS
//  Created by <author> on 18/11/2017.

#pragma once
//#ifndef dcmotor_hpp
//#define dcmotor_hpp
#include <Arduino.h>
//#include <stdint.h>
#include <PID_v1.h>
#include "sensor.hpp"
#include "communication.hpp"

class dcmotor {
private:
  const uint8_t m_has_pin=10;
  const uint8_t m_reta_pin=11;
  const uint8_t m_retb_pin=12;
  PID myPID;
  double Setpoint, Input, Output;
  double Kp=2, Ki=5, Kd=0;
  uint16_t dataArr[1000];
  uint16_t dataArrItt = 0;
  communication m_comm;
public:
    dcmotor(communication &comm, uint16_t acc_const, uint8_t acc_to_speed, double kp, double ki, double kd);
    ~dcmotor();
    const uint32_t datafreq = 50;
    void Forward(uint8_t fwd_speed);
    void Backward(uint8_t bwd_speed);
    void Accelerator(uint8_t acc_to_spd, uint16_t acc_const);
    void emStop();
    static sensor m_sensors[4];
};


//#endif /* dcmotor_hpp */

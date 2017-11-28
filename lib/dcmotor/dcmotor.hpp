//  dcmotor.hpp
//  Car_ABS
//  Created by <author> on 18/11/2017.

#pragma once
#define MAXRUNTIME 15000
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
  uint8_t pwm = 15;
  communication m_comm;
  double Input, Output;
  //double Kp=2, Ki=0, Kd=0;
  double m_trgt_spd;
  PID myPID;
  uint16_t m_acc_const;
  uint16_t m_datafreq;

public:
    dcmotor(communication &comm, uint16_t acc_const, uint16_t datafreq, double trgt_spd, double kp, double ki, double kd);
    ~dcmotor();
    void Forward(uint8_t fwd_speed);
    void Backward(uint8_t bwd_speed);
    void Accelerator();
    void emStop();
    void pid();
    void ABS();
    uint16_t dataArr[1024] = {0};
    uint16_t dataArrItt = 0;
};


//#endif /* dcmotor_hpp */

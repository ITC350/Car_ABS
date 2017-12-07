//  dcmotor.hpp
//  Car_ABS
//  Created by <author> on 18/11/2017.

#pragma once

//#ifndef dcmotor_hpp
//#define dcmotor_hpp
#include <Arduino.h>
#include <avr/wdt.h>
//#include <stdint.h>
//#include <PID_v1.h>
#include "sensor.hpp"
#include "communication.hpp"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#ifndef MAXDATAINPUT
  #define MAXDATAINPUT 1024
#endif

class dcmotor {
private:
  const uint8_t m_has_pin=10;
  const uint8_t m_reta_pin=11;
  const uint8_t m_retb_pin=12;
  uint8_t pwm = 30;
  communication m_comm;
  double m_kp, m_ki, m_kd;
  //double Kp=2, Ki=0, Kd=0;
  uint16_t m_trgt_spd;
  //PID myPID;
  uint16_t m_acc_const;
  uint16_t pid_sampletime = 100;
  uint16_t lastTimepid;
  int val = 0;
  uint16_t m_datafreq;
  uint16_t state[MAXDATAINPUT] = {0};

public:
    dcmotor(communication &comm, uint16_t acc_const, uint16_t datafreq, uint16_t trgt_spd, double kp, double ki, double kd);
    ~dcmotor();
    void Forward(uint8_t fwd_speed);
    void Backward(uint8_t bwd_speed);
    void Accelerator();
    void emStop();
    bool pid();
    void ABS(uint8_t abs_const, uint8_t abs_delay);
    void ABS2(uint8_t, uint8_t, uint8_t);
    bool detect(int border);
    uint8_t *dataOut(uint8_t);
    void ittReset();
    uint16_t *stateOut();
};

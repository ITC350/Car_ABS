//  dcmotor.hpp
//  Car_ABS
//  Created by <author> on 18/11/2017.

#pragma once
#define MAXRUNTIME 4000
//#ifndef dcmotor_hpp
//#define dcmotor_hpp
#include <Arduino.h>
#include <avr/wdt.h>
//#include <stdint.h>
//#include <PID_v1.h>
#include "sensor.hpp"
#include "communication.hpp"

class dcmotor {
private:
  const uint8_t m_has_pin=10;
  const uint8_t m_reta_pin=11;
  const uint8_t m_retb_pin=12;
  uint8_t pwm = 20;
  communication m_comm;
  double m_kp, m_ki, m_kd;
  //double Kp=2, Ki=0, Kd=0;
  uint16_t m_trgt_spd;
  //PID myPID;
  uint16_t m_acc_const;
  uint16_t m_datafreq;
  uint16_t pid_sampletime = 50;
<<<<<<< HEAD
  uint16_t lastTimepid;
  uint16_t lastTimeData;
=======
  int val = 0;
>>>>>>> f47a84abdb8ffaca405bf5a78a37c4ff76c5c982

public:
    dcmotor(communication &comm, uint16_t acc_const, uint16_t datafreq, uint16_t trgt_spd, double kp, double ki, double kd);
    ~dcmotor();
    void Forward(uint8_t fwd_speed);
    void Backward(uint8_t bwd_speed);
    void Accelerator();
    void emStop();
    void pid();
    void ABS();
    uint16_t dataArr[1024] = {0};
    uint16_t dataArrItt = 0;
    bool detect(int sort, int hvid);
};


//#endif /* dcmotor_hpp */

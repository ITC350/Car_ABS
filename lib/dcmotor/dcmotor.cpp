//
//  dcmotor.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#include "dcmotor.hpp"
//#include <stdint.h>

dcmotor::dcmotor(sensor sensors[4])  {
  pinMode(m_has_pin, OUTPUT);
  pinMode(m_reta_pin, OUTPUT);
  pinMode(m_retb_pin, OUTPUT);

  for (uint8_t i = 0; i < 4; ++i) {
      m_sensors[i] = sensors[4];
  }
}
dcmotor::~dcmotor() {}

void dcmotor::Forward(uint8_t fwd_speed){
  analogWrite(m_has_pin, fwd_speed);
  digitalWrite(m_reta_pin,HIGH);
  digitalWrite(m_retb_pin,LOW);
}

void dcmotor::Backward(uint8_t bwd_speed){
  analogWrite(m_has_pin, bwd_speed);
   digitalWrite(m_reta_pin,LOW);
   digitalWrite(m_retb_pin,HIGH);
}

void dcmotor::emStop(){
    analogWrite(m_has_pin, 0);
     digitalWrite(m_reta_pin,LOW);
     digitalWrite(m_retb_pin,LOW);
}

void dcmotor::Accelerator(uint8_t acc_to_spd, uint16_t acc_const){
    uint8_t pwm = 1;
    Forward(pwm);
    uint32_t cur_time = 0;
    while(pwm < 255){
        if(millis() - cur_time >= acc_const){
            ++pwm;
            Forward(pwm);
        }
        if (sensor.input1 = acc_to_spd//-something) {
            //break or return;
        }
    }
}

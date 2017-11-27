//
//  dcmotor.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#include "dcmotor.hpp"
//#include <stdint.h>

dcmotor::dcmotor(); myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT)  {
  pinMode(m_has_pin, OUTPUT);
  pinMode(m_reta_pin, OUTPUT);
  pinMode(m_retb_pin, OUTPUT);

  //sensor
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(18), triggerISR1, HIGH); //attach interrupt
  attachInterrupt(digitalPinToInterrupt(19), triggerISR2, HIGH); //attach interrupt
  attachInterrupt(digitalPinToInterrupt(2), triggerISR3, HIGH); //attach interrupt
  attachInterrupt(digitalPinToInterrupt(3), triggerISR4, HIGH); //attach interrupt

  noInterrupts();//stop interrupts

  //Timer5 16 bit
  //  #######################################################
  TCCR5A = 0;               //set entire TCCR1A register to 0
  TCCR5B = 0;               //set entire TCCR1B register to 0
  TCNT5 = 0;                //Register for timer value

  TCCR5B |= (1 << CS52) | (1 << CS50);    // prescaler
  TCCR1B |= (0 << WGM52);   //Normal mode

  interrupts();//allow interrupts


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

void PID(){

}

void dcmotor::Accelerator(uint8_t acc_to_spd, uint16_t acc_const){
    uint8_t pwm = 1;
    Forward(pwm);
    uint32_t cur_time = 0;
    uint32_t cur_time2 = 0;
    while(pwm < 255){
        if(millis() - cur_time >= acc_const){
            cur_time=millis();
            ++pwm;
            Forward(pwm);
        }
        if (millis()-cur_time2>=datafreq){
          dataArr[dataArrItt]=m_sensors[1].average;
          ++dataArrItt;
        }
        if (m_sensors[1].average = (acc_to_spd*3)/4) {
            break;
        }
    }
    PID();
}

void dcmotor::triggerISR1(){
    m_sensors[0].event();
}
void dcmotor::triggerISR2(){
    m_sensors[1].event();
}
void dcmotor::triggerISR3(){
    m_sensors[2].event();
}
void dcmotor::triggerISR4(){
    m_sensors[3].event();
}

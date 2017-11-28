//
//  dcmotor.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#include "dcmotor.hpp"
//#include <stdint.h>

void triggerISR1(){
    dcmotor::m_sensors[0].event();
}
void triggerISR2(){
    dcmotor::m_sensors[1].event();
}
void triggerISR3(){
    dcmotor::m_sensors[2].event();
}
void triggerISR4(){
    dcmotor::m_sensors[3].event();
}
ISR(TIMER1_COMPA_vect) { //timer1 interrupt
    m_sensors[0].average()
    m_sensors[1].average()
    m_sensors[2].average()
    m_sensors[3].average()
}


dcmotor::dcmotor(communication &comm, uint16_t acc_const, uint8_t trgt_spd, double kp, double ki, double kd)
    :m_comm(comm),
    myPID(&Input, &Output, &trgt_spd, kp, ki, kd, DIRECT)  {
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

  //Timer1 16 bit
  TCCR1A = 0;               //set entire TCCR1A register to 0
  TCCR1B = 0;               //set entire TCCR1B register to 0
  TCNT1 = 0;                //Register for timer value

  OCR1A = 1250;            //compare match register 16MHz/256/50Hz  50 hz timer
  TCCR1B |= (1 << WGM12);   //CTC mode
  TCCR1B |= (1 << CS12);    //256 prescaler
  TIMSK1 |= (1 << OCIE1A);  //enable timer compare interrupt

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

void dcmotor::pid(){

    //initialize the variables we're linked to
    Input = m_sensors[1].average();

    //turn the PID on
    myPID.SetMode(AUTOMATIC);

    while(1){
        if(m_comm.check_halt())emStop();
    Input = m_sensors[1].average();
    myPID.Compute();
    analogWrite(m_has_pin, Output);
  }
}

void dcmotor::Accelerator(){
    uint8_t pwm = 1;
    Forward(pwm);
    uint32_t cur_time = 0;
    uint32_t cur_time2 = 0;
    while(pwm < 255){
        if(m_comm.check_halt())emStop();
        if(millis() - cur_time >= acc_const){
            cur_time=millis();
            ++pwm;
            Forward(pwm);
        }
        if (millis()-cur_time2>=datafreq){
          dataArr[dataArrItt] = m_sensors[1].average();
          ++dataArrItt;
        }
        if (m_sensors[1].average() == (trgt_spd*3)/4) {
            break;
        }
    }
    pid();
}

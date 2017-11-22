//
//  dcmotor.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//
#include <Aduino.h>
#include "dcmotor.hpp"

dcmotor::dcmotor()  {
  pinMode(dc_has, OUTPUT);
  pinMode(dc_ret1, OUTPUT);
  pinMode(dc_ret2, OUTPUT);
}
dcmotor::~dcmotor() {}

void Forward(){
  analogWrite(dc_has, 35);
  digitalWrite(dc_ret1,HIGH);
  digitalWrite(dc_ret2,LOW);
  delay(1000);
}

void Backward(){
  analogWrite(dc_has, 35);
   digitalWrite(dc_ret1,LOW);
   digitalWrite(dc_ret2,HIGH);
   delay(1000);
}

//
//  servo.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#include "servo.hpp"

servo::servo()  {
  TCCR3B = TCCR3B & 0b11111000 | 0x04;
  pinMode(m_servoPin, OUTPUT);
}
void servo::Servo_turn(turn_val dir){
  analogWrite(m_servoPin, dir);
}
servo::~servo() {}

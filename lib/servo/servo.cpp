//
//  servo.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#include "servo.hpp"
bool state;
//Timer interrrput
/*ISR(TIMER3_COMPA_vect) { //timer3 interrupt
  digitalWrite(5, state);
  state = !state;
}*/

servo::servo()  {

  pinMode(m_servoPin, OUTPUT);
analogWrite(m_servoPin, 127);
/*    noInterrupts();//stop interrupts
  //Timer3 16 bit
  TCCR3A = 0;               //set entire TCCR1A register to 0
  TCCR3B = 0;               //set entire TCCR1B register to 0
  TCNT3 = 0;                //Register for timer value

  OCR3A = 62500/500;            //compare match register 16MHz/256/1Hz  1 hz timer
  TCCR3B |= (1 << WGM32);   //CTC mode
  TCCR3B |= (1 << CS32);    //256 prescaler
  TIMSK3 |= (1 << OCIE3A);  //enable timer compare interrupt

  interrupts();//allow interrupts
*/
}
void servo::Servo_turn(uint16_t dir){
    analogWrite(m_servoPin, dir);
    /*if(dir < 1000 && dir > 500){
        OCR3A = 62500/dir;
    }*/
}
servo::~servo() {}

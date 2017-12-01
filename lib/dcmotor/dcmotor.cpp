//  dcmotor.cpp
//  Car_ABS
//  Created by ITC350 on 18/11/2017.

#include "dcmotor.hpp"
//#include <stdint.h>

sensor m_sensors[4];

void triggerISR1() { m_sensors[0].event(); }
void triggerISR2() { m_sensors[1].event(); }
void triggerISR3() { m_sensors[2].event(); }
void triggerISR4() { m_sensors[3].event(); }
// Timer interrrput
ISR(TIMER1_COMPA_vect) { // timer1 interrupt
  m_sensors[0].average();
  m_sensors[1].average();
  m_sensors[2].average();
  m_sensors[3].average();
}

ISR(WDT_vect) {
  analogWrite(10, 0);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

dcmotor::dcmotor(communication &comm, uint16_t acc_const, uint16_t datafreq,
                 uint16_t trgt_spd, double kp, double ki, double kd)
    : m_comm(comm), m_trgt_spd(trgt_spd), m_kp(kp), m_ki(ki), m_kd(kd),
      // myPID(&Input, &Output, &m_trgt_spd, kp, ki, kd, DIRECT),
      m_datafreq(datafreq), m_acc_const(acc_const) {

  if (m_trgt_spd > 26)
    m_trgt_spd = 26;

  pinMode(m_has_pin, OUTPUT);
  pinMode(m_reta_pin, OUTPUT);
  pinMode(m_retb_pin, OUTPUT);

  // sensor
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(18), triggerISR1,
                  HIGH); // attach interrupt
  attachInterrupt(digitalPinToInterrupt(19), triggerISR2,
                  HIGH); // attach interrupt
  attachInterrupt(digitalPinToInterrupt(2), triggerISR3,
                  HIGH); // attach interrupt
  attachInterrupt(digitalPinToInterrupt(3), triggerISR4,
                  HIGH); // attach interrupt

  noInterrupts(); // stop interrupts
  // Timer1 16 bit
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // set entire TCCR1B register to 0
  TCNT1 = 0;  // Register for timer value

  OCR1A = 62500 / 50;      // compare match register 16MHz/256/50Hz  50 hz timer
  TCCR1B |= (1 << WGM12);  // CTC mode
  TCCR1B |= (1 << CS12);   // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt

  interrupts(); // allow interrupts
  Serial.print("dataFreq: ");
  Serial.println(m_datafreq);
  Serial.print("accconst: ");
  Serial.println(m_acc_const);
  Serial.print("trgt_spd: ");
  Serial.println(m_trgt_spd);

  delay(1000);
}
dcmotor::~dcmotor() {}

void dcmotor::Forward(uint8_t fwd_speed) {
  analogWrite(m_has_pin, fwd_speed);
  digitalWrite(m_reta_pin, HIGH);
  digitalWrite(m_retb_pin, LOW);
}

void dcmotor::Backward(uint8_t bwd_speed) {
  analogWrite(m_has_pin, bwd_speed);
  digitalWrite(m_reta_pin, LOW);
  digitalWrite(m_retb_pin, HIGH);
}

void dcmotor::emStop() {
  analogWrite(m_has_pin, 0);
  digitalWrite(m_reta_pin, LOW);
  digitalWrite(m_retb_pin, LOW);
}

void dcmotor::pid() {
    uint32_t cur_time2 = 0;
    uint32_t timerset = millis();
    uint16_t pid_time_change = (timerset - lastTimepid);
    uint16_t data_time_change = (timerset - lastTimeData);
    double outputSum = pwm;
    // initialize the variables we're linked to turn the PID on
    // myPID.SetMode(AUTOMATIC);
    // if(m_comm.check_halt())emStop();
    if (pid_time_change >= pid_sampletime) { // PID compute

        uint16_t input = m_sensors[1].getvalue();
        int16_t error = m_trgt_spd - input;
        outputSum += (m_ki * error);  // I delen udregnes
        double output = m_kp * error; // P delen udregnes
        output += outputSum;

        if (output > 255)output = 255; // sørger for output holder sig inden for range
        else if (output < 0)output = 0; // myPID.Compute();

        analogWrite(m_has_pin, output);
        lastTimepid = timerset;
    }
    if (data_time_change >= m_datafreq) {
        cur_time2 = millis();
        dataArr[dataArrItt] = m_sensors[1].getvalue();
        ++dataArrItt;
        Serial.println(m_sensors[2].getvalue());
        lastTimeData = timerset;
    }


}


void dcmotor::Accelerator() {
  /*Sørger for at bilen kan accelerrere langsomt op så hjulspind kan undgåes*/
  noInterrupts(); // Watchdog initialiceres
  wdt_reset();    // reset the WDT timer
  /*
  WDTCSR configuration:
  WDIE = 1: Interrupt Enable
  WDE = 0 :Reset Disable
  WDP3 = 1 :For 4000ms Time-out
  WDP2 = 0 :For 4000ms Time-out
  WDP1 = 0 :For 4000ms Time-out
  WDP0 = 0 :For 4000ms Time-out
  */
  // Enter Watchdog Configuration mode:
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  // Set Watchdog settings:
  WDTCSR = (1 << WDIE) | (0 << WDE) | (1 << WDP3) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0); // resetter watchdog så bilen kører maks 4 sek.

  interrupts();

  Forward(pwm);
  uint32_t cur_time = 0;
  uint32_t cur_time2 = 0;

  while (pwm < 255) {
    // if(m_comm.check_halt())emStop();
    // Serial.print("pwm: ");Serial.println(pwm);
    if (millis() - cur_time >= m_acc_const)
    {
    // kontroller om der er gået acc_const i ms og øger derefter outputtet til motoren.
      cur_time = millis();
      ++pwm;
      analogWrite(m_has_pin, pwm);    }
    if (millis() - cur_time2 >=
        m_datafreq) { // gemmer data i arrary med en frekvens sat i datafreq
      cur_time2 = millis();
      dataArr[dataArrItt] = m_sensors[1].getvalue();
      ++dataArrItt;
      Serial.println(m_sensors[2].getvalue());
    }
    if (m_sensors[1].getvalue() >= (m_trgt_spd * 7) / 8)return; // Ved tre fjerdedele af den ønsket hastighed stoppes accelerationen
    /*Serial.print("spd: ");Serial.println(m_sensors[1].getvalue());
    Serial.print("pwm: ");Serial.println(pwm);
    delay(1000);*/
  }
  return;
}

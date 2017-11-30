#include <Arduino.h>
#include "servo.hpp"
#include "sensor.hpp"
#include "dcmotor.hpp"
#include "communication.hpp"






void setup() {

  double Kp = 0, Ki = 0, Kd = 0; //Kp=0.4 Ki=0.005 Kd=0
  uint16_t target_speed = 0;
  uint16_t acc_const = 0;
  uint16_t data_freq = 0;
  bool disable_abs = true;

  servo myServo;
  communication comm(Serial1);
  comm.receive();
  dcmotor motor(comm, acc_const, data_freq, target_speed, Kp, Ki, Kd);

  myServo.Servo_turn(661);
  delay(2000);
  motor.Accelerator();
  motor.pid();
  //motor.emStop();
  for (uint8_t i = 0; i < DEFAULT_RECV_SIZE; i++) {
    switch (comm.recv_msg[i]) {
      case NOP:
        break;
      case SETTINGS:
        Kp = (float)comm.recv_msg[++i];
        Ki = (float)comm.recv_msg[++i];
        Kd = (float)comm.recv_msg[++i];
        target_speed = comm.recv_msg[++i];
        acc_const = comm.recv_msg[++i];
        data_freq = comm.recv_msg[++i];
        break;
      case DISABLE_ABS:
        disable_abs = false;
        break;
      case START: {
          dcmotor motor(comm, acc_const, data_freq, target_speed, Kp, Ki, Kd);
          //motor.Accelerator();
          //motor.pid();
          //motor.ABS();
          comm.send((uint8_t *)motor.dataArr, 2048);
        }
        break;
      default:
        return;
    }

  }

  comm.send((uint8_t *)comm.recv_msg, 40);

}

void loop() {
  // put your main code here, to run repeatedly:

}

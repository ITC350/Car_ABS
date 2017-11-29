#include <Arduino.h>
#include "servo.hpp"
#include "sensor.hpp"
#include "dcmotor.hpp"
#include "communication.hpp"


void setup() {
  double Kp = 0, Ki = 0, Kd = 0;
  uint16_t target_speed = 0; //check om uint16 er ok
  uint16_t acc_const = 0;
  uint16_t data_freq = 0;
  bool disable_abs = true;

  communication comm(Serial1);
  comm.receive();

  for (uint8_t i = 0; i < DEFAULT_RECV_SIZE; i++) {
    switch (comm.recv_msg[i]) {
      case NOP:
        break;
      case SETTINGS:
        Kp = 1.0 * comm.recv_msg[++i];
        Ki = 1.0 * comm.recv_msg[++i];
        Kd = 1.0 * comm.recv_msg[++i];
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
          comm.send((uint8_t *)motor.dataArr, motor.dataArrItt * 2);
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

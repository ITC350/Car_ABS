#include <Arduino.h>
#include "servo.hpp"
#include "sensor.hpp"
#include "dcmotor.hpp"
#include "communication.hpp"


void setup() {
  double Kp = 0, Ki = 0, Kd = 0;
  double target_speed = 0;
  uint32_t acc_const = 0;
  uint32_t data_freq = 0;
  bool disable_abs = true;

  communication comm(Serial);
  comm.receive();

  for (uint8_t i = 0; i < DEFAULT_RECV_SIZE; i++) {
    switch (comm.recv_msg[i]) {
      case NOP:
        break;
      case SETTINGS:
        Kp = comm.recv_msg[++i] * 1.0; // 2
        Ki = comm.recv_msg[++i] * 1.0; // 0
        Kd = comm.recv_msg[++i] * 1.0; // 0
        target_speed = comm.recv_msg[++i] * 1.0; // 500
        acc_const = comm.recv_msg[++i]; // 50
        data_freq = comm.recv_msg[++i]; // 50
        break;
      case DISABLE_ABS:
        disable_abs = false;
        break;
      case START: {
          dcmotor motor(comm, acc_const, data_freq, target_speed, Kp, Ki, Kd);
          motor.Accelerator();
          motor.pid();
          //motor.ABS();
          comm.send(motor.dataArr, motor.dataArrItt);
        }
        break;
      default:
        return;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

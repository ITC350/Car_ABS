#include <Arduino.h>
#include "servo.hpp"
#include "sensor.hpp"
#include "dcmotor.hpp"
#include "communication.hpp"






void setup() {
    pinMode(41,INPUT_PULLUP);
    double Kp = 0.4, Ki = 0.0001, Kd = 0; //Kp=0.4 Ki=0.005 Kd=0
    uint16_t target_speed = 15; //10
    uint16_t acc_const = 75;   //100
    uint16_t data_freq = 1000;   //1000
    bool disable_abs = true;

    servo myServo;
    communication comm(Serial);
    //comm.receive();
    dcmotor motor(comm, acc_const, data_freq, target_speed, Kp, Ki, Kd);

    myServo.Servo_turn(201);
    delay(2000);
    motor.ittReset();
    motor.Accelerator();
    while (!motor.detect(150)) {
        if(!motor.pid())break;
    }

    //motor.emStop();
    //motor.Backward(20);
    //motor.Forward(10);
    //while(!motor.detect(150));
    //motor.emStop();
    motor.ABS2(20,1,1000);
    //motor.ABS(uint8_t abs_const);
    while(digitalRead(41));

    comm.serial_printout(motor.dataOut(0), motor.dataOut(1),
                         motor.dataOut(2), motor.dataOut(3),
                         motor.stateOut());

  //motor.emStop();

  //motor.Accelerator();
  //motor.pid();
  //motor.emStop();
  /*for (uint8_t i = 0; i < DEFAULT_RECV_SIZE; i++) {
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
          motor.Accelerator();
          motor.pid();
          //motor.ABS();
          comm.send((uint8_t *)motor.dataArr, 2048);
        }
        break;
      default:
        return;
    }

}*/


}

void loop() {
  // put your main code here, to run repeatedly:

}

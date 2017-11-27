#pragma once

#include <Arduino.h>

#include "opcode.hpp"
#include "communication.hpp"
#include "dcmotor.hpp"
#include "servo.hpp"
#include "sensor.hpp"


class scheduler {
private:
    communication m_comm;
    dcmotor m_motor;
    servo m_servo;

public:
    void start_test();
    scheduler(communication& comm, dcmotor& motor, servo& servo);
    ~scheduler();
protected:

};

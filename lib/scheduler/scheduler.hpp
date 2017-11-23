#pragma once

#include <Arduino.h>

#include "opcode.hpp"
#include "communication.hpp"

class scheduler {
private:
    communication m_comm;
public:
    void start(uint8_t commands[16]);
    scheduler(communication comm);
    ~scheduler();
protected:

};
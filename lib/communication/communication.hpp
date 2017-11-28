#pragma once

#include <Arduino.h>
#include "opcode.hpp"

#define DEFAULT_RECV_SIZE 32

class communication {
private:
    HardwareSerial m_serial;
    const uint16_t baud_rate = 9600;
    uint8_t recv_single_byte();
    uint32_t recv_quad();
    
public:
    communication(HardwareSerial serial);
    ~communication();
    uint32_t recv_msg[DEFAULT_RECV_SIZE];
    void receive();
    void send(uint8_t msg[32]);
    bool check_halt();
};

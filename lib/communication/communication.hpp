#pragma once

#include <Arduino.h>
#include "opcode.hpp"

#define DEFAULT_RECV_SIZE 16

class communication {
private:
    HardwareSerial m_serial;
    const uint16_t baud_rate = 9600;
    uint32_t recv_msg[DEFAULT_RECV_SIZE];
    uint8_t recv_single_byte();
    double recv_double();
    
public:
    communication(HardwareSerial serial);
    ~communication();
    uint32_t *receive();
    void send(uint8_t msg[32]);
    bool check_halt();
};

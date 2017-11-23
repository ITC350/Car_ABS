//
//  communication.hpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#pragma once

#include <Arduino.h>
#include "opcode.hpp"

class communication {
private:
    HardwareSerial m_serial;
    const uint16_t baud_rate = 9600;
    uint8_t rec_msg[16];

public:
    communication(HardwareSerial& serial);
    ~communication();
    uint8_t *receive_cmds();
    void send(uint8_t msg[32]);
    bool is_halt();

protected:

};

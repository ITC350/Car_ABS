//
//  communication.cpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#include "communication.hpp"

communication::communication()
  : m_serial(serial)
{
    serial.begin(baud_rate);
}
communication::~communication()
{
    serial.end();
}

uint8_t *communication::receive_cmds()
{
    for (size_t i = 0; i < 16; i++)
    {
        if(serial.available())
        {
            rec_msg[i] = serial.read();
        }
    }
    return rec_msg;
}

bool is_halt()
{
    return serial.read() == HALT;
}

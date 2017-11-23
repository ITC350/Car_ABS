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

uint8_t *communication::receive()
{
    serial.read();
}

#include "communication.hpp"

communication::communication(HardwareSerial serial)
  : m_serial(serial)
{
    serial.begin(baud_rate);
}
communication::~communication()
{
    m_serial.end();
}

uint8_t *communication::receive_cmds()
{
    for (size_t i = 0; i < 16; i++)
    {
        if(m_serial.available())
        {
            rec_msg[i] = m_serial.read();
        }
    }
    return rec_msg;
}

bool communication::is_halt()
{
    return m_serial.read() == HALT;
}

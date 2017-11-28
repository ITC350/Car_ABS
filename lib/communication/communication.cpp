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

uint8_t communication::recv_single_byte()
{
    if (m_serial.available())
    {
        return m_serial.read();
    }
}

double communication::recv_double()
{
    uint32_t d = 0;

    d += recv_single_byte() << 0x20;
    d += recv_single_byte() << 0x18;
    d += recv_single_byte() << 0x10;
    d += recv_single_byte() << 0x08;

    return (double)d;
}

void communication::receive()
{
    uint32_t op = 0;

    for (size_t i = 0; i < DEFAULT_RECV_SIZE; i++)
    {
        op = recv_single_byte();
        
        switch (op) {
            case NOP:
                recv_msg[i] = NOP;
                break;
            case START:
                recv_msg[i] = START;
                break;
            case ACCELERATE:
                recv_msg[i] = ACCELERATE;
                recv_msg[++i] = recv_single_byte();
                break;
            case DISABLE_ABS:
                recv_msg[i] = DISABLE_ABS;
                break;
            case EPID:
                recv_msg[i] = EPID;
                recv_msg[++i] = recv_double();
                recv_msg[++i] = recv_double();
                recv_msg[++i] = recv_double();
                break;
            default:
                return NULL;
        }
    }
    return recv_msg;
}

bool communication::check_halt()
{
    return m_serial.read() == HALT;
}

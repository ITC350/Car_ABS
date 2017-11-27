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

    d += recv_single_byte() << 32;
    d += recv_single_byte() << 24;
    d += recv_single_byte() << 16;
    d += recv_single_byte() << 8;

    return (double)d;
}

uint32_t *communication::receive()
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
            case HALT:
                recv_msg[0] = HALT;
                return recv_msg;
            case ACCELERATE:
                recv_msg[i] = ACCELERATE;
                recv_msg[++i] = recv_single_byte();
                break;
            case DISABLE_ABS:
                recv_msg[i] = DISABLE_ABS;
                break;
            case PID:
                recv_msg[i] = PID;
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

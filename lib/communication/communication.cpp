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

uint32_t communication::recv_quad()
{
    uint32_t q = 0;

    q += recv_single_byte() << 0x08;
    q += recv_single_byte() << 0x10;
    q += recv_single_byte() << 0x18;
    q += recv_single_byte() << 0x20;

    return q;
}

void communication::receive()
{
    uint32_t op = 0;

    recv_single_byte();
    recv_single_byte();

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
            case DISABLE_ABS:
                recv_msg[i] = DISABLE_ABS;
                break;
            case SETTINGS:
                recv_msg[i] = SETTINGS;
                recv_msg[++i] = recv_quad();
                recv_msg[++i] = recv_quad();
                recv_msg[++i] = recv_quad();
                recv_msg[++i] = recv_quad();
                recv_msg[++i] = recv_quad();
                recv_msg[++i] = recv_quad();
                break;
            default:
                return;
        }
    }
    return;
}

bool communication::check_halt()
{
    return m_serial.read() == HALT;
}

void communication::send(uint16_t msg[1024], size_t length)
{
    m_serial.write((uint8_t *)msg, length * 2);
}
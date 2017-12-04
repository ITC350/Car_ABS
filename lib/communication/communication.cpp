#include "communication.hpp"

communication::communication(HardwareSerial &serial)
  : m_serial(serial)
{
    m_serial.begin(baud_rate);
}

communication::~communication()
{
    m_serial.end();
}

uint8_t communication::recv_single_byte()
{
    while (!m_serial.available()) {}
    return m_serial.read();
}

uint32_t communication::recv_quad()
{
    uint32_t q = 0;

    q += recv_single_byte();
    q += recv_single_byte() << 0x08;
    q += recv_single_byte() << 0x10;
    q += recv_single_byte() << 0x18;

    return q;
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

void communication::send(uint8_t *msg, size_t length)
{
    m_serial.write(msg, length);
}

void communication::serial_printout(uint8_t dataSens1[], uint8_t dataSens2[], uint8_t dataSens3[], uint8_t dataSens4[])
{
  uint16_t datTime = 0;
    for (uint16_t i = 0; i < MAXDATAINPUT; i++) {
      datTime += 20;
      Serial.print(datTime);Serial.print(",");Serial.print((int)dataSens1[i]);Serial.print(",");Serial.print((int)dataSens2[i]);Serial.print(",");Serial.print((int)dataSens3[i]);Serial.print(",");Serial.println((int)dataSens4[i]);
    }
}

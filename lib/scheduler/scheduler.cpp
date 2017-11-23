#include "scheduler.hpp"

scheduler::scheduler(communication& comm, dcmotor& motor, servo& servo, sensor sensors[4])
    : m_comm(comm), m_motor(motor), m_servo(servo)
{
    for (uint8_t i = 0; i < 4; ++i) {
        m_sensors[i] = sensors[4];
    }
}

void scheduler::start_test()
{
    uint8_t *commands = m_comm.receive();
    uint8_t iter = 0;

    while (iter < 16)
    {
        switch (commands[iter])
        {
            case HALT:
                break;
            case NOP:
                iter++;
                break;
            case START:
                iter += 2;
                break;
            case BRAKE:
                iter += 2;
                break;
            case FORWARD:
                iter += 2;
                break;
            case BACKWARD:
                iter += 2;
                break;
            case TURN:
                iter += 2;
                break;
        }
    }
}
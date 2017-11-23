#include "scheduler.hpp"

scheduler::scheduler(communication comm)
    : m_comm(comm)
{
    
}

void scheduler::start(uint8_t commands[16])
{
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
#include "scheduler.hpp"

scheduler::scheduler(communication& comm, dcmotor& motor, servo& servo)
    : m_comm(comm), m_motor(motor), m_servo(servo)
{

}

void scheduler::check_emergency_brake()
{
    if (m_comm.is_halt) {
        m_motor.emBrake();
    }
}
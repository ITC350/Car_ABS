#pragma once

typedef enum opcode_e {
    NOP         = 0x00,
    START       = 0x01,
    ACCELERATE  = 0x02,
    DISABLE_ABS = 0x03,
    PID         = 0x04,
    HALT        = 0xFF
} opcode_t;
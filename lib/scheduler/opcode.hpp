#pragma once

typedef enum opcode_e {
    NOP         = 0x00,
    START       = 0x01,
    BRAKE       = 0x02,
    FORWARD     = 0x03,
    BACKWARD    = 0x04,
    TURN        = 0x05,
    DISABLE_ABS = 0x06,
    HALT        = 0xFF
} opcode_t;
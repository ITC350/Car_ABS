#pragma once

typedef enum opcode_e {
    NOP         = 0x00,
    START       = 0x01,
    SETTINGS    = 0x02,
    DISABLE_ABS = 0x03,
    HALT        = 0x04
} opcode_t;
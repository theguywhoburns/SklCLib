#ifndef _SKLC_LIB_CPU_6502_H_
#define _SKLC_LIB_CPU_6502_H_

#include <sklc_lib/defines.h>

typedef struct _memory_6502 {
    Byte data[0xFFFF];
    void (*reset)(struct _memory_6502 *mem);
} memory_6502;


typedef struct _cpu_6502 {
    memory_6502 *mem;
    
    u8 A;   // Accumulator
    u8 X;   // X register
    u8 Y;   // Y register
    
    union {
        u8 status;
        struct {
            u8 carry            : 1;
            u8 zero             : 1;
            u8 interrupt_disable: 1;
            u8 decimal_mode     : 1;
            u8 break_cmd        : 1;
            u8 unused           : 1;
            u8 overflow         : 1;
            u8 negative         : 1;
        } flags;
    } p;    // Processor status register
    
    u16 pc; // Program counter
    u8 sp;  // Stack pointer
    
    void (*reset)(struct _cpu_6502* cpu);
    b8  (*update)(struct _cpu_6502* cpu);
} cpu_6502;

// WARNING, memory has to be reset manually
// Doesnt need to be shut down
cpu_6502 cpu_6502_init(memory_6502 *mem);


#endif//_SKLC_LIB_CPU_6502_H_
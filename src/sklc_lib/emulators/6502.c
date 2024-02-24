#include <sklc_lib/emulators/6502.h>

void cpu_6502_reset(cpu_6502* cpu) {
    cpu->A = cpu->X = cpu->Y = 0x0000;
    cpu->sp = 0x0100; 
    cpu->pc = 0xFFFC;
    cpu->p.status = 0x0000;
    
}

b8 cpu_6502_update(cpu_6502* cpu) {
    
}

cpu_6502 cpu_6502_init(memory_6502 *mem) {
    cpu_6502 ret = {0};
    ret.mem = mem;
    cpu_6502_reset(&ret);
    ret.reset = cpu_6502_reset;
    ret.update = cpu_6502_update;
    return ret;
}

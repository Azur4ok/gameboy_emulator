#include <stdio.h>
#include "mmu.h"
#include "cpu.h"

int main() {
    
    mmu_init();
    
    cpu_init();
    
    mmu_write(0x0100, 0xAB);
    mmu_write(0x0101, 40);
    
    cpu_step();
    
    u8 value = mmu_read(0x0100);
    
    printf("%s","Game boy Emulator\n");
    
    printf("Read: by 0x0100 adress value is %d\n", value);
    return 0;
}
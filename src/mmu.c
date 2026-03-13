#include <stdio.h>
#include <string.h>
#include "mmu.h"

static u8 memory[0x10000];

void mmu_init() {
    memset(memory, 0, sizeof(memory));
}

u8 mmu_read(u16 address) {
   return memory[address];
}

void mmu_write(u16 address, u8 value) {
    memory[address] = value;
}
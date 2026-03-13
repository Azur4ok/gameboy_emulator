#ifndef MMU_H
#define MMU_H

#include "types.h"

void mmu_init(void);

u8 mmu_read(u16 address);

void mmu_write(u16 address, u8 value);

#endif
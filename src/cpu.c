#include "cpu.h"
#include "mmu.h"
#include <stdio.h>

typedef struct {
  u8 dst;
  u8 src;
} LD_r_register;

static struct CPU cpu;

static u8 *reg_map[8] = {&cpu.B, &cpu.C, &cpu.D, &cpu.E,
                         &cpu.H, &cpu.L, NULL,   &cpu.A};

void cpu_init() { cpu.PC = 0x0100; }

u8 cpu_get_flag(FLAGS flag) {
  u8 res = cpu.F & flag;
  if (res) {
    return 1;
  }
  return 0;
};

void cpu_set_flag(FLAGS flag, u8 value) {
  if (value) {
    cpu.F = cpu.F | flag;
  } else {
    cpu.F = cpu.F & ~flag;
  }
};

static LD_r_register parse_LD_r_opcode(u8 opcode) {
  LD_r_register result;
  result.src = opcode & 0x07;
  result.dst = (opcode >> 3) & 0x07;
  return result;
}

void cpu_step() {
  u8 opcode = mmu_read(cpu.PC);
  ++cpu.PC;
  printf("register %#010x and %d\n", cpu.PC, opcode);

  if (opcode == 0x76) {
    printf("HALT");
  } else if ((opcode & 0xC0) == 0x40) {
    LD_r_register result = parse_LD_r_opcode(opcode);

    if (result.src == 6) {
         u8 HL_opcode = mmu_read(cpu.HL);
         *reg_map[result.dst] = HL_opcode;
    } else if (result.dst == 6) {
        mmu_write(cpu.HL, *reg_map[result.src]);
    }  else {
        *reg_map[result.dst] = *reg_map[result.src];
    }
    printf("LD r, r opcode %d\n", opcode);
  }
};

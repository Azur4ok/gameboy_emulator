#ifndef CPU_H
#define CPU_H

#include "types.h"

typedef enum {
    FLAG_C = 0x10,
    FLAG_H = 0x20,
    FLAG_N = 0x40,
    FLAG_Z = 0x80
} FLAGS;

struct CPU {
  union {
    u16 AF;
    struct {
      u8 F;
      u8 A;
    };
  };
  union {
    u16 BC;
    struct {
      u8 C;
      u8 B;
    };
  };
  union {
    u16 DE;
    struct {
      u8 E;
      u8 D;
    };
  };
  union {
    u16 HL;
    struct {
      u8 L;
      u8 H;
    };
  };
  u16 SP, PC;
  u32 cycles;
  u8 halted;
};

void cpu_init(void);

void cpu_step(void);

u8 cpu_get_flag(FLAGS flag);

void cpu_set_flag(FLAGS flag, u8 value);

#endif

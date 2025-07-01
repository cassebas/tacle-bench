#include "endmark.h"

void __attribute__((aligned(64))) __attribute__((optimize("O0")))  benchmark_endmark( void )
{
  asm volatile ("nop");
}

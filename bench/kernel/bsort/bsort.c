/*

  This program is part of the TACLeBench benchmark suite.
  Version 2.0

  Name: bsort

  Author: unknown

  Function: A program for testing the basic loop constructs,
            integer comparisons, and simple array handling by
            sorting 100 integers

  Source: MRTC
          http://www.mrtc.mdh.se/projects/wcet/wcet_bench/bsort100/bsort100.c

  Original name: bsort100

  Changes: See ChangeLog.txt

  License: May be used, modified, and re-distributed freely.

*/

#include <stdint.h>
#include "kprintf.h"

#ifndef RISCV_CORE_CONFIG
#define RISCV_CORE_CONFIG "rv32_i4k_d4k"
#endif

// The reset control register allows us to signal a CPU reset
#define RESET_CONTROL_ADDR 0x60040000

#define BOOTDEVICE_ADDR    0x60050000  // Addres of the mmio boot device
#define BOOTDEVICE_BOOTNUM 0x00003F00  // Offset to the bootnum parameter

/*
  Forward declaration of functions
*/

void bsort_init( void );
void bsort_main( void );
int bsort_return( void );
int bsort_Initialize( int Array[] );
int bsort_BubbleSort( int Array[] );


/*
  Declaration of global variables
*/

#define bsort_SIZE 10

static int bsort_Array[ bsort_SIZE ];


/*
  Initialization- and return-value-related functions
*/

/* Initializes given array with randomly generated integers. */
int bsort_Initialize( int Array[] )
{
  int Index;

  _Pragma( "loopbound min 100 max 100" )
  for ( Index = 0; Index < bsort_SIZE; Index ++ )
    Array[ Index ] = ( Index + 1 ) * -1;

  return 0;
}


void bsort_init( void )
{
  bsort_Initialize( bsort_Array );
}


int bsort_return( void )
{
  int Sorted = 1;
  int Index;

  _Pragma( "loopbound min 99 max 99" )
  for ( Index = 0; Index < bsort_SIZE - 1; Index ++ )
    Sorted = Sorted && ( bsort_Array[ Index ] < bsort_Array[ Index + 1 ] );

  return 1 - Sorted;
}


/*
  Core benchmark functions
*/

/* Sorts an array of integers of size bsort_SIZE in ascending
   order with bubble sort. */
int bsort_BubbleSort( int Array[] )
{
  int Sorted = 0;
  int Temp, Index, i;

  _Pragma( "loopbound min 99 max 99" )
  for ( i = 0; i < bsort_SIZE - 1; i ++ ) {
    Sorted = 1;
    _Pragma( "loopbound min 3 max 99" )
    for ( Index = 0; Index < bsort_SIZE - 1; Index ++ ) {
      if ( Index > bsort_SIZE - i )
        break;
      if ( Array[ Index ] > Array[Index + 1] ) {
        Temp = Array[ Index ];
        Array[ Index ] = Array[ Index + 1 ];
        Array[ Index + 1 ] = Temp;
        Sorted = 0;
      }
    }

    if ( Sorted )
      break;
  }

  return 0;
}


void _Pragma( "entrypoint" ) bsort_main( void )
{
  bsort_BubbleSort( bsort_Array );
}


/*
  Main function
*/

int main( void )
{
  uintptr_t cycles1, cycles2, cycles3;

  volatile uint32_t *reset_ctrl_reg = (uint32_t *) RESET_CONTROL_ADDR;
  *reset_ctrl_reg = 0;

  // The 'constant' boot_num (changed by the program on each run),
  // tells us how many times we have booted. It is a constant present
  // in the binary boot.elf, but since we have the binary in the block
  // ram, we can alter its contents.
  volatile uint32_t *boot_memory = (uint32_t *) BOOTDEVICE_ADDR;
  volatile uint32_t boot_num = boot_memory[BOOTDEVICE_BOOTNUM];
  // Put the new 'constant' in the block ram where the boot.elf binary resides
  boot_num++;
  boot_memory[BOOTDEVICE_BOOTNUM] = boot_num;

  asm volatile ("csrr %0, mcycle" : "=r" (cycles1));
  bsort_init();
  asm volatile ("csrr %0, mcycle" : "=r" (cycles2));
  bsort_main();
  asm volatile ("csrr %0, mcycle" : "=r" (cycles3));

  kprintf("bootnum=%d ", boot_num);
  kprintf("cycles bsort::bsort_init=%ld ", cycles2 - cycles1);
  kprintf("cycles bsort::bsort_main=%ld\n", cycles3 - cycles2);

  // Set the reset control register to all ones, signalling CPU reset.
  *reset_ctrl_reg = 0xffffffff;

  return bsort_return();
}

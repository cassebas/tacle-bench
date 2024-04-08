/**
 * synthetic_bench.h
 *
 *  Created on: Apr 2, 2024
 *      Author: Caspar Treijtel
 */
#ifndef SYNTHETIC_BENCH_H
#define SYNTHETIC_BENCH_H

#include <stdint.h>

/**
 * We want to use a data structure that consists of more than
 * 512KB (size of L2 cache). The 64 bytes is chosen because we 
 * want to touch as many cache lines as possible, with a jump of
 * 64 bytes each iteration, we try to fill the L2 as soon as possible.
 * This is because the cache (both L1 and L2) have cache line
 * sizes of 64 bytes.
 */

/* Maybe define the size of the array that is used in the
   synthetic benchmarks.
   If already defined in the CFLAGS (-DSYNBENCH_DATASIZE=...) then
   do nothing. */
#ifndef SYNBENCH_DATASIZE
#define SYNBENCH_DATASIZE 131072
#endif
// To make bigstruct 64 bytes, which is equal to the line size of the caches
// id + data == 64 bytes
#define BIGSTRUCT_DATASIZE 63

/**
 * Synthetic benchmark inspired by the paper `Predictable and Efficient Virtual
 * Addressing for Safety-Critical Real-Time Systems', written by Bennet and
 * Audsley (2001).
 */

/**
 * Type bigstruct_t is (with int32_t being 4 bytes) a 256 bytes struct.
 */
typedef struct bigstruct {
	int32_t id;
	int32_t data[BIGSTRUCT_DATASIZE];
} bigstruct_t;


int32_t array_access_linear(volatile bigstruct_t *data);
void array_write_linear(volatile bigstruct_t *data);

#endif /* SYNTHETIC_BENCH_H */

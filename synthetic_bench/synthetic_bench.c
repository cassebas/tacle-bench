/*
 * synthetic_bench.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Caspar Treijtel
*/

#include "synthetic_bench.h"
#include <stdlib.h>

int32_t array_access_linear(volatile bigstruct_t *data)
{
	int32_t sum = 0;
	if (data != NULL) {
        for (int i=0; i<SYNBENCH_DATASIZE; i++) {
            sum += data[i].id;
        }
	}
	return sum;
}

void array_write_linear(volatile bigstruct_t *data)
{
	if (data != NULL) {
        for (int j=0; j<BIGSTRUCT_DATASIZE; j++) {
            for (int i=0; i<SYNBENCH_DATASIZE; i++) {
                data[i].id = j;
                data[i].data[j] = 0xff;
            }
        }
	}
}

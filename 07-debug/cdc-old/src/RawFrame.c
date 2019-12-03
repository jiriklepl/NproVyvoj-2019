/*
 * RawFrame.c
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#include "RawFrame.h"

#include <stdint.h>

void RAWFRAME_copy(RawFrame* dest, int32_t lengths_size, int32_t* lengths_, const char* signs_, float* positions_) {
	int i = 0, pos = 0, pos2 = 0, pos3 = 0, pos4 = 0, j=0;
	for (; i < lengths_size; i++) {
		dest->lengths[pos++] = lengths_[i];
		dest->positions[pos2++] = positions_[3 * i];
		dest->positions[pos2++] = positions_[3 * i + 1];
		dest->positions[pos2++] = positions_[3 * i + 2];
		for (j = 0; j < lengths_[i]; j++)
			dest->callsigns[pos3++] = signs_[pos4 + j];
		pos4 += lengths_[i];
	}
	dest->planeCnt = lengths_size;
}


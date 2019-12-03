/*
 * RawFrame.h
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#ifndef RAWFRAME_H_
#define RAWFRAME_H_

struct RawFrameType ;

#define RAWFRAME_MAX_PLANES 1000
#define RAWFRAME_MAX_SIGNS 10 * RAWFRAME_MAX_PLANES

typedef struct RawFrameType
{
    int lengths[RAWFRAME_MAX_PLANES];
    char callsigns[RAWFRAME_MAX_SIGNS];
    float positions[3 * RAWFRAME_MAX_PLANES];
    int planeCnt;
} RawFrame ;

void RAWFRAME_copy(RawFrame * dest, int lengths_size, int * lengths_, const char * signs_, float * positions_);

#endif /* RAWFRAME_H_ */

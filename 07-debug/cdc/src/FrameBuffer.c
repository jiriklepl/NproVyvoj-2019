/*
 * FrameBuffer.c
 *
 *  Created on: Jul 25, 2009
 *      Author: ghaitho
 */

#include "RawFrame.h"
#include "FrameBuffer.h"
#include "Constants.h"
#include "helper.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

RawFrame * RawFrames;

int FRAMEBUFFER_frameno = 0, FRAMEBUFFER_droppedFrames=0;

void FRAMEBUFFER_init() {
	RawFrames = (RawFrame *) malloc (sizeof (RawFrame)*BUFFER_FRAMES);
}

void FRAMEBUFFER_putFrameInternal(int32_t length, float * positions_, int32_t * lengths_, char * callsigns_) {
	if ( (FRAMEBUFFER_last + 1) % BUFFER_FRAMES == FRAMEBUFFER_first) {
		FRAMEBUFFER_droppedFrames ++;
		return;
	}
	RAWFRAME_copy(&RawFrames[FRAMEBUFFER_last], length, lengths_, callsigns_, positions_);
	FRAMEBUFFER_last = (FRAMEBUFFER_last + 1) % BUFFER_FRAMES;
}


void FRAMEBUFFER_putFrame(int32_t length, float* positions_, int32_t * lengths_, char * callsigns_) {

	if (SYNCHRONOUS_DETECTOR || DUMP_SENT_FRAMES) {
		printFrame(FRAMEBUFFER_frameno,"S-FRAME", length, positions_, lengths_, callsigns_);
		FRAMEBUFFER_frameno++;
	}
	FRAMEBUFFER_putFrameInternal(length, positions_, lengths_, callsigns_);
}


RawFrame * FRAMEBUFFER_getFrame() {
	if (FRAMEBUFFER_last == FRAMEBUFFER_first) {
		return 0;
	} else {
		int f = FRAMEBUFFER_first;
		FRAMEBUFFER_first = (FRAMEBUFFER_first + 1) % BUFFER_FRAMES;
		return &RawFrames[f];   // NOTE: if the simulator could run between this and the previous line,
							// it could corrupt the present frame
	}
}

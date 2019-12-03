/*
 * FrameBuffer.h
 *
 *  Created on: Jul 25, 2009
 *      Author: ghaitho
 */

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include "RawFrame.h"

int FRAMEBUFFER_first, FRAMEBUFFER_last;
void FRAMEBUFFER_init();
void FRAMEBUFFER_putFrameInternal(int length, float* positions_, int* lengths_, char* callsigns_);
void FRAMEBUFFER_putFrame(int length, float* positions_, int* lengths_, char* callsigns_);
RawFrame * FRAMEBUFFER_getFrame();

extern RawFrame * RawFrames;

#endif /* FRAMEBUFFER_H_ */

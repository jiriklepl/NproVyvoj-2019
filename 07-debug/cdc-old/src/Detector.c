/*
 * Detector.c
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#include "Detector.h"
#include "TransientDetector.h"
#include "FrameBuffer.h"

#include <stdio.h>

int stop = 0;

void DETECTOR_init() {
	TRANSIENTDETECTOR_init();
}

void DETECTOR_run() {
	RawFrame * frm = FRAMEBUFFER_getFrame();
	while (frm!=0) {
		TRANSIENTDETECTOR_setFrame(frm);
		TRANSIENTDETECTOR_run();
		frm = FRAMEBUFFER_getFrame();
	}
}

void DETECTOR_finish() {

	printf("Detector is finished, processed all frames.");

}

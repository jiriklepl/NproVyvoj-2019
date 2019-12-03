/*
 * ImmortalEntry.c
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#include "ImmortalEntry.h"
#include "Detector.h"
#include "Constants.h"
#include <stdio.h>

void IMMORTALENTRY_run() {
// FIXME: Do not print values of parameters that are unused
//	printf("Detector: detector priority is %d\n",DETECTOR_PRIORITY);
//	printf("Detector: detector period is %ld\n",DETECTOR_PERIOD);
	DETECTOR_init();
}


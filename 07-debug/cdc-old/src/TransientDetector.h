/*
 * TransientDetector.h
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#ifndef TRANSIENTDETECTOR_H_
#define TRANSIENTDETECTOR_H_

#include "RawFrame.h"
#include "Motion.h"
#include "CallSign.h"
#include "Reducer.h"
#include "Aircraft.h"
#include "Vector3d.h"

// ArrayList implementation for collisions
struct collision_list {
	Aircraft * one;
	Aircraft * two;
	Vector3d * location;
   struct collision_list * next;
};

typedef struct collision_list collisions;

void TRANSIENTDETECTOR_init();
void TRANSIENTDETECTOR_run();
int TRANSIENTDETECTOR_lookForCollisions(Motion *,list_motions * l, collisions * c);
list_motions * TRANSIENTDETECTOR_reduceCollisionSet(Motion *,list_motions * l);
void TRANSIENTDETECTOR_dumpFrame( char * );
void TRANSIENTDETECTOR_setFrame(RawFrame *);
Motion * TRANSIENTDETECTOR_createMotions();
CallSign * TRANSIENTDETECTOR_getCallSign(CallSign *, char * cs);
int TRANSIENTDETECTOR_determineCollisions(motions * mm, collisions * c);

#endif /* TRANSIENTDETECTOR_H_ */

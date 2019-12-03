/*
 * Motion.h
 *
 *  Created on: Jul 29, 2009
 *      Author: ghaitho
 */

#ifndef MOTION_H_
#define MOTION_H_

#include "Aircraft.h"
#include "Vector3d.h"

struct MotionType ;

typedef struct MotionType
{
	Aircraft * aircraft;
	Vector3d * pos_one;
	Vector3d * pos_two;
} Motion ;

Motion * MOTION_init1(Motion * mt, Aircraft * ac, Vector3d * v1, Vector3d * v2);
Motion * MOTION_init2(Motion * mt, Aircraft * ac, Vector3d * v);
char * MOTION_toString(Motion * mt);
int MOTION_findIntersection(Motion * one, Motion * two, Vector3d * v );

#endif /* MOTION_H_ */

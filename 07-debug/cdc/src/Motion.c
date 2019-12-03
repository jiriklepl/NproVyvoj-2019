/*
 * Motion.c
 *
 *  Created on: Jul 29, 2009
 *      Author: ghaitho
 */

#include "Motion.h"
#include "Constants.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Motion * MOTION_init1(Motion * mt, Aircraft * ac, Vector3d * v1, Vector3d * v2) {
	mt->aircraft = ac;
	mt->pos_one = v1;
	mt->pos_two = v2;
	return mt;
}

Motion * MOTION_init2(Motion * mt, Aircraft * ac, Vector3d * v) {
	mt->aircraft = ac;
	mt->pos_one = v;
	mt->pos_two = v;
	return mt;
}

int MOTION_findIntersection(Motion * one, Motion * two, Vector3d * v ) {
	Vector3d * i1, *i2, *f1, *f2;
	i1 = one->pos_one;
	f1 = one->pos_two;
	i2 = two->pos_one;
	f2 = two->pos_two;
	float r = PROXIMITY_RADIUS;
	float vx1 = f1->x - i1->x;
	float vx2 = f2->x - i2->x;
	float vy1 = f1->y - i1->y;
	float vy2 = f2->y - i2->y;
	float vz1 = f1->z - i1->z;
	float vz2 = f2->z - i2->z;

	// this test is not geometrical 3-d intersection test, it takes the fact that the aircraft move
	// into account ; so it is more like a 4d test
	// (it assumes that both of the aircraft have a constant speed over the tested interval)

	// we thus have two points, each of them moving on its line segment at constant speed ; we are looking
	// for times when the distance between these two points is smaller than r

	// V1 is vector of aircraft 1
	// V2 is vector of aircraft 2

	// if a = 0 iff the planes are moving in parallel and have the same speed (can be zero - they may not be moving at all)

	// a = (V2 - V1)^T * (V2 - V1) = < (V2 - V1), (V2 - V1) > = sqrt( || V2 - V1 || )
	float a = (vx2 - vx1) * (vx2 - vx1) + (vy2 - vy1) * (vy2 - vy1) + (vz2 - vz1) * (vz2 - vz1);

	if (a != 0.0f) {

		// we are first looking for instances of time when the planes are exactly r from each other
		// at least one plane is moving ; if the planes are moving in parallel, they do not have constant speed

		// if the planes are moving in parallel, then
		//   if the faster starts behind the slower, we can have 2, 1, or 0 solutions
		//   if the faster plane starts in front of the slower, we can have 0 or 1 solutions

		// if the planes are not moving in parallel, then


		// point P1 = I1 + vV1
		// point P2 = I2 + vV2
		//   - looking for v, such that dist(P1,P2) = || P1 - P2 || = r

		// it follows that || P1 - P2 || = sqrt( < P1-P2, P1-P2 > )
		//   0 = -r^2 + < P1 - P2, P1 - P2 >
		//  from properties of dot product
		//   0 = -r^2 + <I1-I2,I1-I2> + v * 2<I1-I2, V1-V2> + v^2 *<V1-V2,V1-V2>
		//   so we calculate a, b, c - and solve the quadratic equation
		//   0 = c + bv + av^2

		// b = 2 * <I1-I2, V1-V2>
		float b = 2.0f * (i2->x * vx2 - i2->x * vx1 - i1->x * vx2 + i1->x * vx1 +
						  i2->y * vy2 - i2->y * vy1 - i1->y * vy2 + i1->y * vy1 +
						  i2->z * vz2 - i2->z * vz1 - i1->z * vz2 + i1->z * vz1);

		// c = -r^2 + (I2 - I1)^T * (I2 - I1)
		float c = -r * r + (i2->x - i1->x) * (i2->x - i1->x) + (i2->y - i1->y) * (i2->y - i1->y) + (i2->z - i1->z)
			* (i2->z - i1->z);

		float discr = b * b - 4.0f * a * c;
		if (discr < 0.0f) return 0;

		// the left side
		float v1 = (-b - (float) sqrt(discr)) / (2.0f * a);
		// the right side
		float v2 = (-b + (float) sqrt(discr)) / (2.0f * a);

		// FIXME: v1 <= v2 always holds, correct ?
		//  .. because v1 > v2 only if a < 0, which would mean <V1-V2,V1-V2> < 0, which is impossible

		if (v1 <= v2 && (v1 <= 1.0f && 1.0f <= v2 || v1 <= 0.0f && 0.0f <= v2 || 0.0f <= v1 && v2 <= 1.0f)) {
			// new: calculate the location of the collision; if it is
			// outside of the bounds of the Simulation, don't do anything!
			float x1col = i1->x + vx1 * (v1 + v2) / 2.0f;
			float y1col = i1->y + vy1 * (v1 + v2) / 2.0f;
			float z1col = i1->z + vz1 * (v1 + v2) / 2.0f;
			if (z1col > MIN_Z && z1col <= MAX_Z && x1col >= MIN_X
					&& x1col <= MAX_X && y1col >= MIN_Y && y1col <= MAX_Y) {

				VECTOR3D_init2(v,x1col,y1col,z1col);return 1;
			}
		}
	} else {

		// the planes have the same speeds and are moving in parallel (or they are not moving at all)
		// they  thus have the same distance all the time ; we calculate it from the initial point

		// dist = || i2 - i1 || = sqrt(  ( i2 - i1 )^T * ( i2 - i1 ) )

		float dist = (i2->x - i1->x) * (i2->x - i1->x) + (i2->y - i1->y) * (i2->y - i1->y) + (i2->z - i1->z) * (i2->z - i1->z);
		dist = (float) sqrt(dist);

		// System.out.println("i1 = "+i1+", i2 = "+i2+", dist = "+dist);
		if (dist <= r) {
			VECTOR3D_init2(v,one->pos_one->x,one->pos_one->y,one->pos_one->z);return 1;
		}
	}
	return 0;
}


char * MOTION_toString(Motion * mt) {
	char buf[30],buf2[30];
	char * acStr = AIRCRAFT_toString(mt->aircraft);
	char * pos1Str = VECTOR3D_toString(buf,mt->pos_one);
	char * pos2Str = VECTOR3D_toString(buf2,mt->pos_two);
	char * ret = (char *) malloc(strlen(acStr)+strlen(pos1Str)+strlen(pos2Str)+21); // !!! sync 21 with the string below
	sprintf(ret,"MOTION of %s from %s to %s",acStr,pos1Str,pos2Str);
	return ret;
}

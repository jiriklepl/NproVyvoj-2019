/*
 * Vector3d.c
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#include "Vector3d.h"
#include <stdio.h>
#include "helper.h"

void VECTOR3D_init(Vector3d * v) {
	v->x = 0.0f;
	v->y = 0.0f;
	v->z = 0.0f;
}

void VECTOR3D_init2(Vector3d * v,float i, float j, float k) {
	v->x = i;
	v->y = j;
	v->z = k;
}

void VECTOR3D_set(Vector3d * v,float i, float j, float k) {
	v->x = i;
	v->y = j;
	v->z = k;
}


int VECTOR3D_hashCode(Vector3d * v) {
	return (int) ((v->x + v->y + v->z) * v->y + (v->x - v->y + v->z) * v->x - (v->x - v->y - v->z) * v->z);
}


char * VECTOR3D_toString(char * buf, Vector3d * v) {
	char b1[30],b2[10],b3[10];
	sprintf(buf,"(%s, %s, %s)",fixnum(b1,v->x),fixnum(b2,v->y),fixnum(b3,v->z));
	return buf;
}

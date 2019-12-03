/*
 * StateTable.c
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */


#include "Vector3d.h"
#include "StateTable.h"
#include "HashMap.h"

#include <stdlib.h>
#include <stdio.h>

Vector3d * allocatedVectors;
int usedVectors;
map_t motionVectors;

/** Mapping Aircraft -> Vector3d. */

void STATETABLE_init() {
	int i=0;
	allocatedVectors = (Vector3d *) malloc (sizeof (Vector3d)*MAX_AIRPLANES);
	for(;i<MAX_AIRPLANES;i++){
		VECTOR3D_init(&allocatedVectors[i]);
	}
	usedVectors = 0;
	motionVectors = hashmap_new();
}

void STATETABLE_put(CallSign * callsign, float x, float y, float z) {
	//Vector3d * v = (Vector3d *) malloc(sizeof(Vec));
	int i=-1;
	if (hashmap_get(motionVectors, CALLSIGN_HashCode(callsign), (any_t *)&i)!=MAP_OK) {
	    allocatedVectors[usedVectors].x=x;
	    allocatedVectors[usedVectors].y=y;
	    allocatedVectors[usedVectors].z=z;
	    if(hashmap_put(motionVectors, CALLSIGN_HashCode(callsign), (any_t) usedVectors) != MAP_OK) {
	    	exit(0);
	    }
	    usedVectors++;
    } else {
	    allocatedVectors[i].x=x;
	    allocatedVectors[i].y=y;
	    allocatedVectors[i].z=z;
    }
}

int STATETABLE_get(CallSign * callsign, Vector3d * v) {
	int i=-1;
	int j = hashmap_get(motionVectors, CALLSIGN_HashCode(callsign), (any_t *)&i);
	if (j==MAP_OK)VECTOR3D_set(v,allocatedVectors[i].x,allocatedVectors[i].y,allocatedVectors[i].z);
	return j;
}


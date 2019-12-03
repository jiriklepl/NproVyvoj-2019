/*
 * VoxelMap.c
 *
 *  Created on: Aug 4, 2009
 *      Author: ghaitho
 */

#include "VoxelMap.h"
#include "HashMap.h"
#include "Vector2d.h"
#include "Motion.h"

#include <stdlib.h>

// FIXME: remove unused comments

Motion *** allocatedMotions;
int usedMotions;
int *usedMotionsInList;
map_t voxel_map;

void VOXELMAP_init() {
	int i=0,j=0;

	allocatedMotions = (Motion ***) malloc (MAX_LIST*sizeof (Motion**));
	for (i=0;i<MAX_LIST;i++)
		allocatedMotions[i] = (Motion **) malloc(MAX_ITEMS_PER_LIST*sizeof(Motion *));
//	for(;i<MAX_LIST;i++){
//		for(j=0;j<MAX_ITEMS_PER_LIST;j++)
//			allocatedMotions[i][j]=0;
//	}

	usedMotions = 0;
	// allocate an array of MAX_ITEMS_PER_LIST integers
	usedMotionsInList = (int *) malloc(MAX_ITEMS_PER_LIST * sizeof(int));
	// initialize all the allocated integers to zero
	for (j=0;j<MAX_ITEMS_PER_LIST;j++)usedMotionsInList[j]=0;
	voxel_map = hashmap_new();
}

void VOXELMAP_reset() {
	int j=0;
//	for(;i<MAX_LIST;i++){
//		for(j=0;j<MAX_ITEMS_PER_LIST;j++)
//			allocatedMotions[i][j]=0;
//	}
	usedMotions = 0;
	for (j=0;j<MAX_ITEMS_PER_LIST;j++)usedMotionsInList[j]=0;
	hashmap_free(voxel_map);
	voxel_map = hashmap_new();
}

void VOXELMAP_put(Vector2d * v, Motion * m) {
	//Vector3d * v = (Vector3d *) malloc(sizeof(Vec));
	int i=-1;
	if (hashmap_get(voxel_map, VECTOR2D_hashCode(v), (any_t *)&i)!=MAP_OK) {
		allocatedMotions[usedMotions][usedMotionsInList[usedMotions]]=m;
	    if(hashmap_put(voxel_map, VECTOR2D_hashCode(v), (any_t) usedMotions) != MAP_OK) {
	    	exit(0);
	    }
	    usedMotionsInList[usedMotions]++;
	    usedMotions++;
    } else {
    	allocatedMotions[i][usedMotionsInList[i]]=m;
    	usedMotionsInList[i]++;
    }
}

int VOXELMAP_getMotionCount(Vector2d * v) {
	int i=-1;
	int j = hashmap_get(voxel_map,VECTOR2D_hashCode(v), (any_t *)&i);
	if (j==MAP_OK)return usedMotionsInList[i];
	else return 0;
}

int VOXELMAP_get(Vector2d * v, int location, Motion ** m) {
	int i=-1;
	int j = hashmap_get(voxel_map,VECTOR2D_hashCode(v), &i);
	if (j==MAP_OK)*m=allocatedMotions[i][location];
	return j;
}

int VOXELMAP_getMotionListsCount() {
	return usedMotions;
}

int VOXELMAP_getMotionCountUsingLocation(int loc) {
	return usedMotionsInList[loc];
}

void VOXELMAP_getUsingLocation(int loc, int location, Motion ** m) {
	*m=allocatedMotions[loc][location];
}

int iterresult;
int itercnt;
int iterval;
int currentmotions;

int iter(any_t l, any_t  m) {
	if (usedMotionsInList[(int)m]==currentmotions) {
		itercnt++;
		if (itercnt==iterval) {
			iterresult=(int)m;
			return -1;
		}
	}
	return MAP_OK;
}

void VOXELMAP_initIter() {
	iterval = 1;
	currentmotions=1;
}

int VOXELMAP_iterNext() {
	if (iterval==hashmap_length(voxel_map)+1) return -1;
	itercnt=0;
	iterresult = -1;
	currentmotions=0;
	while (iterresult == -1) {
		hashmap_iterate(voxel_map, (PFany)&iter, (any_t) "");
		if(iterresult == -1){currentmotions++;}
		else {iterval++;}
	}
	itercnt=0;
	//printf("%d %d %d\n",iterresult,usedMotionsInList[iterresult],iterval);
	return iterresult;
}

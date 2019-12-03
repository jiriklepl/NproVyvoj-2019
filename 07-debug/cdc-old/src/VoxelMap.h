/*
 * VoxelMap.h
 *
 *  Created on: Aug 4, 2009
 *      Author: ghaitho
 */

#ifndef VOXELMAP_H_
#define VOXELMAP_H_

#include "Motion.h"
#include "Vector2d.h"

#define MAX_LIST 100
#define MAX_ITEMS_PER_LIST 100

void VOXELMAP_init();
void VOXELMAP_reset();
void VOXELMAP_put(Vector2d * v, Motion * m);
int VOXELMAP_getMotionCount(Vector2d * v);
int VOXELMAP_get(Vector2d * v, int location, Motion ** m);
int VOXELMAP_getMotionListsCount();
int VOXELMAP_getMotionCountUsingLocation(int loc);
void VOXELMAP_getUsingLocation(int loc, int location, Motion ** m);
void VOXELMAP_initIter();
int VOXELMAP_iterNext();

#endif /* VOXELMAP_H_ */

/*
 * Reducer.h
 *
 *  Created on: Jul 28, 2009
 *      Author: ghaitho
 */

#ifndef REDUCER_H_
#define REDUCER_H_

#include "Motion.h"
#include "HashMap.h"
#include "Vector2d.h"
#include "Vector3d.h"

// ArrayList implementation for motions
struct motion_list {
   Motion * val;
   struct motion_list * next;
};

typedef struct motion_list motions;

// ArrayList implementation for list of motions
struct motions_list {
	motions * val;
   struct motions_list * next;
};

typedef struct motions_list list_motions;

void REDUCER_init(float);
void REDUCER_voxelHash(Vector3d * position, Vector2d * voxel);
int REDUCER_isInVoxel(Vector2d * voxel, Motion * motion);
void REDUCER_putIntoMap(Vector2d * voxel, Motion * motion);
void REDUCER_dfsVoxelHashRecurse(Motion * motion, Vector2d * next_voxel, map_t graph_colors);
void REDUCER_performVoxelHashing(Motion * motion, map_t graph_colors);
#endif /* REDUCER_H_ */

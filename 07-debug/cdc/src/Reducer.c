/*
 * Reducer.c
 *
 *  Created on: Jul 28, 2009
 *      Author: ghaitho
 */

#include "Reducer.h"
#include "Motion.h"
#include "HashMap.h"
#include "Vector2d.h"
#include "Constants.h"
#include "VectorMath.h"

#include <stdlib.h>
#include <stdio.h>

float voxel_size;
static Vector2d horiz;
static Vector2d vert;
Vector2d * horizontal;
Vector2d * vertical;

void REDUCER_init(float v) {
	voxel_size = v;
	horizontal = &horiz;
	vertical = &vert;
	VECTOR2D_initParam(horizontal,voxel_size, 0.0f);
	VECTOR2D_initParam(vertical,0.0f, voxel_size);
}

/** Creates a Vector2d that represents a voxel. */
void REDUCER_voxelHash(Vector3d * position, Vector2d * voxel) {
	int x_div = (int) (position->x / voxel_size);
	voxel->x = voxel_size * (x_div);
	if (position->x < 0.0f) voxel->x -= voxel_size;

	int y_div = (int) (position->y / voxel_size);
	voxel->y = voxel_size * (y_div);
	if (position->y < 0.0f) voxel->y -= voxel_size;
}

/**
 * Given a voxel and a Motion, determines if they overlap.
 */
int REDUCER_isInVoxel(Vector2d * voxel, Motion * motion) {
	if (voxel->x > MAX_X || voxel->x + voxel_size < MIN_X || voxel->y > MAX_Y
			|| voxel->y + voxel_size < MIN_Y) return 0;

	// this code detects intersection between a line segment and a square
	// (geometric intersection, it ignores the time and speeds of aircraft)
	//
	// the intuition is that we transform the coordinates such that the line segment
	// ends up being a line from (0,0) to (1,1) ; in this transformed system, the coordinates of
	// the square (becomes rectangle) are (low_x,low_y,high_x,high_y) ; in this transformed system,
	// it is possible to detect the intersection without further arithmetics (just need comparisons)
	//
	// this algorithm is probably of general use ; I have seen too many online posts advising
	// more complex solution to the problem that involved calculating intersections between rectangle
	// sides and the segment/line

	Vector3d * init = motion->pos_one;
	Vector3d * fin = motion->pos_two;

	float v_s = voxel_size;
	float r = PROXIMITY_RADIUS / 2.0f;

	float v_x = voxel->x;
	float x0 = init->x;
	float xv = fin->x - init->x;

	float v_y = voxel->y;
	float y0 = init->y;
	float yv = fin->y - init->y;

	float low_x, high_x;
	low_x = (v_x - r - x0) / xv;
	high_x = (v_x + v_s + r - x0) / xv;

	if (xv < 0.0f) {
		float tmp = low_x;
		low_x = high_x;
		high_x = tmp;
	}

	float low_y, high_y;
	low_y = (v_y - r - y0) / yv;
	high_y = (v_y + v_s + r - y0) / yv;

	if (yv < 0.0f) {
		float tmp = low_y;
		low_y = high_y;
		high_y = tmp;
	}
	// ugliest expression ever.
	int result = (
		(
		(xv == 0.0 && v_x <= x0 + r && x0 - r <= v_x + v_s) /* no motion in x */ ||
			((low_x <= 1.0f && 1.0f <= high_x) || (low_x <= 0.0f && 0.0f <= high_x) || (0.0f <= low_x && high_x <= 1.0f))
		)
		&&
		(
		(yv == 0.0 && v_y <= y0 + r && y0 - r <= v_y + v_s) /* no motion in y */ ||
			((low_y <= 1.0f && 1.0f <= high_y) || (low_y <= 0.0f && 0.0f <= high_y) || (0.0f <= low_y && high_y <= 1.0f))
		)
		&&
		(xv == 0.0f || yv == 0.0f || /* no motion in x or y or both */
				(low_y <= high_x && high_x <= high_y) || (low_y <= low_x && low_x <= high_y) || (low_x <= low_y && high_y <= high_x))
	);
	return result;
}

int printcontents(any_t * l, any_t * m) {
	printf("%u\n",m);
	return MAP_OK;
}

int collisioncounter = 0;

void REDUCER_dfsVoxelHashRecurse(Motion * motion, Vector2d * next_voxel, map_t graph_colors) {
	Vector2d *tmp;
	tmp = (Vector2d *) malloc(sizeof(Vector2d));
	Vector2d *tmp2;

	if (REDUCER_isInVoxel(next_voxel, motion) &&
			(hashmap_get(graph_colors, VECTOR2D_hashCode(next_voxel), NULL)!=MAP_OK)) {
		tmp2 = (Vector2d *) malloc(sizeof(Vector2d));
		VECTOR2D_init(tmp2,next_voxel);
		hashmap_put(graph_colors,VECTOR2D_hashCode(tmp2),(any_t)0);

		VOXELMAP_put(next_voxel, motion);

		// left boundary
		VERCORMATH2D_subtract(next_voxel, horizontal, tmp);
		REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

		// right boundary
		VERCORMATH2D_add(next_voxel, horizontal, tmp);
		REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

		// upper boundary
		VERCORMATH2D_add(next_voxel, vertical, tmp);
		REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

		// lower boundary
		VERCORMATH2D_subtract(next_voxel, vertical, tmp);
		REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

		// upper-left
		VERCORMATH2D_subtract(next_voxel, horizontal, tmp);
		VERCORMATH2D_add(tmp, vertical, tmp);
		REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

		// upper-right
		VERCORMATH2D_add(next_voxel, horizontal, tmp);
		VERCORMATH2D_add(tmp, vertical, tmp);
		REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

		// lower-left
		VERCORMATH2D_subtract(next_voxel, horizontal, tmp);
		VERCORMATH2D_subtract(tmp, vertical, tmp);
		REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

		// lower-right
		VERCORMATH2D_add(next_voxel, horizontal, tmp);
		VERCORMATH2D_subtract(tmp, vertical, tmp);
		REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

		free(tmp2);
	}

	free(tmp);
}

void REDUCER_performVoxelHashing(Motion * motion, map_t graph_colors) {
	hashmap_clear(graph_colors);
	graph_colors = hashmap_new();
	Vector2d *voxel ;
	voxel = (Vector2d*)malloc(sizeof(Vector2d));
	VECTOR2D_initParam(voxel,0.0,0.0);
	REDUCER_voxelHash(motion->pos_one, voxel);
	REDUCER_dfsVoxelHashRecurse(motion, voxel, graph_colors);
	free(voxel);
	hashmap_free(graph_colors);
}

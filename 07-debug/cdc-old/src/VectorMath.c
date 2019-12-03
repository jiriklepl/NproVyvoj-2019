/*
 * VectorMath.c
 *
 *  Created on: Jul 31, 2009
 *      Author: ghaitho
 */

#include "VectorMath.h"

/**
 * The <code>add</code> method takes two vectors and adds them, placing the result in a third
 * vector.
 * @param a the value of the first vector
 * @param b the value of the second vector
 * @param dest the destination Vector2d to store the result
 */
void VERCORMATH2D_add(Vector2d * a, Vector2d * b, Vector2d * dest) {
	dest->x = a->x + b->x;
	dest->y = a->y + b->y;
}

/**
 * The <code>subtract</code> method takes two vectors and subtracts them, placing the result
 * in a third vector.
 * @param a the value of the first vector
 * @param b the value of the second vector
 * @param dest the destination Vector2d to store the result
 */
void VERCORMATH2D_subtract(Vector2d * a, Vector2d * b, Vector2d * dest) {
	dest->x = a->x - b->x;
	dest->y = a->y - b->y;
}



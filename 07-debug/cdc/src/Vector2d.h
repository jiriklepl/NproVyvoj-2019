/*
 * Vector2d.h
 *
 *  Created on: Jul 28, 2009
 *      Author: ghaitho
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

struct Vector2dType ;

typedef struct Vector2dType
{
	float x;
	float y;
} Vector2d ;

void VECTOR2D_init(Vector2d * dest,Vector2d * src);
void VECTOR2D_initParam(Vector2d * dest,float x, float y);
int VECTOR2D_hashCode(Vector2d * v);
char * VECTOR2D_toString(char * buf, Vector2d * v);

#endif /* VECTOR2D_H_ */

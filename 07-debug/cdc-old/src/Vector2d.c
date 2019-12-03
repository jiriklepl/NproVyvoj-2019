/*
 * Vector2d.c
 *
 *  Created on: Jul 28, 2009
 *      Author: ghaitho
 */

#include "Vector2d.h"
#include "helper.h"

#include <stdio.h>
#include <stdlib.h>

void VECTOR2D_init(Vector2d * dest,Vector2d * src) {
	dest->x = src->x;
	dest->y = src->y;
}

void VECTOR2D_initParam(Vector2d * dest,float x, float y) {
	dest->x = x;
	dest->y = y;
}

int VECTOR2D_hashCode(Vector2d * v) {
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;
   char * str = (char *)v;
   int len = sizeof(Vector2d);

   for(i = 0; i < len; str++, i++)
   {
	  hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
							   (~((hash << 11) + (*str) ^ (hash >> 5)));
   }

   return hash;
}

char * VECTOR2D_toString(char * buf, Vector2d * v) {
	char b1[30],b2[10];
	sprintf(buf,"(%s, %s)",fixnum(b1,v->x),fixnum(b2,v->y));
	return buf;
}

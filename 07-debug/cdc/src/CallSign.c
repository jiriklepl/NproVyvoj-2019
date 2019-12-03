/*
 * CallSign.c
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#include "CallSign.h"

#include <stdlib.h>


int CALLSIGN_HashCode(CallSign * cs)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;
   char * str = cs->val;
   int len = cs->length;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + (*str) ^ (hash >> 5)));
   }

   return hash;
}

/** Performs a comparison between this object and another. */
int CALLSIGN_equals(CallSign * c1,CallSign * c2) {

	int i=0;
	
	if (c1 == c2) return 1;
	if (c1->length != c2->length) return 0;
	for (; i < c2->length; i++)
		if (c1->val[i] != c2->val[i]) return 0;
	return 1;
}

/** Performs comparison with ordering taken into account. */
int CALLSIGN_compareTo(CallSign *c1,CallSign *c2){
	int i=0;
	if (c2->length < c1->length) return -1;
	if (c2->length > c1->length) return +1;
	for (; i < c2->length; i++)
		if (c2->val[i] < c1->val[i]) return -1;
		else if (c2->val[i] > c1->val[i]) return +1;
	return 0;
}


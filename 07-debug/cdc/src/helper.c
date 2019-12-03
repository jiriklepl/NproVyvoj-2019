/*
 * helper.c
 *
 *  Created on: Jul 27, 2009
 *      Author: ghaitho
 */

#include "helper.h"

#include <stdint.h>
#include <stdio.h>

char * fixnum (char * dest, float f) {
	int ind = 0;
	sprintf(dest,"%f",f);
	// find the decimal point
	while(dest[ind]!='.')ind++;
	if (dest[ind+1]=='0' && dest[ind+2]=='0')dest[ind+2]=0;
	else if (dest[ind+2]=='0')dest[ind+2]=0;
	else dest[ind+3]=0;
	return dest;
}

void printFrame(int frameno,char * prefix, int32_t length, float* positions_, int32_t * lengths_, char * callsigns_) {
	int offset = 0;
	int i=0;
	char b1[10],b2[10],b3[10];
	for (;i<length;i++) {

		int cslen = lengths_[i];
		printf("%s %d ",prefix,frameno);
		int j = 0;
		while (j<cslen) {
			printf("%c",callsigns_[offset+j]);
			j++;
		}
		printf(" %s %s %s \n",fixnum(b1,positions_[3*i]),fixnum(b2,positions_[3*i+1]),fixnum(b3,positions_[3*i+2]));

		offset += cslen;
	}

}

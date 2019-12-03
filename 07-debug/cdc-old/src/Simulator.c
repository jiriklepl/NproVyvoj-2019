/*
 * Simulator.c
 *
 *  Created on: Jul 25, 2009
 *      Author: ghaitho
 */

#include "Simulator.h"
#include "Detector.h"
#include "Constants.h"
#include "FrameBuffer.h"
#include "config.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef CDC_LITTLE_ENDIAN
#define fread_bigendiandata freadswap
#else
#define fread_bigendiandata freadnoswap
#endif

void freadnoswap(void* ptr, int size, int cnt, FILE* f) {
	if (fread(ptr,size,cnt,f) != cnt) {
		fprintf(stderr,"Error reading input file at %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}
}

void freadswap(void* ptr, int size, int cnt, FILE* f) {

	int i=0,j=0;
	char * p = malloc(size*cnt);

	if (!p) {
		fprintf(stderr,"Out of memory in malloc at %s:%d.\n", __FILE__, __LINE__);
		exit(1);
	}

	if (fread(p,size,cnt,f) != cnt) {
		fprintf(stderr,"Error reading input file at %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}
	char * q = p;

	for(i=0; i<cnt; i++) {
		for(j=0; j<size; j++) {
			*(char *)(ptr+i*size+j) = *(char *)(q+(i*size+size-j-1));
		}
	}
	free(p);
	free(q);
}

void generate(char * args[]) {
	
	FILE *fp;
	int32_t nframes, nplanes, callsigns_length;
	int frameCounter, i, j;
	float *positions_temp;
	int32_t* lengths_temp;
	char* callsigns_temp;

	/* open the file */
	fp = fopen(args[1], "r");
	if (!fp) {
		printf("Cannot open file with frames binary dump.\n");
		exit(1);
	}

	fread_bigendiandata(&nframes, 4, 1, fp);

	if (nframes > MAX_FRAMES) {
		printf("Not enough frames in binary dump.");
		exit(1);
	}

	frameCounter == 0;

	FRAMEBUFFER_init();

	while (++frameCounter < nframes+1) {
	
		fread_bigendiandata(&nplanes,4,1,fp);

		positions_temp = (float *)malloc(3*sizeof(float)*nplanes);
		for(i=0; i<nplanes; i++) {
			fread_bigendiandata(&positions_temp[3*i],4,3,fp);
		}

		lengths_temp = (int32_t *)malloc(sizeof(int32_t)*nplanes);
		for(i=0; i<nplanes; i++) {
			fread_bigendiandata(&lengths_temp[i],4,1,fp);
		}

		fread_bigendiandata(&callsigns_length,4,1,fp);
		callsigns_temp = (char *)malloc(sizeof(char)*callsigns_length);
		for (j=0; j<callsigns_length; j++)
			freadnoswap(&callsigns_temp[j],1,1,fp);

		FRAMEBUFFER_putFrame(nplanes, positions_temp, lengths_temp, callsigns_temp);

		free(positions_temp);
		free(lengths_temp);
		free(callsigns_temp);
	}

	/* close the file */
	fclose(fp);

	// Notify Detector there is a new frame in the buffer
	// TODO: the Java version notifies using threads, maybe need to do something similar?!
	DETECTOR_run();

	return;
}

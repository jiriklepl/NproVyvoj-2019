/*
 * Aircraft.c
 *
 *  Created on: Jul 29, 2009
 *      Author: ghaitho
 */

#include "Aircraft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Aircraft * AIRCRAFT_init(Aircraft * ac, char * cs) {
	ac->callsign = cs;
	return ac;
}

char * AIRCRAFT_toString(Aircraft * ac) {
	char * ret = (char *) malloc(strlen(ac->callsign)+1);
	strcpy(ret,ac->callsign);
	return ret;
}

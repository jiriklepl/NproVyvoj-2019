/*
 * CallSign.h
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#ifndef CALLSIGN_H_
#define CALLSIGN_H_

struct CallSignType ;

#define RAWFRAME_MAX_PLANES 1000
#define RAWFRAME_MAX_SIGNS 10 * RAWFRAME_MAX_PLANES

typedef struct CallSignType
{
    int length;
    char * val; // zero terminated string
} CallSign ;

int CALLSIGN_HashCode(CallSign *);
int CALLSIGN_equals(CallSign *,CallSign *);
int CALLSIGN_compareTo(CallSign *,CallSign *);
CallSign * CALLSIGN_cp(CallSign *, char * cs, int);

#endif /* CALLSIGN_H_ */

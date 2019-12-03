/*
 * StateTable.h
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#ifndef STATETABLE_H_
#define STATETABLE_H_

#include "CallSign.h"
#include "Vector3d.h"

#define MAX_AIRPLANES 10000

void STATETABLE_init();
void STATETABLE_put(CallSign * callsign, float, float, float);
int STATETABLE_get(CallSign * callsign, Vector3d *);

#endif /* STATETABLE_H_ */

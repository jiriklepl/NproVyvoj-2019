/*
 * NanoClock.c
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#include "NanoClock.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

long baseMillis = -1;
long baseNanos = -1;

void NANOCLOCK_init() {
    if (baseMillis != -1 || baseNanos != -1) {
      printf("NanoClock already initialized.");
      exit(0);
    }

    // TODO: get nanoseconds from cpu time
    baseNanos = 0;
    baseMillis = clock();
}

long NANOCLOCK_now() {

    long millis = clock() - baseMillis;
    long nanos = 0;

    return millis*1000000 + nanos - baseNanos;
  }


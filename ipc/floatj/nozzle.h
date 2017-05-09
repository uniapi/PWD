/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 7, 2017
***************************************************************************************/

#ifndef NOZZLE
#define NOZZLE

#include "floatjet.h"

typedef struct {
	synchronizer sync;
	int ignited;
	floage floatygen;
} nozzle;

int nzlpre(nozzle *nzl);

#endif

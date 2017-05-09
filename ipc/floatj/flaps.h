/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 4, 2017
***************************************************************************************/

#ifndef FLAPS
#define FLAPS

#include <float.h>
#include "ctlact.h"

#define FLOWLIM DBL_DIG

typedef struct {
	int n;
	int x;
	char flow[FLOWLIM];
	ctlact *ctls;
} flaps;

#endif

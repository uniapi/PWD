/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 4, 2017
***************************************************************************************/

#ifndef FLOATIDIZER
#define FLOATIDIZER

#include <math.h>
#include "floatjet.h"

typedef struct {
	double exponent;
	floage floatygen;
} floatidizer;

floage floatidize(floatidizer *flt);

#endif

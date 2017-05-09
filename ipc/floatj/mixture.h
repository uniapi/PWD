/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 3, 2017
***************************************************************************************/

#ifndef MIXTURE
#define MIXTURE

#include <unistd.h>
#include "inlet.h"
#include "floatidizer.h"
#include "combustor.h"

int diffuse(inlet *inl, floatidizer *flt);
int inject(floatidizer *flt, combustor *cmb);

#endif

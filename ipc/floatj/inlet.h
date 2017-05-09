/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                    April 27, 2017
***************************************************************************************/

#ifndef INLET
#define INLET

#include "floatjet.h"

typedef struct {
    int in;
    int out;
} inlet;

int inlseal(inlet *inl, ioput io);

#endif

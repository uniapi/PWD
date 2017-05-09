/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                    April 27, 2017
***************************************************************************************/

#ifndef COMBUSTOR
#define COMBUSTOR

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "floatjet.h"

#define POSIMP

#ifdef POSIMP
	#include <sys/mman.h>
#else
	#include <sys/shm.h>
#endif

typedef struct {
	cmbid id;
	synchronizer sync;
	int injected;
	floage floatygen;
} combustor;

combustor *cmbat(cmbid cid);
int cmbpre(combustor *cmb);
cmbid cmbdt(combustor *cmb);

#endif

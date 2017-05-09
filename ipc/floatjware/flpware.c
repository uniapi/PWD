/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 7, 2017
***************************************************************************************/

#include "flpware.h"

flaps *flpget(ctlact *ctls)
{
	flaps *f = (flaps *) malloc(sizeof(flaps));

	if (f)
		f->ctls = ctls;
	return f;
}

void flprem(flaps *flp)
{
	if (flp) {
        if (flp->ctls)
			free(flp->ctls);
		free(flp);
	}
}

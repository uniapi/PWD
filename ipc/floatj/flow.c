/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 3, 2017
***************************************************************************************/

#include "flow.h"

int intake(flaps *flp, inlet *inl)
{
	floage f;
	int done = 0;
	size_t gsz = sizeof f;

	if (!flp || ! inl)
		return -1;
	if (!sscanf(flp->flow, "%lf", &f))
		return done;
	if (gsz == write(inl->in, (void *) &f, gsz))
		done = !done;
	return done;
}

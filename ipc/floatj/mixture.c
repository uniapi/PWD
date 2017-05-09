/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 4, 2017
***************************************************************************************/

#include "mixture.h"

int diffuse(inlet *inl, floatidizer *flt)
{
	int done = 0;
	size_t gsz = sizeof flt->floatygen;
	
	if (!inl || !flt)
		done = -1;
	else if (gsz == read(inl->out, (void *) &flt->floatygen, gsz))
		done = !done;
	return done;
}

int inject(floatidizer *flt, combustor *cmb)
{
	int done = 0;
	
	if (!flt || !cmb)
		done = -1;
	else do  {
		synclock(&cmb->sync);
		if (!cmb->injected) {
			cmb->floatygen = flt->floatygen;
			cmb->injected = !cmb->injected;
			done = !done;
		}
		syncunlock(&cmb->sync);
	}
	while (!done);

	return done;
}

/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 7, 2017
***************************************************************************************/

#include "inlware.h"

inlet *inlget(void)
{
	inlet *i = (inlet *) malloc(sizeof(inlet));

	if (i)
		if (pipe(i) == -1)
			free(i);
	return i;
}

void inlrem(inlet *inl)
{
	if (inl)
		free(inl);
}

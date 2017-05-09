/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 7, 2017
***************************************************************************************/

#include "inlet.h"

int inlseal(inlet *inl, ioput io)
{
	int sealed = 0;

	if (!inl)
		return -1;

	switch (io) {
	case INPUT:
		close(inl->in);
		break;
	case OUTPUT:
		close(inl->out);
		break;
	default:
		sealed = 1;
	}

	return sealed;
}

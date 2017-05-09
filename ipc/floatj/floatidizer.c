/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 4, 2017
***************************************************************************************/

#include "floatidizer.h"

floage floatidize(floatidizer *flt)
{
	flt->floatygen = pow(flt->floatygen, flt->exponent);

	return flt->floatygen;
}

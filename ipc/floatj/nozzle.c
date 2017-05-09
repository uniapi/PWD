/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 7, 2017
***************************************************************************************/

#include "nozzle.h"

int nzlpre(nozzle *nzl)
{
	if (!nzl)
		return -1;
	nzl->ignited = 0;
	
	return 	syncinit(&nzl->sync);
}

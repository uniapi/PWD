/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 8, 2017
***************************************************************************************/

#include "synchronizer.h"

int syncinit(synchronizer *sync)
{
	return pthread_mutex_init(sync, (synchrotuner *) 0);
}

int synclock(synchronizer *sync)
{
	return pthread_mutex_lock(sync);
}

int syncunlock(synchronizer *sync)
{
	return pthread_mutex_unlock(sync);
}


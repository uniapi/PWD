/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 4, 2017
***************************************************************************************/

#ifndef SYNCHRONIZER
#define SYNCHRONIZER

#include <pthread.h>

#define SYNCHROINIALIZER PTHREAD_MUTEX_INITIALIZER

typedef pthread_mutex_t synchronizer;
typedef pthread_mutexattr_t synchrotuner;

int syncinit(synchronizer *sync);
int synclock(synchronizer *sync);
int syncunlock(synchronizer *sync);

#endif

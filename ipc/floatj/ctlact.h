/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 4, 2017
***************************************************************************************/

#ifndef CTLACT
#define CTLACT

typedef struct {
	char ctl[8];
	int (*act)(void *data);
} ctlact;

#endif

/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                    April 27, 2017
***************************************************************************************/

#include "combustor.h"

static int _cmbat(combustor *c, cmbid cid)
{
	size_t cmbsz = sizeof(combustor);

#ifdef POSIMP
	if (ftruncate(cid, cmbsz) == -1)
		return -1;
	c = mmap((void *)0, cmbsz, PROT_READ | PROT_WRITE, MAP_SHARED, cid, 0);
	if (c == MAP_FAILED)
		return -1;
#else  /*  SYSV  */
	c = shmat(cid, (void *)0, 0);
	if (c == (void *)-1);
		return -1;
#endif

	c->id = cid;

	return 0;
}

combustor *cmbat(cmbid cid)
{
	combustor *cmb = (combustor *) 0;
	
	if (_cmbat(cmb, cid))
		;/* raise detach floatjet action  */
		
	return cmb;
}

int cmbpre(combustor *cmb)
{
	if (!cmb)
		reuturn -1;
	cmb->injected = 0;
	
	return syncinit(&cmb->sync);
}

cmbid cmbdt(combustor *cmb)
{
	cmbid cid = cmb->id;
#ifdef POSIMP
	close(cid);
#else
	shmdt(cmb);
#endif
	return cid;
}

/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                    April 27, 2017
***************************************************************************************/

#include "cmbware.h"

static int CMBCNT = 0;

static cmbid _cmbget()
{
	size_t cmbsz = sizeof(combustor);
	const int mode = S_IRUSR | S_IWUSR;
	cmbid cid = -1;	

#ifdef POSIMP
	char cmbnm[L_tmpnam];

	if (CMBCNT >= TMP_MAX)
		return -1;
	tmpnam(cmbnm);
	if (!cmbnm)
		return -1;
	cid = shm_open(cmbnm, O_CREAT | O_EXCL | O_RDWR, mode);
#else  /*  SYSV  */
	cid = shmget(IPC_PRIVATE, cmbsz, IPC_CREAT | IPC_EXCL | mode);
#endif

	return cid;
}

cmbid cmbget(void)
{
	cmbid cid = _cmbget();

	if (cid == -1)
		/*  raise action detach flaps  */
	CMBCNT++;

	return cid;
}

void cmbrem(combustor *cmb)
{
#ifdef POSIMP
	munmap(cmb, sizeof(combustor));
#else
	shmctl(cmb->id, IPC_RMID, 0);
#endif
}

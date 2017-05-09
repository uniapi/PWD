/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                    April 27, 2017
***************************************************************************************/

#ifndef CMBWARE
#define CMBWARE

#include <stdio.h>
#include <fcntl.h>
#include "../floatj/combustor.h"

cmbid cmbget(void);           /*  geting a combustor    */
void cmbrem(combustor *cmb);  /*  removing a combustor  */

#endif

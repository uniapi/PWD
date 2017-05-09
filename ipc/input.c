/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 9, 2017
***************************************************************************************/

/*  [not implemented]  */

#include "input.h"


int getin(flaps *flp, inlet *inl)
{
	char c;

	while (1) {
		c = getchar();

		switch (c) {
		case '\n':
			intake(flp, inl);
			break;
		
	}
}

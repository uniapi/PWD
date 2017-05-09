/***************************************************************************************
                  Licensed under the Academic Free License version 3.0
                                Written by Ali Muhammed
                                patrash.ali@promwad.com
                                  uniapi@outlook.com
                                     May 9, 2017
***************************************************************************************/

#include "env.h"

static struct termios srcterm, stdterm;

void envon()
{
	tcgetattr(STDIN_FILENO, &srcterm);
	stdterm = srcterm;

	stdterm.c_lflag &= ~ (ECHO | ICANON);
	stdterm.c_cc[VMIN] = 1;
	stdterm.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &stdterm);
}

void envoff()
{
	tcsetattr(0, TCSANOW, &srcterm);
}

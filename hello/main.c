/**********************************************************
                  Written by Ali Muhammed
                  patrash.ali@promwad.com
                    uniapi@outlook.com
                      March 17, 2017
**********************************************************/

#include <stdio.h>

extern char *hello(void);       /* explicit forward declaration  */
extern char *goodbye(void);

main(argc, argv)
int argc; char *argv[];
{
    printf("%s\n", hello());    /*  printing: Hello, World       */
    puts(goodbye());            /*  printing: Goodbye, World     */
}

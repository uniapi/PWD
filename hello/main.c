/**********************************************************
                  Written by Ali Muhammed
                  patrash.ali@promwad.com
                    uniapi@outlook.com
                      March 17, 2017
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "goodbye.h"

#define LIBPATH "LD_LIBRARY_PATH"
#define LIBHELLO "libhello.so"

main(int argc, char *argv[])
{
    char *libpath = NULL;                   /*  a good practise for team-projects          */
    void *libhello = NULL;
    char *(*hello)(void) = NULL;

	libhello = dlopen(LIBHELLO, RTLD_LAZY); /*  loading libhello.so                        */
	if (!libhello) {                        /*  checking if libhello.so is loaded          */
		fprintf(stderr, "error: " LIBHELLO " not found\n");
		fprintf(stderr, "tip: copy " LIBHELLO " to /usr/lib or if no access privileges\n");

		libpath = getenv(LIBPATH);
		if (!libpath)                       /*  checking if LD_LIBRARY_PATH exists         */
			fprintf(stderr, "     export " LIBPATH " variable with the value of its directory\n");
		else
			fprintf(stderr, "     add its directory to your " LIBPATH " variable\n");

		exit(1);                            /*  exiting with the error code                */
	}

	hello = (char *(*)(void))dlsym(libhello, "hello");        /*  loading hello function   */
	if (!hello) {                           /*  checking if the function is loaded         */
		fprintf(stderr, "error: broken package\n");
        fprintf(stderr, "tip: try to rebuild the program\n");

		exit(1);
	}

	printf("%s\n", hello());                /*  printing: Hello, World    */
	puts(goodbye());                        /*  printing: Goodbye, World  */
	
    dlclose(libhello);                      /*  uploading libhello.so     */

    return 0;                               /*  exiting with the success  */
}

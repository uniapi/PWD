# **************************************************************************************
#                 Licensed under the Academic Free License version 3.0
#                               Written by Ali Muhammed
#                               patrash.ali@promwad.com
#                                 uniapi@outlook.com
#                                    May 9, 2017
# **************************************************************************************

CFLAGS="-std=c89"

all: libfloatjware.a

libfloatjware.a: flpware.o inlware.o cmbware.o
	ar cr libfloatjware.a flpware.o inlware.o cmbware.o

flpware.o: flpware.c flpware.h
	cc $(CFLAGS) -c flpware.c
inlware.o: inlware.c inlware.h
	cc $(CFLAGS) -c inlware.c
cmbware.o: cmbware.c cmbware.h
	cc $(CFLAGS) -c cmbware.c

clean-obj:
	rm *.o
clean-ar:
	rm *a

clean: clean-obj clean-ar

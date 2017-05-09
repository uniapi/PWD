# **************************************************************************************
#                 Licensed under the Academic Free License version 3.0
#                               Written by Ali Muhammed
#                               patrash.ali@promwad.com
#                                 uniapi@outlook.com
#                                    May 8, 2017
# **************************************************************************************

CFLAGS="-std=c89"

all: libfloatjet.a

libfloatjet.a: flow.o mixture.o expansion.o \
	           inlet.o floatidizer.o nozzle.o
	ar cr libfloatjet.a flow.o mixture.o expansion.o \
	      inlet.o floatidizer.o nozzle.o

flow.o: flow.c flow.h
	cc $(CFLAGS) -c flow.c
mixture.o: mixture.c mixture.h
	cc $(CFLAGS) -c mixture.c
expansion.o: expansion.c expansion.h
	cc $(CFLAGS) -c expansion.c

inlet.o: inlet.c inlet.h floatjet.h
	cc $(CFLAGS) -c inlet.c
floatidizer.o: floatidizer.c floatidizer.h floatjet.h
	cc $(CFLAGS) -c floatidizer.c
combustor.o: combustor.c combustor.h floatjet.h
	cc $(CFLAGS) -c combustor.c
nozzle.o: nozzle.c nozzle.h floatjet.h
	cc $(CFLAGS) -c nozzle.c

clean-obj:
	rm *.o
clean-ar:
	rm *a
clean: clean-obj clean-ar

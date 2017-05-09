# **************************************************************************************
#                 Licensed under the Academic Free License version 3.0
#                               Written by Ali Muhammed
#                               patrash.ali@promwad.com
#                                 uniapi@outlook.com
#                                    May 9, 2017
# **************************************************************************************

CFLAGS="-std=c89"
TARGET="floatjet"
FLOATJ="./floatj"
FLOATJWARE="./floatjware"

all: this libs
	cc $(CFLAGS) -o $(TARGET) main.o env.o input.o exponent.o output.o \
	             -L $(FLOATJ) -lfloatjet -L $(FLOATJWARE) -lfloatjware

this: main.o env.o input.o exponent.o output.o

libs: libfloatjet libfloatjware

libfloatjet:
	cd $(FLOATJ) && $(MAKE)
libfloatjware:
	cd $(FLOATJWARE) && $(MAKE)

main.o: main.c env.h input.h exponent.h output.h
	cc $(CFLAGS) -c main.c
env.o: env.c
	cc $(CFLAGS) -c env.c
input.o: input.c
	cc $(CFLAGS) -c input.c
exponent.o: exponent.c
	cc $(CFLAGS) -c exponent.c
output.o: output.c
	cc $(CFLAGS) -c output.c

clean-this:
	rm *.o

clean-obj:
	cd $(FLOATJ) && $(MAKE) clean-obj
	cd $(FLOATJWARE) && $(MAKE) clean-obj

clean-ar:
	cd $(FLOATJ) && $(MAKE) clean-ar
	cd $(FLOATJWARE) && $(MAKE) clean-ar

clean-libs: clean-obj clean-ar

clean: clean-this clean-libs


CFLAGS="-std=c89"

all: main.o libhello.so libgoodbye.a
#	building with this option you need to copy libhello.so to /usr/lib or if no access privileges
#	export an environment variable: LD_LIBRARY_PATH being set to libhello.so directory
	cc $(CFLAGS) -o hello main.o -L. -lgoodbye -ldl
#	this option does not require anything while a shared library resides in the current directory
#	cc $(CFLAGS) -o hello main.o -L. -lhello -Wl,-rpath,./ -L. -lgoodbye

main.o: main.c goodbye.h
	cc $(CFLAGS) -c main.c

libs: libhello.so libgoodbye.a

libhello.so: hello.o
	cc -shared -fPIC -o libhello.so hello.o
hello.o: hello.c
	cc $(CFLAGS) -c -fPIC hello.c

libgoodbye.a: goodbye.o
	ar cr libgoodbye.a goodbye.o
goodbye.o: goodbye.c
	cc $(CFLAGS) -c goodbye.c

clean:
	rm hello *.o *.a *.so

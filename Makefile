CC = gcc
CFLAGS = -Wall -g
PROG = encode decode cmp copy stshell ctrl_C
LIB = libcodecA.so libcodecB.so
LIBDIR = .
all: $(PROG)
encode: encode.o $(LIB)
	$(CC) $(CFLAGS) -o encode encode.o -L$(LIBDIR) -lcodecA -lcodecB -Wl,-rpath=$(LIBDIR)
decode: decode.o $(LIB)
	$(CC) $(CFLAGS) -o decode decode.o -L$(LIBDIR) -lcodecA -lcodecB -Wl,-rpath=$(LIBDIR)
#Libraries
libcodecA.so: codecA.o
	$(CC) -shared -fPIC -o libcodecA.so codecA.o
libcodecB.so: codecB.o
	$(CC) -shared -fPIC -o libcodecB.so codecB.o

cmp: cmp.o
	$(CC) $(FLAG) -o cmp cmp.o

ctrl_C: ctrl_C.o
	$(CC) $(FLAG) -o ctrl_C ctrl_C.o

cmp.o: cmp.c
	$(CC) $(FLAG) -c cmp.c

copy: copy.o
	$(CC) $(FLAG) -o copy copy.o

copy.o: copy.c
	$(CC) $(FLAG) -c copy.c

stshell: stshell.o
	$(CC) $(FLAG) -o stshell stshell.o

stshell.o: stshell.c
	$(CC) $(FLAG) -c stshell.c

ctrl_C.o: ctrl_C.c
	$(CC) $(FLAG) -c ctrl_C.c
	
.PHONY: clean all
clean:
	rm -f *.o $(LIB) $(PROG)
